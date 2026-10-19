#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

class hkpRackAndPinionConstraintData;

namespace ksys::phys {

// Whole factory 0x7100f70248 allocates 0xc0 and installs the four-slot
// vtable 0x71024f6610 after calling Constraint's constructor.
class RackAndPinionCs : public Constraint {
    SEAD_RTTI_OVERRIDE(RackAndPinionCs, Constraint)
public:
    // Factory 0x7100f70248 reads four vectors, then the pitch and the screw flag.
    struct Param : Constraint::Param {
        u8 _20[4];
        sead::Vector3f pivot_a = sead::Vector3f::zero;
        sead::Vector3f pivot_b = sead::Vector3f::zero;
        sead::Vector3f axis_a = sead::Vector3f::ez;
        sead::Vector3f axis_b = sead::Vector3f::ez;
        f32 pinion_radius_or_screw_pitch = 1.0f;
        bool is_screw = false;
    };

    static RackAndPinionCs* make(const Param& param, sead::Heap* heap);

    ~RackAndPinionCs() override;

private:
    RackAndPinionCs(hkpConstraintInstance* instance, RigidBody* body_a, RigidBody* body_b,
                    ConstraintUnk18* breakable, hkpRackAndPinionConstraintData* data)
        : Constraint(instance, body_a, body_b, 8, breakable), mData(data) {}

    hkpRackAndPinionConstraintData* mData;
};
KSYS_CHECK_SIZE_NX150(RackAndPinionCs, 0xc0);

u32 sub_7100F703FC(bool breakable, bool extra);

}  // namespace ksys::phys
