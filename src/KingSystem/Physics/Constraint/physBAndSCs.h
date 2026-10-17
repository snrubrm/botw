#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

class hkpBallAndSocketConstraintData;

namespace ksys::phys {

// Whole factory 0x7100f6af10 allocates 0xc0, calls Constraint's constructor,
// and installs the complete four-slot vtable at 0x71024f61f8.
class BAndSCs : public Constraint {
    SEAD_RTTI_OVERRIDE(BAndSCs, Constraint)
public:
    struct Param : Constraint::Param {
        // The factory does not consume this four-byte prefix before the pivots.
        u8 _20[4];
        sead::Vector3f pivot_a;
        sead::Vector3f pivot_b;
    };
    static BAndSCs* make(const Param& param, sead::Heap* heap);

    ~BAndSCs() override;

    void sub_7100F6B144(const sead::Vector3f& pivot_a, const sead::Vector3f& pivot_b);
    // 0x7100f6b198 (placeholder name): sets both pivots from one world-space pivot.
    void sub_7100F6B198(const sead::Matrix34f& body_a_mtx, const sead::Matrix34f& body_b_mtx,
                        const sead::Vector3f& pivot);
    // 0x7100f6b394 (placeholder name): reads back the two body-space pivots.
    void sub_7100F6B394(sead::Vector3f* pivot_a, sead::Vector3f* pivot_b) const;

private:
    BAndSCs(hkpConstraintInstance* instance, RigidBody* body_a, RigidBody* body_b,
             ConstraintUnk18* breakable, hkpBallAndSocketConstraintData* data)
        : Constraint(instance, body_a, body_b, 1, breakable), mData(data) {}

    // Full factory and independent body-space setter use this same library owner.
    hkpBallAndSocketConstraintData* mData;
};
KSYS_CHECK_SIZE_NX150(BAndSCs, 0xc0);

u32 sub_7100F6B100(bool breakable, bool extra);

}  // namespace ksys::phys
