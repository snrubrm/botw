#include "KingSystem/Physics/Constraint/physLimitHingeCs.h"
#include "KingSystem/Physics/Constraint/physConstraintCallbacks.h"
#include "KingSystem/Physics/physConversions.h"

namespace ksys::phys {

// 0x71015f1e18: the Havok limited-hinge frame setter (declaration only).
void sub_71015F1E18(void* data, const hkVector4f& a, const hkVector4f& b, const hkVector4f& c,
                    const hkVector4f& d, const hkVector4f& e, const hkVector4f& f);

LimitHingeCs::~LimitHingeCs() = default;

void LimitHingeCs::sub_7100F6E584(const sead::Vector3f& a, const sead::Vector3f& b,
                                  const sead::Vector3f& c, const sead::Vector3f& d,
                                  const sead::Vector3f& e, const sead::Vector3f& f) {
    hkVector4f va;
    hkVector4f vb;
    hkVector4f vc;
    hkVector4f vd;
    hkVector4f ve;
    hkVector4f vf;
    loadFromVec3(&va, a);
    loadFromVec3(&vb, b);
    loadFromVec3(&vc, c);
    loadFromVec3(&vd, d);
    loadFromVec3(&ve, e);
    loadFromVec3(&vf, f);
    sub_71015F1E18(mData, va, vb, vc, vd, ve, vf);
}

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
