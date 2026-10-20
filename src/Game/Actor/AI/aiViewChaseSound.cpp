#include "Game/Actor/AI/aiViewChaseSound.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"
#include <cmath>

namespace uking::ai {

ViewChaseSound::ViewChaseSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ViewChaseSound::~ViewChaseSound() = default;

bool ViewChaseSound::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: request construction store order (the original zeroes _c with _8 next to the vtable) and the scheduling
// of the direction subtraction
inline bool ViewChaseSound::isTargetInViewMaybe() const {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;
    Unk_71023e26d8 request;
    if (auto* sensor = awareness->_260[0])
        sensor->m4(&request);
    const sead::Vector3f target = *mTargetPos_d;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    const sead::Vector3f dir = mActor->getMtx().getBase(2);
    return sub_710072DEF0(target, request.params.alert.radius, request.params.alert.angle, request.params.alert.height_min, pos, dir, request.params.alert.height_max, 1.0f, 1.2f);
}

void ViewChaseSound::enter_(ksys::act::ai::InlineParamPack* params) {
    if (isTargetInViewMaybe()) {
        changeChild("見まわし");
        return;
    }

    sead::Vector3f dir;
    dir.setSub(*mTargetPos_d, mActor->getMtx().getTranslation());
    dir.normalize();
    if (dir.dot(mActor->getMtx().getBase(2)) >= std::cos(*mTurnDir_s)) {
        auto* nav = mActor->m45();
        const f32 radius = nav ? nav->getRadiusMaybe() : 0.0f;
        if (sub_710072F944(mActor, *mTargetPos_d, nullptr, radius, 10.0f))
            sub_71005E4268();
        else
            sub_71005E4150();
    } else {
        sub_71005E39E8();
    }
}

// 0x71005e3bf0
// NON_MATCHING: request construction store order (as enter_).
void ViewChaseSound::calc_() {
    if (!isCurrentChild("見まわし")) {
        const sead::Vector3f target = *mTargetPos_d;
        sub_71005DB1D8(mActor, target);
    } else {
        sub_71005DB3EC(mActor);
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!isCurrentChild("追跡") && !isCurrentChild("直線追跡")) {
            if (!isCurrentChild("回転")) {
                setFinished();
                return;
            }
            if (!isTargetInViewMaybe()) {
                sub_71005E3B00(false);
                return;
            }
        }
        changeChild("見まわし");
        return;
    }

    if (child->isChangeable()) {
        if (isCurrentChild("追跡") || isCurrentChild("直線追跡")) {
            if (isTargetInViewMaybe()) {
                changeChild("見まわし");
                return;
            }
            if (sub_71005E3B00(false))
                return;
        } else if (isCurrentChild("回転")) {
            if (isTargetInViewMaybe())
                changeChild("見まわし");
        }
    }

    sead::Vector3f pos = *mTargetPos_d;
    somePositionCalc(&pos, pos, -sead::Vector3f::ey, 10.0f);
    child->setDynamicParam(pos, "TargetPos");
}

void ViewChaseSound::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ViewChaseSound::loadParams_() {
    getStaticParam(&mTurnDir_s, "TurnDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// 0x71005e39e8
// 0x71005e3b00
bool ViewChaseSound::sub_71005E3B00(bool force) {
    auto* nav = mActor->m45();
    const f32 radius = nav ? nav->getRadiusMaybe() : 0;
    if (sub_710072F944(mActor, *mTargetPos_d, nullptr, radius, 10.0f)) {
        if (!force && isCurrentChild("直線追跡"))
            return false;
        sub_71005E4268();
    } else {
        if (!force && isCurrentChild("追跡"))
            return false;
        sub_71005E4150();
    }
    return true;
}

void ViewChaseSound::sub_71005E39E8() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos = *mTargetPos_d;
    somePositionCalc(&pos, pos, -sead::Vector3f::ey, 10.0f);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("回転", &pack);
}

// 0x71005e4150
void ViewChaseSound::sub_71005E4150() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos = *mTargetPos_d;
    somePositionCalc(&pos, pos, -sead::Vector3f::ey, 10.0f);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("追跡", &pack);
}

// 0x71005e4268
void ViewChaseSound::sub_71005E4268() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos = *mTargetPos_d;
    somePositionCalc(&pos, pos, -sead::Vector3f::ey, 10.0f);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("直線追跡", &pack);
}

}  // namespace uking::ai
