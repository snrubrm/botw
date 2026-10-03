#include "Game/AI/Action/actionSlippedWalkBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SlippedWalkBase::SlippedWalkBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SlippedWalkBase::~SlippedWalkBase() = default;

bool SlippedWalkBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SlippedWalkBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sead::Vector3f dir = actor->getVelocity();
    const f32 speed = dir.normalize();
    mFlags.set(Flag::Changeable);

    if (auto* controller = actor->getCharacterController()) {
        const f32 ang_speed = actor->getAngVelocity().length();
        _a0 = ang_speed > *mRotSpd_s ? *mRotSpd_s : ang_speed;
        sub_710073FA90(&_7c, actor);
        _70.set(0.0f, 0.0f, 1.0f);
        sub_710072C1B4(controller, dir);
        sub_7100737708(controller, speed);
    } else {
        setFailed();
    }
}

void SlippedWalkBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SlippedWalkBase::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mWallHitLimitTime_s, "WallHitLimitTime");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mFollowGround_s, "FollowGround");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SlippedWalkBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
