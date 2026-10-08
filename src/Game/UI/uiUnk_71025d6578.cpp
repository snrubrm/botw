#include "Game/UI/uiUnkSingletons.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(Unk_71025d6578)

// D1 0x7100949ce0, D0 0x7100949ce4
Unk_71025d6578::~Unk_71025d6578() = default;

// NON_MATCHING: same flag updates; the original selects the first result into w8 (the register of the loaded byte)
// where clang uses another register, and swaps the csel operands of the second flag
// 0x710094b844: sets the flag pair (bits 2 / 3 if `a3`, else bits 0 / 1)
void Unk_71025d6578::sub_710094B844(bool a1, bool a2, bool a3) {
    if (a3) {
        _63 = a1 ? (_63 | 4) : (_63 & ~4);
        _63 = !a2 ? (_63 & ~8) : (_63 | 8);
    } else {
        _63 = a1 ? (_63 | 1) : (_63 & ~1);
        _63 = !a2 ? (_63 & ~2) : (_63 | 2);
    }
}

// NON_MATCHING: inlines sub_710094B844 above (same register differences)
// 0x710094b8a4: sets bit 0, rewrites bit 1 with its own value
void Unk_71025d6578::sub_710094B8A4(bool a1) {
    sub_710094B844(a1, (_63 & 2) != 0, false);
}

// 0x710094bcdc
// NON_MATCHING: state-store merging and ceil calculation scheduling differ.
void Unk_71025d6578::sub_710094BCDC() {
    if (!_4a)
        return;
    _3c = 13;
    _40 = 7;
    _44 = 0;
    _2c = _4c;
    _30 = _50;
    _34 = _54;
    _28 = u32(sead::Mathf::ceil(_50 * 0.25f)) >> 4;
    _58 = 0;
    _5c = 0;
    _48 = 0;
    _49 = 0;
    _4a = 0;
    _38 = _4c < 5;
}

// 0x710094c094
// NON_MATCHING: early-return branches are duplicated by the compiler.
u32 Unk_71025d6578::sub_710094C094(u32 value) const {
    if (value == 0)
        return 0;
    if (_54 > value)
        return 0;
    const u32 current = _50 - _54;
    if (current == 120)
        return 0;
    return current + value > 120 ? 120 - current : value;
}

// 0x710094be14
void Unk_71025d6578::sub_710094BE14() {
    if (_61 & 2)
        _61 = (_61 & ~6) | 4;
}

void Unk_71025d6578::sub_710094BE30() {
    if (!(_61 & 0x10))
        _61 = 0;
}

}  // namespace uking::ui
