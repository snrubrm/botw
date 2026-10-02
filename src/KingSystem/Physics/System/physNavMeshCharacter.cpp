#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <prim/seadScopedLock.h>

namespace ksys::phys {

Unk_7100f7e9f0::Unk_7100f7e9f0() : _0(nullptr), _8(-1), _10(nullptr) {}

bool Unk_7100f7e9f0::sub_7100F7EB40() const {
    return _0 && _8 != -1;
}

void NavMeshCharacter::sub_7100F76778() {
    _220 |= 0x4000;
}

void NavMeshCharacter::sub_7100F76790() {
    _220 |= 0x8000;
}

void NavMeshCharacter::sub_7100F7D350() {
    _d0 = 0;
}

void NavMeshCharacter::sub_7100F75F3C(u8 value) {
    auto lock = sead::makeScopedLock(_1e0);
    _1d9 = value;
    _220 |= 8;
}

}  // namespace ksys::phys
