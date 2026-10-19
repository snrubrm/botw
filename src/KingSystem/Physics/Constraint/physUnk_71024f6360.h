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

// Whole factories 0x7100f6c72c and 0x7100f6c904 allocate 0xc0, call
// Constraint's constructor and install the same four-slot vtable 0x71024f6360.
// Their CogWheelCs/MagnesisGearEmbedCs labels do not resolve this class's name.
class Unk_71024f6360 : public Constraint {
    SEAD_RTTI_OVERRIDE(Unk_71024f6360, Constraint)
public:
    // Layout read by the CogWheel factory: four frame vectors and two scalars after
    // the shared Constraint prefix (the 0x20 word is not read by the factory).
    struct Param : Constraint::Param {
        u8 _20[4];
        sead::Vector3f _24;
        sead::Vector3f _30;
        sead::Vector3f _3c;
        sead::Vector3f _48;
        f32 _54;
        f32 _58;
    };
    static_assert(sizeof(Param) == 0x60);

    // 0x7100f6c72c: the cog-wheel factory.
    static Unk_71024f6360* make(const Param& param, sead::Heap* heap);

    ~Unk_71024f6360() override;

private:
    Unk_71024f6360(hkpConstraintInstance* instance, RigidBody* body_a, RigidBody* body_b,
                   const u32& value, ConstraintUnk18* breakable, hkpConstraintData* data)
        : Constraint(instance, body_a, body_b, value, breakable), mData(data) {}

    // Both factories store the library data pointer here; its interface is unresolved.
    hkpConstraintData* mData;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f6360, 0xc0);

u32 sub_7100F6CC8C(bool breakable, bool extra);

}  // namespace ksys::phys
