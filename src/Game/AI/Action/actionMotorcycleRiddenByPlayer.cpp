#include "Game/AI/Action/actionMotorcycleRiddenByPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"

namespace uking::action {

// NON_MATCHING: the original keeps the six 0xffff halfword stores of the BoneAccessKeys separate
MotorcycleRiddenByPlayer::MotorcycleRiddenByPlayer(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

MotorcycleRiddenByPlayer::~MotorcycleRiddenByPlayer() {
    _c0.sub_7100D786EC();
}

bool MotorcycleRiddenByPlayer::init_(sead::Heap* heap) {
    _c0.sub_7100D78564(heap);
    return true;
}

void MotorcycleRiddenByPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MotorcycleRiddenByPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void MotorcycleRiddenByPlayer::loadParams_() {
    getStaticParam(&mCrashVelocityThreshold_s, "CrashVelocityThreshold");
    getStaticParam(&mRideOnDelayFrames_s, "RideOnDelayFrames");
    getStaticParam(&mFallThresholdForThrowOff_s, "FallThresholdForThrowOff");
    getStaticParam(&mCrashVelocityDeltaThreshold_s, "CrashVelocityDeltaThreshold");
    getStaticParam(&mChargeVelocityThreshold_s, "ChargeVelocityThreshold");
    getStaticParam(&mDriftCutGrassRange_s, "DriftCutGrassRange");
    getStaticParam(&mDriftCutGrassIntensity_s, "DriftCutGrassIntensity");
    getStaticParam(&mCutLowTreeVelocityThreshold_s, "CutLowTreeVelocityThreshold");
    getStaticParam(&mCutLowTreeVelocitySize_s, "CutLowTreeVelocitySize");
    getStaticParam(&mTerrorVelocityThreshold1_s, "TerrorVelocityThreshold1");
    getStaticParam(&mTerrorVelocityThreshold2_s, "TerrorVelocityThreshold2");
    getStaticParam(&mTerrorVelocityThreshold3_s, "TerrorVelocityThreshold3");
    getStaticParam(&mTerrorVelocityThreshold4_s, "TerrorVelocityThreshold4");
    getStaticParam(&mTerrorRadius_s, "TerrorRadius");
    getStaticParam(&mTerrorOffsetDistanceSec_s, "TerrorOffsetDistanceSec");
    getStaticParam(&mForbidSpinturnAngleRange_s, "ForbidSpinturnAngleRange");
    getStaticParam(&mPermitManualWheelieAngleRange_s, "PermitManualWheelieAngleRange");
    getStaticParam(&mAttackChargeBoneOffset_s, "AttackChargeBoneOffset");
}

void MotorcycleRiddenByPlayer::calcTerrorVelocityStuff(f32 speed, const sead::Vector3f* dir) {
    f32 level = 0;
    if (*mTerrorVelocityThreshold4_s <= speed)
        level = 4;
    else if (*mTerrorVelocityThreshold3_s <= speed)
        level = 3;
    else if (*mTerrorVelocityThreshold2_s <= speed)
        level = 2;
    else if (*mTerrorVelocityThreshold1_s <= speed)
        level = 1;
    _c0._10._10.makeAllZero();
    _c0._10._18.m15();
    const int idx = 2;
    _c0.x(idx, 0x80, level);
    _c0.setRadius(*mTerrorRadius_s);
    const f32 scale = *mTerrorOffsetDistanceSec_s * speed;
    const f32 dx = dir->x * scale;
    const f32 dy = scale * dir->y;
    const f32 dz = scale * dir->z;
    const auto& m = mActor->getMtx();
    const sead::Vector3f offset{dx * m(0, 0) + dy * m(1, 0) + dz * m(2, 0),
                                dx * m(0, 1) + dy * m(1, 1) + dz * m(2, 1),
                                dx * m(0, 2) + dy * m(1, 2) + dz * m(2, 2)};
    _c0._88 = offset;
}

void MotorcycleRiddenByPlayer::calc_() {
    ksys::act::ai::Action::calc_();
}

bool MotorcycleRiddenByPlayer::hasUpdateForPreDeleteCb() {
    return true;
}

bool MotorcycleRiddenByPlayer::updateForPreDelete() {
    auto* body = _c0._8;
    if (!body)
        return true;
    return !body->isAddedToWorld();
}

}  // namespace uking::action
