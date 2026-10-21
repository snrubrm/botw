#include "Game/Actor/Behavior/behaviorRumbleController.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

namespace uking::behavior {

RumbleController::RumbleController(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

RumbleController::~RumbleController() = default;

bool RumbleController::init_(sead::Heap* heap) {
    return true;
}

void RumbleController::enter() {}

void RumbleController::leave() {}

void RumbleController::loadParams() {
    getStaticParam(&mReduceDist_s, "ReduceDist");
}

// NON_MATCHING: the "Large"/"Middle" comparisons keep a SafeString temporary that clang inlines away in
// smaller functions (one extra assureTerminationImpl_ call, an unrolled byte loop and a 0x10 larger frame),
// and clang folds the Mathi::floor below to a plain truncation here.
void RumbleController::calc() {
    auto* list = mActor->getASList();
    if (!list)
        return;
    if (ksys::VFR::instance()->getDeltaFrame() < 1.0f)
        return;

    ksys::as::ASList::Unk4 query;
    if (list->sub_710115FBC8(50, &query, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        RumblePattern pattern(3);
        if (query.name == "Large")
            pattern = RumblePattern::_5;
        else if (query.name == "Middle")
            pattern = RumblePattern::_4;

        const sead::Vector3f position = mActor->getMtx().getTranslation();
        const f32 distance = (getPlayerPosition() - position).length();
        if (*mReduceDist_s > 0.0f) {
            const s32 lowered = int(pattern) - sead::Mathi::floor(distance / *mReduceDist_s);
            s32 lowest = 3;
            if (int(pattern) >= 0 && int(pattern) < 3)
                lowest = 0;
            pattern = RumblePattern(sead::Mathi::clampMin(lowered, lowest));
            if (lowered >= lowest) {
                const f32 duration = Rumble::instance()->sub_7100899108(pattern);
                const s32 frames = sead::Mathi::clampMin(
                    sead::Mathi::floor(query._10 / f32(ksys::VFR::instance()->getFrameRate()) /
                                       duration),
                    1);
                s32 count = 1;
                if (duration <= 3.0f && duration > 0.0f)
                    count = sead::Mathi::clampMax(frames, s32(3.0f / duration));
                Rumble::instance()->sub_7100897FE4(pattern, count);
            }
        } else {
            pattern = RumblePattern::_0;
            if (int(pattern) < 0 || int(pattern) > 2)
                pattern = RumblePattern::_3;
        }
        mActor->m107();
    }

    if (list->sub_710115FBC8(86, &query, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
        RumblePattern pattern(0);
        if (query.name == "Large")
            pattern = RumblePattern::_2;
        else if (query.name == "Middle")
            pattern = RumblePattern::_1;

        const sead::Vector3f position = mActor->getMtx().getTranslation();
        const f32 distance = (getPlayerPosition() - position).length();
        if (*mReduceDist_s > 0.0f) {
            const s32 lowered = int(pattern) - sead::Mathi::floor(distance / *mReduceDist_s);
            s32 lowest = 3;
            if (int(pattern) >= 0 && int(pattern) < 3)
                lowest = 0;
            pattern = RumblePattern(sead::Mathi::clampMin(lowered, lowest));
            if (lowered >= lowest)
                Rumble::instance()->sub_7100897FE4(pattern, 1);
        } else {
            pattern = RumblePattern::_0;
            if (int(pattern) < 0 || int(pattern) > 2)
                pattern = RumblePattern::_3;
        }
    }
}

}  // namespace uking::behavior
