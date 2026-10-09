#pragma once

#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

// Whole factories 0x7100f6c72c and 0x7100f6c904 allocate 0xc0, call
// Constraint's constructor and install the same four-slot vtable 0x71024f6360.
// Their CogWheelCs/MagnesisGearEmbedCs labels do not resolve this class's name.
class Unk_71024f6360 : public Constraint {
    SEAD_RTTI_OVERRIDE(Unk_71024f6360, Constraint)
public:
    ~Unk_71024f6360() override;

private:
    // Both factories store the library data pointer here; its interface is unresolved.
    u8 _b8[8];
};
KSYS_CHECK_SIZE_NX150(Unk_71024f6360, 0xc0);

u32 sub_7100F6CC8C(bool breakable);

}  // namespace ksys::phys
