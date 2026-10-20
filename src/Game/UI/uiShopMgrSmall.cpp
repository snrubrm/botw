#include "Game/gameNpcShopData.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "Game/UI/uiShopMgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/gameHorseMgr.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ui {

// The shop-state to screen-list table. The native TU initializer 0x7100985584 sets
// the buffer to these 16 entries (count 0x71025d7ca0, pointer 0x71025d7ca8).
static s32 sUnk_7102476ca0[] = {3, 1, 0, 1, 0, 1, 0, 3, 3, 2, 0, 1, 1, 1, 1, 3};
static sead::Buffer<s32> sUnk_71025d7ca0(sUnk_7102476ca0);

// 0x7100981888
// NON_MATCHING: the original merges the static buffer into the TU globals; branch layout also differs.
void UiShopMgr::sub_7100981888(bool value, s32 index) {
    _c8 = 0;
    _c6 = value;
    const s32 type = sUnk_71025d7ca0[_30];
    if (type == 0) {
        if (auto* screen = sead::DynamicCast<ScreenShopBtnList20>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList20)))
            screen->sub_7100A4CD5C(value);
    } else if (type == 2) {
        if (auto* screen = sead::DynamicCast<ScreenShopBtnList15>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList15))) {
            screen->sub_7100A4B0B4(value);
            if (index >= 0)
                screen->sub_7100A4B10C(index);
        }
    } else if (type == 1) {
        if (auto* screen = sead::DynamicCast<ScreenShopBtnList5>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList5)))
            screen->sub_7100A4E070(value);
    }
}

// 0x7100981fac
// NON_MATCHING: the original merges the static buffer into the TU globals; branch layout also differs.
void UiShopMgr::sub_7100981FAC() {
    const s32 type = sUnk_71025d7ca0[_30];
    if (type == 0) {
        if (auto* screen = sead::DynamicCast<ScreenShopBtnList20>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList20)))
            screen->sub_7100A4CD70();
    } else if (type == 1) {
        if (auto* screen = sead::DynamicCast<ScreenShopBtnList5>(eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList5)))
            screen->sub_7100A4E084();
    }
}

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

// Native 985584 initializes these four profile/default-name strings.
static sead::SafeString sUnk_71025d7cb0 = "HorseReins";
static sead::SafeString sUnk_71025d7cc0 = "HorseSaddle";
static sead::SafeString sUnk_71025d7cd0 = "GameRomHorseReins_00";
static sead::SafeString sUnk_71025d7ce0 = "GameRomHorseSaddle_00";

s32 sub_7100A82DE8(PouchCategory category);
const PouchItem* sub_7100A82E00(PouchCategory category, s32 index);

// 0x71009831b0
// NON_MATCHING: native shop-state dispatch, SafeString copies and register allocation differ.
bool UiShopMgr::sub_71009831B0(s32 index, ShopItem* item) {
    auto* info = ksys::act::InfoData::instance();
    auto* pouch = PauseMenuDataMgr::instance();
    bool npc_shop;
    switch (_30) {
    case 1: case 3: case 5: case 9: case 11: case 14:
        npc_shop = true;
        break;
    default:
        npc_shop = false;
        break;
    }
    const auto clear_item = [&] {
        item->name.clear();
        item->_58 = 0;
        item->_5c = 0;
        item->_60 = 0;
        item->_64 = 0;
        item->_68 = -1;
        item->_6c = 0;
        item->_70 = nullptr;
    };
    if (index < 0 || (npc_shop ? !_d0 : !pouch) || index >= _d8) {
        clear_item();
        return false;
    }
    switch (_30) {
    case 1: case 3: case 9: case 14: {
        item->name = _d0->mItems[index].name;
        item->_5c = 0;
        item->_64 = _30 == 3;
        item->_6c = 0;
        if (item->name.isEmpty())
            break;
        item->_60 = _d0->mItems[index].unitPrice;
        if (_30 == 14) {
            item->_58 = sub_7100A98808(sub_7100A985DC(item->name));
            if (_cc && item->name == _38.name) {
                const s32 count = ksys::gdt::getFlag_Shop_TradeItemNum();
                item->_58 = count <= item->_58 ? item->_58 - count : 0;
            }
        } else if (_30 == 9) {
            item->_58 = -1;
        } else {
            item->_58 = _d0->mItems[index].count;
            if (item->_58 < 1 && _d0->mItems[index]._40 >= 0)
                item->_58 = 0;
        }
        break;
    }
    case 5:
        item->name = _d0->mItems[index].name;
        item->_5c = 1;
        item->_64 = 0;
        item->_6c = 0;
        if (!item->name.isEmpty()) {
            item->_60 = info ? ksys::act::getItemCreatingPrice(info, item->name.cstr()) : 0;
            if (auto* mgr = PauseMenuDataMgr::instance())
                item->_58 = mgr->getItemCount(item->name, true);
        }
        break;
    case 11:
        item->name = _d0->mItems[index].name;
        item->_64 = 3;
        if (!item->name.isEmpty()) {
            item->_60 = 0;
            item->_58 = -1;
            item->_6c = item->name == _e8;
        }
        break;
    case 12: case 13:
        if (index == 0) {
            item->name = _30 == 12 ? sUnk_71025d7cd0 : sUnk_71025d7ce0;
        } else {
            sead::FixedSafeString<64> profile;
            profile = _30 == 12 ? sUnk_71025d7cb0 : sUnk_71025d7cc0;
            const s32 count = sub_7100A82DE8(PouchCategory::KeyItem);
            s32 match = 1;
            for (s32 i = 0; i < count; ++i) {
                const auto* candidate = sub_7100A82E00(PouchCategory::KeyItem, i);
                if (candidate && info) {
                    const char* candidate_profile = nullptr;
                    info->getActorProfile(&candidate_profile, candidate->getName().cstr());
                    if (candidate_profile && profile == candidate_profile) {
                        if (match == index) {
                            item->name = candidate->getName();
                            break;
                        }
                        ++match;
                    }
                }
            }
        }
        item->_64 = 3;
        if (!item->name.isEmpty()) {
            item->_60 = 0;
            item->_58 = -1;
            item->_6c = item->name == _e8;
        }
        break;
    }
    if (item->name.isEmpty()) {
        clear_item();
        return false;
    }
    if (item->_58 < 0) {
        item->_5c = 2;
        item->_58 = -1;
    }
    item->_68 = sub_7100982B9C(*item);
    return true;
}

}  // namespace uking::ui
