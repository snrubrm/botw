#include "KingSystem/Physics/Constraint/physLimitHingeCs.h"
#include "KingSystem/Physics/Constraint/physConstraintCallbacks.h"

namespace ksys::phys {

LimitHingeCs::~LimitHingeCs() = default;

void LimitHingeCs::sub_7100F6E300(f32 angle) {
    mData->mMinAngle = angle;
    mData->mMaxAngle = angle;
}

void LimitHingeCs::sub_7100F6E314(f32 min_angle, f32 max_angle) {
    mData->mMinAngle = min_angle;
    mData->mMaxAngle = max_angle;
}

void LimitHingeCs::sub_7100F6E328(f32 torque) {
    mData->mMaxFrictionTorque = torque;
}

void LimitHingeCs::sub_7100F6E334(f32 tau_factor) {
    mData->mAngularLimitsTauFactor = tau_factor;
}

f32 LimitHingeCs::sub_7100F6E340() const {
    return mData->mMaxAngle;
}

f32 LimitHingeCs::sub_7100F6E34C() const {
    return mData->mMinAngle;
}

f32 LimitHingeCs::sub_7100F6E358() const {
    return mData->mAngularLimitsTauFactor;
}
Unk_71024f6420::~Unk_71024f6420() = default;

u32 sub_7100F6E2A0(bool breakable, bool extra) {
    return sub_7100F6ACF4(breakable) + (extra ? 0x240 : 0x210);
}

}  // namespace ksys::phys
