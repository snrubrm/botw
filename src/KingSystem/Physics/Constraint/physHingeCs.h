#pragma once

#include <math/seadVector.h>
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

class hkpHingeConstraintData;

namespace ksys::phys {

// 0x7100f6d9dc allocates 0xc0, calls Constraint's constructor and installs
// vtable 0x71024f63c0. Its four slots are RTTI queries and the two destructors.
class HingeCs : public Constraint {
    SEAD_RTTI_OVERRIDE(HingeCs, Constraint)
public:
    // Layout from HingeMagneFixedRigid::m32 (the only caller seen so far; lane3 s71): pivots and hinge axes in the
    // space of body_a / body_b.
    struct Param : Constraint::Param {
        bool _20 = true;
        sead::Vector3f pivot_a = sead::Vector3f::zero;
        sead::Vector3f pivot_b = sead::Vector3f::zero;
        sead::Vector3f axis_a = sead::Vector3f::ez;
        sead::Vector3f axis_b = sead::Vector3f::ez;
    };

    ~HingeCs() override;

    static HingeCs* make(const Param& param, sead::Heap* heap);

    // 0x7100f6deac (placeholder name): converts the four vectors to hkVector4 and passes them to
    // the Havok hinge data at +0xb8.
    void sub_7100F6DEAC(const sead::Vector3f& pivot_a, const sead::Vector3f& pivot_b,
                        const sead::Vector3f& axis_a, const sead::Vector3f& axis_b);

private:
    HingeCs(hkpConstraintInstance* instance, RigidBody* body_a, RigidBody* body_b,
            ConstraintUnk18* breakable, hkpHingeConstraintData* data)
        : Constraint(instance, body_a, body_b, 3, breakable), mData(data) {}

    // Factory F6D9DC stores the pointer used independently by F6DEAC.
    hkpHingeConstraintData* mData;
};
KSYS_CHECK_SIZE_NX150(HingeCs, 0xc0);

// 0x7100f6dc48 adds the hinge data extent to the shared allocation size.
u32 sub_7100F6DC48(bool breakable);

}  // namespace ksys::phys
