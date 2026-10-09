#include "KingSystem/Physics/Constraint/physLimitHingeCs.h"
#include "KingSystem/Physics/Constraint/physConstraintCallbacks.h"

namespace ksys::phys {

LimitHingeCs::~LimitHingeCs() = default;
Unk_71024f6420::~Unk_71024f6420() = default;

u32 sub_7100F6E2A0(bool breakable, bool extra) {
    return sub_7100F6ACF4(breakable) + (extra ? 0x240 : 0x210);
}

}  // namespace ksys::phys
