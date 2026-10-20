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

// 0x7100980f48
// NON_MATCHING: the state branches and currency/count lookup paths allocate registers differently.
void UiShopMgr::sub_7100980F48(ShopItem* item) {
    auto* info = ksys::act::InfoData::instance();
    auto* data_mgr = PauseMenuDataMgr::instance();
    if (!info || !data_mgr)
        return;
    if (item->_68 == 17 || item->_68 == -1) {
        if (auto* screen = sead::DynamicCast<ScreenShopInfo>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::ShopInfo)))
            screen->close(-1);
        return;
    }
    createAndLoadScreenIfNeededImpl(ScreenId::ShopInfo, nullptr);
    auto* screen = sead::DynamicCast<ScreenShopInfo>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::ShopInfo));
    if (!screen)
        return;
    screen->sub_7100A52358(item->_68 == 0);
    switch (_30) {
    case 1:
    case 3: {
        screen->sub_7100A5233C(1);
        screen->sub_7100A5237C(item->name, true, -1);
        screen->sub_7100A525C8(item->name, false);
        screen->sub_7100A52DB0(0, item->name);
        s32 currency;
        s32 mode;
        if (_30 == 3) {
            currency = ksys::gdt::getFlag_CurrentMamo(false);
            mode = 2;
        } else {
            currency = ksys::gdt::getFlag_CurrentRupee(false);
            mode = 0;
        }
        screen->sub_7100A52C88(mode, item->_60,
                             currency < item->_60 ? 1 : item->_68 == 1 ? 3 : 0);
        s32 owned;
        if (sub_7100A82E28(s32(PauseMenuDataMgr::getType(item->name))))
            owned = data_mgr->countArmors(item->name);
        else
            owned = PauseMenuDataMgr::instance()->getItemCount(item->name, true);
        screen->setPorchNumText(owned);
        break;
    }
    case 2:
    case 4:
        screen->sub_7100A5233C(2);
        screen->sub_7100A524B0(item->_70, false);
        screen->sub_7100A527CC(item->_70);
        screen->sub_7100A52DB0(0, item->name);
        if (info->hasTag(item->name.cstr(), 0x9b44906f))
            screen->setPorchNumText(item->_70->getValue());
        else
            screen->hidePorchNum();
        if (item->_68 == 13)
            screen->setShopInfoSubTextPartsStateFrame2();
        else
            screen->sub_7100A52C88(_30 == 4 ? 2 : 0, item->_60, item->_68 == 0 ? 0 : 3);
        break;
    case 5: {
        screen->sub_7100A5233C(1);
        screen->sub_7100A5237C(item->name, true, -1);
        screen->sub_7100A525C8(item->name, false);
        screen->sub_7100A52DB0(1, item->name);
        const s32 price = item->_60;
        const s32 currency = ksys::gdt::getFlag_CurrentRupee(false);
        screen->sub_7100A52C88(1, item->_60, currency < price ? 1 : 0);
        s32 owned;
        if (sub_7100A82E28(s32(PauseMenuDataMgr::getType(item->name))))
            owned = data_mgr->countArmors(item->name);
        else
            owned = PauseMenuDataMgr::instance()->getItemCount(item->name, true);
        screen->setPorchNumText(owned);
        break;
    }
    case 6:
        screen->sub_7100A5233C(2);
        screen->sub_7100A524B0(item->_70, true);
        screen->hidePorchNum();
        screen->setShopInfoSubTextPartsStateFrame2();
        if (item->_68 == 5 || item->_68 == 4) {
            screen->sub_7100A52DB0(item->_68 == 5 ? 3 : 2, item->name);
            screen->sub_7100A52A04(item->_70, false);
        } else {
            sead::FixedSafeString<64> next_name;
            next_name = ksys::act::getArmorNextRankName(info, item->name.cstr());
            screen->sub_7100A531D8(next_name, item->_70->getValue());
            screen->sub_7100A52A04(item->_70, true);
        }
        break;
    case 7:
    case 8: {
        screen->sub_7100A5233C(0);
        screen->sub_7100A5237C(item->name, true, _e0);
        screen->sub_7100A525C8(item->name, false);
        const s32 currency = ksys::gdt::getFlag_CurrentRupee(false);
        const s32 mode = _30 == 8 ? 1 : 0;
        screen->sub_7100A52DB0(mode, item->name);
        screen->sub_7100A52C88(mode, item->_60, currency < item->_60 ? 1 : 0);
        s32 owned;
        if (sub_7100A82E28(s32(PauseMenuDataMgr::getType(item->name))))
            owned = data_mgr->countArmors(item->name);
        else
            owned = data_mgr->getItemCount(item->name, true);
        screen->setPorchNumText(owned);
        break;
    }
    case 10:
    case 12:
    case 13:
        screen->sub_7100A5233C(3);
        screen->sub_7100A527CC(item->_70);
        screen->sub_7100A52DB0(0, item->name);
        screen->setShopInfoSubTextPartsStateFrame2();
        if (_30 == 10) {
            auto* mgr = PauseMenuDataMgr::instance();
            screen->sub_7100A53328(mgr ? mgr->getNextGrabbedItemIndex() : 0);
        }
        break;
    case 14: {
        screen->sub_7100A5233C(1);
        screen->sub_7100A5237C(item->name, true, -1);
        screen->sub_7100A525C8(item->name, false);
        screen->sub_7100A52DB0(0, item->name);
        screen->hidePorchNum();
        const s32 price = item->_60;
        const s32 currency = ksys::gdt::getFlag_CurrentRupee(false);
        screen->sub_7100A52C88(0, item->_60,
                             currency < price ? 1 : item->_68 == 1 ? 3 : 0);
        break;
    }
    }
    if (screen->isClosed() || screen->isClosedOrClosing())
        screen->open(1);
}

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
    sub_7100983E48(a1, a2, &_38);
    sub_7100982C90();
    if (_30 != 9 && _30 != 11 && _30 != 12 && _30 != 13)
        sub_7100980F48(&_38);
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

