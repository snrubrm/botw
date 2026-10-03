#include "Game/AI/Action/actionBackWalkBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: regalloc (keeps &_68 in x20 across the memset)
BackWalkBase::BackWalkBase(const InitArg& arg) : ActionEx(arg) {}

void BackWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getCharacterController())
        return;
    const f32 time = *mParams.mTime_s;
    _98 = ksys::Timer(time, time);
    _a4 = ksys::Timer(20.0f, 20.0f);
    sub_7100741034(&_74, mActor);
    const f32 speed = mActor->getAngVelocity().length();
    _68.value = speed;
    _68.prev_value = speed;
    mFlags.set(Flag::Changeable);
}

void BackWalkBase::leave_() {
    ActionEx::leave_();
}

void BackWalkBase::loadParams_() {
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mRotAddRatio_s, "RotAddRatio");
    getStaticParam(&mParams.mTime_s, "Time");
    getStaticParam(&mParams.mFinishDist_s, "FinishDist");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mDecelRatio_s, "DecelRatio");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mIsCliffCheck_s, "IsCliffCheck");
}

void BackWalkBase::calc_() {
    ActionEx::calc_();
}

bool BackWalkBase::isChangeable() const {
    return true;
}

}  // namespace uking::action
