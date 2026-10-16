#include "Game/Actor/Action/actionSlippedMoveBase.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"

namespace uking::action {

SlippedMoveBase::SlippedMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SlippedMoveBase::~SlippedMoveBase() = default;

bool SlippedMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SlippedMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    sead::Vector3f dir = actor->getVelocity();
    const f32 speed = dir.normalize();
    mFlags.set(Flag::Changeable);

    if (auto* controller = actor->getCharacterController()) {
        const f32 ang_speed = actor->getAngVelocity().length();
        _a0 = ang_speed > *mRotSpd_s ? *mRotSpd_s : ang_speed;
        sub_710073FA90(&_7c, actor);
        mWallHitTimer.reset(0.0f, 1.0f);
        sub_710072C1B4(controller, dir);
        sub_7100737708(controller, speed);
    } else {
        setFailed();
    }
}

void SlippedMoveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void SlippedMoveBase::loadParams_() {
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

void SlippedMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

// NON_MATCHING: block layout (the original re-tests the ground dot product instead of branching straight to update)
bool SlippedMoveBase::sub_7100271294(const sead::Vector3f& probe_dir, const sead::Vector3f& dir,
                                     bool* hit_out) {
    const bool hit = sub_710072FEC4(mActor, probe_dir, 2.0f, nullptr, true, nullptr);
    bool against_wall;
    if (isLandedMaybe(mActor, false)) {
        against_wall = dir.dot(sub_71007A471C(mActor, 0)->_c) < 0.0f;
        if (!against_wall && hit)
            against_wall = dir.dot(probe_dir) >= 0.9659258f;
    } else {
        against_wall = hit && dir.dot(probe_dir) >= 0.9659258f;
    }

    if (against_wall)
        mWallHitTimer.update();
    else
        mWallHitTimer.reset(0.0f, 1.0f);

    if (hit_out)
        *hit_out = hit;

    return mWallHitTimer.value <= static_cast<f32>(*mWallHitLimitTime_s) &&
           (!hit || mWallHitTimer.value <= 10.0f);
}

}  // namespace uking::action
