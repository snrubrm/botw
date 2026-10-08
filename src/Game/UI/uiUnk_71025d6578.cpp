#include "Game/UI/uiUnkSingletons.h"
#include <math/seadMathCalcCommon.h>
#include "Game/UI/uiUtils.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/GameData/gdtSpecialFlagNames.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::ui {

s32 sub_7100A9B690();
s32 sub_7100A9B6B0();
bool sub_7100AA8F30();

inline u32 Unk_71025d6578::getCurrentHeartValue() const {
    if (_4a)
        return _4c;
    u32 value = sub_7100A9B690();
    if ((~_63 & 0xa) && sub_7100AA8F30()) {
        // getPlayerActor(nullptr) returns PlayerInfo's PlayerBase pointer.
        if (auto* player = static_cast<ksys::act::PlayerBase*>(getPlayerActor(nullptr)))
            value -= player->m321();
    }
    return value;
}

inline u32 Unk_71025d6578::getMaxHeartValue() const {
    if (_4a)
        return _50;
    u32 value = sub_7100A9B6B0();
    if ((~_63 & 0xa) && sub_7100AA8F30()) {
        if (auto* player = static_cast<ksys::act::PlayerBase*>(getPlayerActor(nullptr)))
            value -= player->m321();
    }
    return value;
}

inline u32 Unk_71025d6578::getExtraHeartValue() const {
    if (_4a)
        return _54;
    auto* player = static_cast<ksys::act::PlayerBase*>(getPlayerActor(nullptr));
    if (!player || ((~_63 & 0xa) && sub_7100AA8F30()))
        return 0;
    return player->m321();
}

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

// 0x710094b8d4: the adjusted maximum calculation is intentionally discarded;
// the final comparison uses a fresh raw maximum when the cache is inactive.
bool Unk_71025d6578::sub_710094B8D4() const {
    const u32 current = getCurrentHeartValue();
    getMaxHeartValue();
    return current == (_4a ? _50 : u32(sub_7100A9B6B0()));
}

// 0x710094b9a0
// NON_MATCHING: ceil calculation and cache/state store scheduling differ.
void Unk_71025d6578::sub_710094B9A0() {
    if (_4a)
        return;
    _4c = getCurrentHeartValue();
    _50 = getMaxHeartValue();
    const u32 extra = getExtraHeartValue();
    _2c = _4c;
    _30 = _50;
    _28 = u32(sead::Mathf::ceil(_50 * 0.25f)) >> 4;
    _54 = extra;
    _34 = extra;
    _3c = 13;
    _40 = 7;
    _44 = 0;
    _48 = 0;
    _49 = 0;
    _61 = 0;
    if (auto* mgr = eui::ScreenMgr::instance()) {
        if (auto* screen = sead::DynamicCast<ScreenMainScreen>(mgr->getScreen(ScreenId::MainScreen)))
            screen->sub_7100A1AB94();
    }
    _4a = 1;
}

// 0x7100949fbc
// NON_MATCHING: the final flag updates use different load/store scheduling and merge the zero store.
void Unk_71025d6578::sub_7100949FBC() {
    if (_61 & 2)
        return;
    _38 = 0;
    if (_61 & 8)
        return;
    const u32 current = getCurrentHeartValue();
    if (_61 & 1) {
        _38 |= 4;
        _61 &= ~1;
    }
    _2c = current;
    if (!_61)
        _2c += _58;
    u32 maximum = getMaxHeartValue();
    if (!_61)
        maximum += _5c;
    if (_30 != maximum) {
        _38 |= 0x40;
        _30 = maximum;
        _28 = u32(sead::Mathf::ceil(maximum * 0.25f)) >> 4;
    }
    _34 = getExtraHeartValue();
    if (!_61)
        _34 += _5c;
    if (current <= 4)
        _38 |= 1;
    else
        _3a = 0;
    if (_61) {
        if (_61 & 4) {
            _61 = (_61 & ~0xc) | 8;
            _38 |= 0x400;
        }
    } else {
        if (_58)
            _38 = _60 ? _38 | 0x180 : (_38 & ~0x180) | 0x80;
        _60 = 0;
    }
}

// 0x710094bd54
// NON_MATCHING: pending-delta arithmetic and flag-mask calculation scheduling differ.
void Unk_71025d6578::sub_710094BD54() {
    if (_61 & 0x10) {
        _61 &= ~0x10;
        sub_7100949FBC();
    }
    const s32 delta = _58;
    _4c += _58;
    _50 += _5c;
    _54 += _5c;
    _58 = 0;
    _5c = 0;
    _61 = delta ? _61 | 3 : (_61 & ~3) | 2;
    _38 &= _4c <= 4 ? u16(~0x180) : u16(~0x181);
    ksys::gdt::setS32ByKey(_4c - _54, ksys::gdt::flagname::CurrentHart(), false);
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

// 0x710094c0d4
u32 Unk_71025d6578::sub_710094C0D4(u32 value) const {
    if (!value)
        return 0;
    const u32 maximum = getMaxHeartValue();
    return _4c + value > maximum ? maximum - _4c : value;
}

// 0x710094bf98
// NON_MATCHING: the inlined maximum-increment limiter duplicates early-return branches.
void Unk_71025d6578::sub_710094BF98(u32 current_increment, u32 max_increment) {
    _5c = sub_710094C094(max_increment);
    _58 = sub_710094C0D4(current_increment);
    if (_54 && _5c)
        _5c -= _54;
    _58 += _5c;
    _60 = 1;
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

// 0x710094be40
bool Unk_71025d6578::sub_710094BE40() {
    if (!_61)
        return false;
    sub_710094BE84();
    _61 |= 0x10;
    return true;
}

// 0x710094be84
void Unk_71025d6578::sub_710094BE84() {
    _2c = getCurrentHeartValue();
    _30 = getMaxHeartValue();
    _34 = getExtraHeartValue();
    _61 = 0;
}

}  // namespace uking::ui
