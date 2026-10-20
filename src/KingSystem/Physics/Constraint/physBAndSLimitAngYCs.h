#pragma once

#include <Havok/Physics/Constraint/Atom/hkpConstraintAtom.h>
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Whole factory 0x7100f6b918 allocates 0xc0, calls Constraint's constructor,
// and installs the complete four-slot vtable at 0x71024f6310.
class BAndSLimitAngYCs : public Constraint {
    SEAD_RTTI_OVERRIDE(BAndSLimitAngYCs, Constraint)
public:
    ~BAndSLimitAngYCs() override;

    // 0x7100f6bd8c: installs both local constraint frames.
    void sub_7100F6BD8C(const sead::Matrix34f& a, const sead::Matrix34f& b);

    // 0x7100f6c280: reconstructs the two local constraint-frame matrices.
    void sub_7100F6C280(sead::Matrix34f* a, sead::Matrix34f* b) const;

    // 0x7100f6c254 (placeholder name): reads back the translations of the two local transforms.
    void sub_7100F6C254(sead::Vector3f* pivot_a, sead::Vector3f* pivot_b) const;

private:
    // Placeholder: the 0xe0-byte library constraint data the factory stores at _b8 (only the local
    // transforms atom at 0x20 is modelled; its class is unresolved).
    struct Data {
        u8 _0[0x20];
        hkpSetLocalTransformsConstraintAtom m_transforms;
    };

    Data* mData;
};
KSYS_CHECK_SIZE_NX150(BAndSLimitAngYCs, 0xc0);

u32 sub_7100F6BD48(bool breakable, bool extra);

}  // namespace ksys::phys
