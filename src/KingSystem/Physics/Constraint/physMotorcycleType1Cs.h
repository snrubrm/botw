#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

class hkpGenericConstraintData;

namespace ksys::phys {

// Whole factory 0x7100f6ecec allocates 0xc0, calls Constraint's constructor,
// and installs the complete four-slot vtable at 0x71024f6568.
class MotorcycleType1Cs : public Constraint {
    SEAD_RTTI_OVERRIDE(MotorcycleType1Cs, Constraint)
public:
    struct Param : Constraint::Param {};

    static MotorcycleType1Cs* make(const Param& param, sead::Heap* heap);

    ~MotorcycleType1Cs() override;

    // 0x7100f6f1b4 (placeholder name): stores `value` at 0xb4 of the constraint data.
    void sub_7100F6F1B4(f32 value);

private:
    MotorcycleType1Cs(hkpConstraintInstance* instance, RigidBody* body_a, RigidBody* body_b,
                      ConstraintUnk18* breakable, hkpGenericConstraintData* data)
        : Constraint(instance, body_a, body_b, 9, breakable), mData(data) {}

    hkpGenericConstraintData* mData;
};
KSYS_CHECK_SIZE_NX150(MotorcycleType1Cs, 0xc0);

}  // namespace ksys::phys
