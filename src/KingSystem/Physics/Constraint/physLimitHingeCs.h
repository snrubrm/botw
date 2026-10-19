#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// 0x7100f6e06c allocates 0xc0 and installs vtable 0x71024f63f0 after
// constructing Constraint. The table has RTTI queries and two destructors.
class LimitHingeCs : public Constraint {
    SEAD_RTTI_OVERRIDE(LimitHingeCs, Constraint)
public:
    ~LimitHingeCs() override;

    // 0x7100f6e584: converts the six frame vectors and passes them to the Havok data at +0xb8.
    void sub_7100F6E584(const sead::Vector3f& a, const sead::Vector3f& b, const sead::Vector3f& c,
                        const sead::Vector3f& d, const sead::Vector3f& e, const sead::Vector3f& f);

    // 0x7100f6e300 .. 0x7100f6e358 (placeholder names): limit and friction accessors of the hinge data.
    void sub_7100F6E300(f32 angle);
    void sub_7100F6E314(f32 min_angle, f32 max_angle);
    void sub_7100F6E328(f32 torque);
    void sub_7100F6E334(f32 tau_factor);
    f32 sub_7100F6E340() const;
    f32 sub_7100F6E34C() const;
    f32 sub_7100F6E358() const;

private:
    // Placeholder: the library limited-hinge constraint data (factory and frame setter 0x7100f6e584 store
    // it here). Only the fields the accessors use are modelled; the names follow the Havok limited-hinge atoms.
    struct Data {
        u8 _0[0xe8];
        f32 mMaxFrictionTorque;
        u8 _ec[0xf8 - 0xec];
        f32 mMinAngle;
        f32 mMaxAngle;
        f32 mAngularLimitsTauFactor;
    };

    Data* mData;
};
KSYS_CHECK_SIZE_NX150(LimitHingeCs, 0xc0);

// The independent placement-link size query supplies false and true.
u32 sub_7100F6E2A0(bool breakable, bool extra);

}  // namespace ksys::phys
