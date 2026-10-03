#pragma once

#include <math/seadMatrix.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Physics/Constraint/physConstraint.h"

namespace sead {
class Heap;
}

namespace ksys::phys {

class RigidBody;

// Name from the CSV ("FixedCs::make", 0x7100f6d070): a fixed constraint between two rigid bodies
// (a Constraint subclass of size 0xc0 whose Havok constraint data is at +0xb8).
// TODO: incomplete (only what AI classes need).
class FixedCs : public Constraint {
    SEAD_RTTI_OVERRIDE(FixedCs, Constraint)
public:
    // Layout deduced from make() and its callers (all of which fill in exactly these defaults).
    struct Param {
        RigidBody* body_a = nullptr;
        RigidBody* body_b = nullptr;
        u64 _10 = 0;
        bool _18 = true;
        bool _19 = false;
        f32 _1c = 10.0f;
        bool _20 = true;
        // Frames of the constraint in the space of body_a / body_b.
        sead::Matrix34f mtx_a = sead::Matrix34f::ident;
        sead::Matrix34f mtx_b = sead::Matrix34f::ident;
    };

    ~FixedCs() override;

    static FixedCs* make(const Param& param, sead::Heap* heap);

    // 0x7100f6d6d8 (placeholder name): sets the frames in the space of body_a / body_b.
    void sub_7100F6D6D8(const sead::Matrix34f& mtx_a, const sead::Matrix34f& mtx_b);
};

}  // namespace ksys::phys
