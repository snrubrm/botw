#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/System/physHavokAI.h"

namespace ksys::phys {

NavMeshCharacter::~NavMeshCharacter() {
    finalize();
}

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

void NavMeshCharacter::sub_7100F7604C(f32 value) {
    _10->_78->_1c = value;
}

void NavMeshCharacter::sub_7100F7605C(f32 value) {
    _10->_78->_18 = value;
}

void NavMeshCharacter::sub_7100F7606C(u32 value) {
    _10->_16c = value;
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

void NavMeshCharacter::sub_7100F7D1B4(const NavMeshCharacter* other) {
    _a8[0] = other->_8->_98;
    _d0 = 1;
}

// NON_MATCHING: register allocation only (the original keeps the index in w8 and moves it to w0 in each
// return block; ours keeps it in w0)
s32 NavMeshCharacter::sub_7100F7D1CC(const NavMeshCharacter* other) {
    s32 result = -1;
    const s32 index = _d0.load();
    if (index <= 9) {
        _a8[index] = other->_8->_98;
        if (_d0.compareExchange(index, index + 1))
            result = index;
    }
    return result;
}

void NavMeshCharacter::sub_7100F7D298(s32 index, const NavMeshCharacter* other) {
    if (index < 0 || _d0.load() <= index)
        return;
    _a8[index] = other->_8->_98;
}

void NavMeshCharacter::sub_7100F75F3C(u8 value) {
    auto lock = sead::makeScopedLock(_1e0);
    _1d9 = value;
    _220 |= 8;
}

}  // namespace ksys::phys
