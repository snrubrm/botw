#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// 0x7100f6d9dc allocates 0xc0, calls Constraint's constructor and installs
// vtable 0x71024f63c0. Its four slots are RTTI queries and the two destructors.
class HingeCs : public Constraint {
    SEAD_RTTI_OVERRIDE(HingeCs, Constraint)
public:
    ~HingeCs() override;

private:
    // The factory and frame setters establish a data pointer here, but its
    // library interface remains unresolved.
    u8 _b8[8];
};
KSYS_CHECK_SIZE_NX150(HingeCs, 0xc0);

// 0x7100f6dc48 adds the hinge data extent to the shared allocation size.
u32 sub_7100F6DC48(bool breakable);

}  // namespace ksys::phys
