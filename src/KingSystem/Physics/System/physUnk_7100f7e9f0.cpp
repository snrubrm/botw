#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace ksys::phys {

// Separate translation unit: the original calls the constructor out of line from
// NavMeshCharacter::sub_7100F76078.
Unk_7100f7e9f0::Unk_7100f7e9f0() : _0(nullptr), _8(-1), _10(nullptr) {}

bool Unk_7100f7e9f0::sub_7100F7EB40() const {
    return _0 && _8 != -1;
}

}  // namespace ksys::phys
