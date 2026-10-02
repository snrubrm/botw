#include "Game/AI/Action/actionAnmDrivenSpeedBackWalk.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AnmDrivenSpeedBackWalk::AnmDrivenSpeedBackWalk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmDrivenSpeedBackWalk::~AnmDrivenSpeedBackWalk() = default;

bool AnmDrivenSpeedBackWalk::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: scheduling of the SafeString temporary stores
void AnmDrivenSpeedBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getCharacterController())
        return;

    if (auto* rideable = mActor->m132())
        rideable->_18.sub_7100E786F0("BackWalk");
    else
        playAS("BackWalk", true, 0, 0, -1.0f);

    const f32 time = *mTime_s;
    _78 = ksys::Timer(time, time);
    _84 = ksys::Timer(20, 20);
    sub_710073FA90(&_54, mActor);
    _50 = mActor->getAngVelocity().length();
    mFlags.set(Flag::Changeable);
}

void AnmDrivenSpeedBackWalk::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmDrivenSpeedBackWalk::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mRotAddRatio_s, "RotAddRatio");
    getStaticParam(&mFinishDist_s, "FinishDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnmDrivenSpeedBackWalk::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
