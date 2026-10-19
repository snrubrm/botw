#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

class hkpLimitedHingeConstraintData;

namespace ksys::phys {

// 0x7100f6e06c allocates 0xc0 and installs vtable 0x71024f63f0 after
// constructing Constraint. The table has RTTI queries and two destructors.
class LimitHingeCs : public Constraint {
    SEAD_RTTI_OVERRIDE(LimitHingeCs, Constraint)
public:
    // Factory 0x7100f6e06c reads six vectors and four scalars: the pivots and
    // two frame axes per body, then the angular limits and friction values.
    struct Param : Constraint::Param {
        bool _20 = false;
        u8 _21[3];
        sead::Vector3f pivot_a = sead::Vector3f::zero;
        sead::Vector3f pivot_b = sead::Vector3f::zero;
        sead::Vector3f axis_a = sead::Vector3f::ez;
        sead::Vector3f axis_b = sead::Vector3f::ez;
        sead::Vector3f axis_a2 = sead::Vector3f::ex;
        sead::Vector3f axis_b2 = sead::Vector3f::ex;
        f32 min_angle = 0.0f;
        f32 max_angle = 0.0f;
        f32 max_friction_torque = 0.0f;
        f32 angular_limits_tau_factor = 1.0f;
    };

    static LimitHingeCs* make(const Param& param, sead::Heap* heap);

    ~LimitHingeCs() override;

    // 0x7100f6e300 .. 0x7100f6e358 (placeholder names): limit and friction accessors of the hinge data.
    void sub_7100F6E300(f32 angle);
    void sub_7100F6E314(f32 min_angle, f32 max_angle);
    void sub_7100F6E328(f32 torque);
    void sub_7100F6E334(f32 tau_factor);
    f32 sub_7100F6E340() const;
    f32 sub_7100F6E34C() const;
    f32 sub_7100F6E358() const;

private:
    LimitHingeCs(hkpConstraintInstance* instance, RigidBody* body_a, RigidBody* body_b,
                 ConstraintUnk18* breakable, hkpLimitedHingeConstraintData* data)
        : Constraint(instance, body_a, body_b, 4, breakable), mData(data) {}

    // Factory and frame setter 0x7100f6e584 store the library limited-hinge data here.
    hkpLimitedHingeConstraintData* mData;
};
KSYS_CHECK_SIZE_NX150(LimitHingeCs, 0xc0);

// The independent placement-link size query supplies false and true.
u32 sub_7100F6E2A0(bool breakable, bool extra);

}  // namespace ksys::phys
