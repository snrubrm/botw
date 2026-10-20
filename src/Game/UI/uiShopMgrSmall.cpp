#include "Game/UI/uiShopMgr.h"
#include "Game/gameHorseMgr.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ui {

// 0x7100984ee0
void UiShopMgr::sub_7100984EE0() {
    if (auto* mgr = HorseMgr::instance())
        mgr->sub_7100E875EC();
}

// 0x7100984be8: sells the selected item (states 2 / 4: for rupees / mon)
// NON_MATCHING: the original computes &_38 before the PauseMenuDataMgr call and keeps it in a callee-saved register
void UiShopMgr::sub_7100984BE8() {
    if (_38._68 != 0)
        return;
    if (_30 != 4 && _30 != 2)
        return;
    auto* data_mgr = PauseMenuDataMgr::instance();
    if (!data_mgr)
        return;

    const s32 count = sead::Mathi::max(ksys::gdt::getFlag_Shop_TradeItemNum(), 1);
    const s32 total = count * _38._60;
    if (_30 == 2)
        ksys::gdt::increaseFlag_CurrentRupee(total);
    else
        ksys::gdt::increaseFlag_CurrentMamo(total);
    data_mgr->sub_710097D250(_38._70, count);
    sub_7100A9127C(_30, _38.name, count);
    _c5 = true;
}

// 0x710098425c
// NON_MATCHING: the state compare is `hs` against 5 instead of `hi` against 4, and _30 is reloaded through a
// pre-indexed register (regalloc)
void UiShopMgr::sub_710098425C(s32 a1, s32 a2) {
    if (_c0 == 2)
        return;
    if (_b4) {
        const bool same = _b0 == a2;
        _b4 = false;
        if (same)
            return;
    }
    _b0 = a2;
    sub_7100983E48(a1, a2, &_38.name);
    sub_7100982C90();
    if (_30 != 9 && _30 != 11 && _30 != 12 && _30 != 13)
        sub_7100980F48(&_38.name);
    if (u32(_30 - 11) <= 2)
        _c7 = false;
}

// 0x71009854fc
bool UiShopMgr::sub_71009854FC(ksys::act::BaseProc* proc) {
    return _140.acquire(proc, false);
}

// 0x7100985508
void UiShopMgr::sub_7100985508() {
    _140.reset();
}

// One horse item name record (0x78 bytes): a fixed string and the two links / type the rider UI keeps.
// Constructed in bulk by 0x7100985584 (sinitHorseItemStrings).
struct HorseItemString {
    HorseItemString();

    sead::FixedSafeString<64> mName;
    /* 0x58 */ void* _58 = nullptr;
    /* 0x60 */ void* _60 = nullptr;
    /* 0x68 */ s32 _68 = -1;
    /* 0x6c */ u8 _6c = 0;
    u8 _6d[3];
    /* 0x70 */ void* _70 = nullptr;
};
KSYS_CHECK_SIZE_NX150(HorseItemString, 0x78);

// 0x7100985510
HorseItemString::HorseItemString() {}

}  // namespace uking::ui
