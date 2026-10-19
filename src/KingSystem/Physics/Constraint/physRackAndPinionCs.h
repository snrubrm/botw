#pragma once

#include <Havok/Physics/Constraint/Data/hkpConstraintData.h>
#include <math/seadVector.h>
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::phys {

class RigidBody;

// Whole factory 0x7100f70248 allocates 0xc0 and installs the four-slot
// vtable 0x71024f6610 after calling Constraint's constructor.
class RackAndPinionCs : public Constraint {
    SEAD_RTTI_OVERRIDE(RackAndPinionCs, Constraint)
public:
    // Layout read by the factory: four vectors and a scalar/flag pair after the
    // shared Constraint prefix.
    struct Param : Constraint::Param {
        u8 _20[4];
        sead::Vector3f _24;
        sead::Vector3f _30;
        sead::Vector3f _3c;
        sead::Vector3f _48;
        f32 _54;
        bool _58;
    };
    static_assert(sizeof(Param) == 0x60);

    static RackAndPinionCs* make(const Param& param, sead::Heap* heap);

    ~RackAndPinionCs() override;

private:
    RackAndPinionCs(hkpConstraintInstance* instance, RigidBody* body_a, RigidBody* body_b,
                    const u32& value, ConstraintUnk18* breakable, hkpConstraintData* data)
        : Constraint(instance, body_a, body_b, value, breakable), mData(data) {}

    // The factory stores its library data pointer here; that interface
    // remains unresolved.
    hkpConstraintData* mData;
};
KSYS_CHECK_SIZE_NX150(RackAndPinionCs, 0xc0);

u32 sub_7100F703FC(bool breakable, bool extra);

}  // namespace ksys::phys