PouchCategory sub_7100A82CF0(PouchItemType type);

// 0x7100983e48
// NON_MATCHING: native record copies and price-selection branch scheduling differ.
bool UiShopMgr::sub_7100983E48(s32 category, s32 index, ShopItem* item) {
    const auto* source = sub_7100A82E00(PouchCategory(category), index);
    if (!source) {
        item->name.clear();
        item->_58 = 0;
        item->_5c = 0;
        item->_60 = 0;
        item->_64 = 0;
        item->_6c = 0;
        item->_70 = nullptr;
        item->_68 = -1;
        return false;
    }
    // The inventory owns mutable items; this record retains the item for sell/remove operations.
    item->_70 = const_cast<PouchItem*>(source);
    auto* info = ksys::act::InfoData::instance();
    const PouchCategory item_category = sub_7100A82CF0(source->getType());
    item->name = source->getName();
    item->_58 = 0;
    if (info && item->_70->isInInventory())
        item->_58 = info->hasTag(item->name.cstr(), 0x9b44906f) ? source->getValue() : 1;
    item->_5c = 1;
    if (_30 == 6) {
        item->_64 = 2;
        if (item_category == PouchCategory::Armor) {
            ArmorInfo armor;
            getArmorInfoMaybe(item->name, &armor);
            item->_60 = armor.star_num;
        }
    } else if (_30 == 4) {
        item->_64 = 1;
        item->_60 = info ? ksys::act::getMonsterShopSellMamo(info, item->name.cstr()) : 0;
    } else if (_30 == 2) {
        item->_64 = 0;
        if (!info)
            item->_60 = 0;
        else if (info->hasTag(item->name.cstr(), 0x30a3552e))
            item->_60 = source->getCookData().mSellPrice;
        else
            item->_60 = ksys::act::getItemSellingPrice(info, item->name.cstr());
    }
    if (!item->_6c)
        item->_6c = source->isEquipped();
    item->_68 = sub_7100982B9C(*item);
    return true;
}

// 0x710098411c
// NON_MATCHING: native shop-state dispatch and selected-record scheduling differ.
void UiShopMgr::sub_710098411C(s32 value) {
    if (_c0 == 2)
        return;
    if (_b4) {
        _b4 = false;
        if (_b0 == value)
            return;
    }
    _b0 = value;
    sub_71009831B0(value, &_38);
    sub_7100982C90();
    if (_30 == 9) {
        if (auto* screen = sead::DynamicCast<ScreenShopBtnList15>(
                    eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList15)))
            screen->sub_7100A4B50C(_38.name);
    } else if (_30 != 11 && _30 != 12 && _30 != 13) {
        sub_7100980F48(&_38);
    }
    if (u32(_30 - 11) < 3)
        _c7 = false;
}

}  // namespace uking::ui
