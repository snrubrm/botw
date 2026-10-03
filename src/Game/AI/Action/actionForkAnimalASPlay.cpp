#include "Game/AI/Action/actionForkAnimalASPlay.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkAnimalASPlay::ForkAnimalASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAnimalASPlay::~ForkAnimalASPlay() = default;

bool ForkAnimalASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAnimalASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* as_list = mActor->getASList();
    auto* controller = mActor->getCharacterController();
    auto* rideable = mActor->m132();
    if (!as_list || !controller || !rideable) {
        setFailed();
        return;
    }

    const s32 frame = *mAllowChangeableFrame_s;
    if (frame >= 0) {
        _50.reset(frame + 0.5f);
        if (_50.value < 1.0f)
            mFlags.set(Flag::Changeable);
    } else {
        _50.reset(frame, 0.0f);
    }

    if (mASKeyName_s.isEmpty()) {
        setFailed();
        return;
    }

    if (*mIsIgnoreSameAS_s && as_list->x_1(0, 0) == mASKeyName_s)
        return;

    rideable->_18.sub_7100E786F0(mASKeyName_s);
}

void ForkAnimalASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAnimalASPlay::loadParams_() {
    getStaticParam(&mAllowChangeableFrame_s, "AllowChangeableFrame");
    getStaticParam(&mSelectNextGearType_s, "SelectNextGearType");
    getStaticParam(&mSelectNextGear_s, "SelectNextGear");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASKeyName_s, "ASKeyName");
}

void ForkAnimalASPlay::calc_() {
    auto* as_list = mActor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }

    m32();
    if (mASKeyName_s != as_list->x_1(0, 0))
        return;
    if (!isFinishedAS(0, 0))
        return;

    if (auto* list = mActor->getASList()) {
        const s32 gear = *mSelectNextGear_s;
        if (gear >= 0) {
            if (auto* rideable = mActor->m132()) {
                const s32 type = *mSelectNextGearType_s;
                rideable->sub_7100E63224(type >= 1 && type <= 5 ? u32(type) : 0, u32(gear));
                list->x_6(1, 0, 0.0f);
                list->x_6(2, 0, 0.0f);
            }
        }
    }
    setFinished();
}

void ForkAnimalASPlay::m32() {
    _50.update();
    if (_50.hasEnded(0.0f))
        mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
