#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/System/physHavokAI.h"

namespace ksys::phys {

void NavMeshCharacter::sub_7100F75AB8() {
    if (_2e0) {
        HavokAI::instance()->sub_7100F83A94(_2e0);
        _2e0 = nullptr;
    }
}

Unk_7100f7e9f0 NavMeshCharacter::sub_7100F76078(sead::Vector3f* out, const sead::Vector3f& to,
                                                f32 a3) {
    if (to.isNan())
        return Unk_7100f7e9f0();

    auto* ai = _18 ? _18 : HavokAI::instance();
    return ai->sub_7100F88B1C(this, out, to, a3);
}

void NavMeshCharacter::sub_7100F76314() {
    _220 |= 0x20000;
    _220 &= ~0x2000u;
}

void NavMeshCharacter::sub_7100F7D2C8() {
    s32 value = _d0.load();
    while (value >= 1) {
        if (_d0.compareExchange(value, value - 1))
            break;
        value = _d0.load();
    }
}

// NON_MATCHING: the original hoists a zero-extension of `expected` (and x9, x1, #0xffffffff) out of the
// compare-exchange loop and rotates the loop so that a failed exchange jumps straight back to ldxr
void NavMeshCharacter::sub_7100F7D308(s32 expected) {
    while (true) {
        const s32 value = _d0.load();
        if (value < 1 || value - 1 != expected)
            return;
        if (_d0.compareExchange(value, expected))
            return;
    }
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
