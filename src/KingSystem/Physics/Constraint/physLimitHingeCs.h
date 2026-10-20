#pragma once

#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::phys {

class RigidBody;

// 0x7100f6e06c allocates 0xc0 and installs vtable 0x71024f63f0 after
// constructing Constraint. The table has RTTI queries and two destructors.
class LimitHingeCs : public Constraint {
    SEAD_RTTI_OVERRIDE(LimitHingeCs, Constraint)
public:
    // Layout read by the factory: a bool at +0x20, six frame vectors and four
    // limit scalars after the shared Constraint prefix.
    struct Param : Constraint::Param {
        // Defaults established before the body setup in ExtendedEntity::init (0x7100e63ba4).
        bool _20 = true;
        u8 _21[3];
        sead::Vector3f _24 = sead::Vector3f::zero;
        sead::Vector3f _30 = sead::Vector3f::zero;
        sead::Vector3f _3c = sead::Vector3f::ez;
        sead::Vector3f _48 = sead::Vector3f::ez;
        sead::Vector3f _54 = sead::Vector3f::ey;
        sead::Vector3f _60 = sead::Vector3f::ey;
        f32 _6c = -3.14159265358979323846f;
        f32 _70 = 3.14159265358979323846f;
        f32 _74 = 0;
        f32 _78 = 1;
    };
    static_assert(sizeof(Param) == 0x80);

    static LimitHingeCs* make(const Param& param, sead::Heap* heap);

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
        u8 _104[0x130 - 0x104];
    };
    static_assert(sizeof(Data) == 0x130);

    LimitHingeCs(hkpConstraintInstance* instance, RigidBody* body_a, RigidBody* body_b,
                 const u32& value, ConstraintUnk18* breakable, Data* data)
        : Constraint(instance, body_a, body_b, value, breakable), mData(data) {}

    Data* mData;
};
KSYS_CHECK_SIZE_NX150(LimitHingeCs, 0xc0);

// The independent placement-link size query supplies false and true.
u32 sub_7100F6E2A0(bool breakable, bool extra);

}  // namespace ksys::phys
