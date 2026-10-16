#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/System/VFR.h"

// Own TU (0x710071a92c .. 0x710071bd38): Unk_7102450fa8's functions are called, not inlined, and the
// Unk_7102450fa8 TU ends with its static initialiser at 0x710071a7b4.

// NON_MATCHING: the free list head of _b0 is addressed through a register in the original (ours reloads this + 0xc0)
// and the clear loop is laid out differently.
Unk_7102450fe0::Unk_7102450fe0() {
    resetOrder();
    for (auto& entry : _8)
        entry.reset(0);
}

Unk_7102450fe0::~Unk_7102450fe0() = default;

// TODO
void Unk_7102450fe0::m5(s32 a8, f32 x, f32 y) {}

void Unk_7102450fe0::m8() {
    if (isFlagOn(Flag(Flag::_1)))
        return;
    sub_710071AECC();
}

// TODO
void Unk_7102450fe0::sub_710071AECC() {}

bool Unk_7102450fe0::m9(const ksys::Message& message) {
    if (!_178.m2(message))
        return false;

    auto& entry = _8[_a0->sub_71007195B0(_178._38.mLink) - 2];
    if (_178._38._0 == 5) {
        _1d0.setBit(Flag(Flag::_2));
        return true;
    }

    const s32 value = m11(entry._0)->_8;
    if (value == _178._38._0)
        entry._4 = value;
    if (_178._38._0 == 2)
        _1d0.resetBit(Flag(Flag::_0));
    return true;
}

void Unk_7102450fe0::sub_710071B37C(Unk_7102450fa8* unit) {
    _a0 = unit;
    _160 = sUnk_71025c8cf8;
}

// NON_MATCHING: the free list head of _b0 is addressed through a register in the original (ours reloads this + 0xc0).
void Unk_7102450fe0::m10() {
    resetOrder();
    for (u32 i = 0; i < 9; ++i) {
        const u32 j = sead::GlobalRandom::instance()->getU32(9);
        if (i != j && u32(_b0.size()) > i && u32(_b0.size()) > j)
            _b0.swap(i, j);
    }
}

const Unk_7102450fe0::State* Unk_7102450fe0::m11(Step step) {
    static const sead::SafeArray<State, 9> sStates = {{
        State(sub_710071B5EC, 0, 0, true, false),
        State(sub_710071B5EC, 1, 2, true, false),
        State(sub_710071B5EC, 2, 3, true, false),
        State(sub_710071B6A4, 0, 4, false, false),
        State(sub_710071B5EC, 3, 5, true, false),
        State(sub_710071B5EC, 0, 6, true, false),
        State(sub_710071B5EC, 4, 7, true, false),
        State(sub_710071B5EC, 0, 0, true, true),
        State(sub_710071B5EC, 0, 0, false, true),
    }};
    return &sStates[step];
}

void Unk_7102450fe0::sub_710071B5EC(Unk_7102450fe0* self, s32 idx) {
    auto& entry = self->_8[idx];
    if (entry._c)
        return;

    const State* state = self->m11(entry._0);
    if (entry._4 == state->_8) {
        entry._c = true;
        return;
    }

    ksys::act::ActorLinkConstDataAccess accessor;
    if (!self->_a0->sub_71007194D4(idx + 2, &accessor) || accessor.isStateSleep())
        entry._c = true;
}

void Unk_7102450fe0::sub_710071B6A4(Unk_7102450fe0* self, s32 idx) {
    auto& entry = self->_8[idx];
    if (entry._c)
        return;

    self->m11(entry._0);
    entry._8 += ksys::VFR::instance()->getDeltaTime();
    if (entry._8 >= self->_16c + self->_170 * *self->_b0(idx)) {
        entry._c = true;
        return;
    }

    ksys::act::ActorLinkConstDataAccess accessor;
    if (!self->_a0->sub_71007194D4(idx + 2, &accessor) || accessor.isStateSleep())
        entry._c = true;
}
