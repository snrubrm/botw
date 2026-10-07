#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/System/physHavokAI.h"

namespace ksys::phys {

const f32 sUnk_7101ec27f4 = 1000000.0f;

// Counter at 0x710260ddd8 (placeholder name; used for the request ids stored in NavMeshCharacter::_290).
sead::Atomic<u32> sUnk_710260ddd8;

NavMeshCharacter::~NavMeshCharacter() {
    finalize();
}

void NavMeshCharacter::sub_7100F75AB8() {
    if (_2e0) {
        HavokAI::instance()->sub_7100F83A94(_2e0);
        _2e0 = nullptr;
    }
}

void NavMeshCharacter::sub_7100F75F8C(const sead::Vector3f& target) {
    auto lock = sead::makeScopedLock(_1e0);
    if (target.isNan())
        return;

    _d4.x = target.x;
    _d4.y = target.y;
    _d4.z = target.z;
    _1da = 1;
    if (!(_220.fetchOr(0x1000) & 0x1000))
        _290 = sUnk_710260ddd8.fetchAdd(1);
}

void NavMeshCharacter::sub_7100F75AF0() {
    if (_2e0)
        HavokAI::instance()->sub_7100F83A9C(_2e0);
}

// NON_MATCHING: the original loads `_18` before the singleton pointer (instruction order of the two loads)
Unk_7100f7e9f0 NavMeshCharacter::sub_7100F760F0(sead::Vector3f* out, const sead::Vector3f& to) {
    if (to.isNan())
        return Unk_7100f7e9f0();

    auto* ai = _18 ? _18 : HavokAI::instance();
    return ai->sub_7100F88FD0(this, out, to);
}

bool NavMeshCharacter::sub_7100F76168(f32 value, bool flag, void* out) {
    if (sead::Mathf::isNan(value))
        return false;

    auto* ai = _18 ? _18 : HavokAI::instance();
    return ai->sub_7100F87594(this, nullptr, getRadiusMaybe(), value, flag, out);
}

bool NavMeshCharacter::sub_7100F761C8(const sead::Vector3f& pos, f32 value, bool flag, void* out) {
    if (pos.isNan() || sead::Mathf::isNan(value))
        return false;

    auto* ai = _18 ? _18 : HavokAI::instance();
    return ai->sub_7100F87594(this, &pos, getRadiusMaybe(), value, flag, out);
}

void NavMeshCharacter::sub_7100F76260(const sead::Vector3f& pos) {
    auto lock = sead::makeScopedLock(_1e0);
    if (pos.isNan())
        return;
    _1b8.x = pos.x;
    _1b8.y = pos.y;
    _1b8.z = pos.z;
    _220 |= 0x2000;
    _220 &= ~0x20000u;
}

// NON_MATCHING: the original builds the mask from a stack temporary (`1 << bit`) and branches on `on`; ours is a csel
void NavMeshCharacter::sub_7100F76344(bool on) {
    _10->_170.changeBit(1, on);
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

void NavMeshCharacter::sub_7100F765E8(const sead::Vector3f& pos) {
    if (pos.isNan())
        return;

    auto lock = sead::makeScopedLock(_1e0);
    _254.x = pos.x;
    _254.y = pos.y;
    _254.z = pos.z;
    _220 |= 4;
}

void NavMeshCharacter::sub_7100F76694(const sead::Vector3f& direction) {
    if (direction.isNan())
        return;

    sead::Vector3f dir(direction.x, 0.0f, direction.z);
    if (dir.normalize() != 0.0f) {
        _260 = dir;
        _248 = dir;
    }
}

void NavMeshCharacter::sub_7100F76380(const sead::Vector3f& pos, const sead::Vector3f& dir_a,
                                      const sead::Vector3f& vec, const sead::Vector3f& dir_b) {
    sub_7100F765E8(pos);

    if (!dir_a.isNan()) {
        sead::Vector3f dir(dir_a.x, 0.0f, dir_a.z);
        if (dir.normalize() != 0.0f)
            _260 = dir;
    }

    if (!vec.isNan()) {
        _26c.x = vec.x;
        _26c.y = vec.y;
        _26c.z = vec.z;
    }

    if (!dir_b.isNan()) {
        sead::Vector3f dir(dir_b.x, 0.0f, dir_b.z);
        if (dir.normalize() != 0.0f)
            _278 = dir;
    }
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
