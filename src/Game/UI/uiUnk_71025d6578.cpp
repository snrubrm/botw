#include "Game/UI/uiUnkSingletons.h"

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
