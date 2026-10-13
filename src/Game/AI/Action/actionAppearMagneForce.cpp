#include "Game/AI/Action/actionAppearMagneForce.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace uking::action {

AppearMagneForce::AppearMagneForce(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearMagneForce::~AppearMagneForce() = default;

bool AppearMagneForce::init_(sead::Heap* heap) {
    _138 = _d0;
    return true;
}

void AppearMagneForce::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AppearMagneForce::leave_() {
    ksys::act::ai::Action::leave_();
}

void AppearMagneForce::loadParams_() {
    getStaticParam(&mMaxMagneForceRange_s, "MaxMagneForceRange");
    getStaticParam(&mMinMagneForceRange_s, "MinMagneForceRange");
    getStaticParam(&mMagneControlSpeed_s, "MagneControlSpeed");
    getStaticParam(&mMagneForceRadius_s, "MagneForceRadius");
    getStaticParam(&mMagneForceDamp_s, "MagneForceDamp");
    getStaticParam(&mMagneForceVelRate_s, "MagneForceVelRate");
    getStaticParam(&mObjectTerror_s, "ObjectTerror");
    getStaticParam(&mMagneShootSpeed_s, "MagneShootSpeed");
    getStaticParam(&mMagneControlRotateSpeed_s, "MagneControlRotateSpeed");
    getStaticParam(&mMagneControlUpDownSpeed_s, "MagneControlUpDownSpeed");
    getStaticParam(&mResistanceSpeedScale_s, "ResistanceSpeedScale");
    getStaticParam(&mMaxMagneHeight_s, "MaxMagneHeight");
    getStaticParam(&mCancelAngle_s, "CancelAngle");
    getStaticParam(&mCancelHeight_s, "CancelHeight");
    getStaticParam(&mCancelAngleFixed_s, "CancelAngleFixed");
    getStaticParam(&mCancelHeightFixed_s, "CancelHeightFixed");
    getStaticParam(&mGyroUpDownSpeed_s, "GyroUpDownSpeed");
    getStaticParam(&mGyroRotateSpeed_s, "GyroRotateSpeed");
}

void AppearMagneForce::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action

// NON_MATCHING: placeholder destructor; the original (0x710009c5b4) also destroys members or bases
// this class does not declare yet.
Unk_7102366538::~Unk_7102366538() = default;
