#include "Game/gameNpcShopData.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "Game/UI/uiShopMgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUI.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/gameRoot1.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/UIGlue.h"
#include <math/seadMathCalcCommon.h>

namespace uking::ui {

// 0x7100a96c68 / 0x7100a96d24 / 0x7100a97f80 (uiScreenFacade.cpp)
bool triggerRupeeCountScreen();
bool sub_7100A96D24();
bool sub_7100A97F80();

// The shop-state to screen-list table. The native TU initializer 0x7100985584 sets
// the buffer to these 16 entries (count 0x71025d7ca0, pointer 0x71025d7ca8).
static s32 sUnk_7102476ca0[] = {3, 1, 0, 1, 0, 1, 0, 3, 3, 2, 0, 1, 1, 1, 1, 3};
static sead::Buffer<s32> sUnk_71025d7ca0(sUnk_7102476ca0);

SEAD_SINGLETON_DISPOSER_IMPL(UiShopMgr)

// 0x7100980794 (inlined into createInstance) and 0x7102476d00 (vtable)
UiShopMgr::UiShopMgr() : mTransceiver(this) {}

// D1 0x7100980968, D0 0x71009809e0 (thunks at +8: 0x71009809a4 / 0x7100980a24)
UiShopMgr::~UiShopMgr() = default;

// 0x7100980a70
void UiShopMgr::initStubbed() {}

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

// The screen of each shop type (0: 20 buttons, 1: 5 buttons, 2: 15 buttons).
static const s32 sShopTypeScreens[] = {ScreenId::ShopBtnList20, ScreenId::ShopBtnList5,
                                       ScreenId::ShopBtnList15};

// 0x7100982f48: closes the button-list screen selected by `type` (the 15-button list is looked up
// in the table) and then the shop background screen. `this` is unused.
// NON_MATCHING: our build folds the type table's index (`sShopTypeScreens[type]`, type is known to be
// 2 there) to the constant screen id, so the 0x7101e7d8a8 table load is gone (149 vs 154 bytes), and
// it places the type-2 test before the type-0/1 tests instead of after them.
void UiShopMgr::sub_7100982F48(u8 type, bool set_flag) {
    if (type == 0) {
        if (auto* screen = sead::DynamicCast<ScreenShopBtnList20>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList20))) {
            if (set_flag)
                screen->_3864 = 1;
            screen->close(-1);
        }
    } else if (type == 1) {
        if (auto* screen = sead::DynamicCast<ScreenShopBtnList5>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList5))) {
            if (set_flag)
                screen->_3628 = 1;
            screen->close(-1);
        }
    } else if (type == 2) {
        if (auto* mgr = eui::ScreenMgr::instance()) {
            if (auto* screen = mgr->getScreen(sShopTypeScreens[type]))
                screen->close(-1);
        }
    }
    if (auto* screen = sead::DynamicCast<ScreenShopBG>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBG)))
        screen->close(-1);
}

// inline-only in the original; names are guesses. Their switches show up as the 0x20d3 / 0x201f
// bit masks over the states 1, 2, 5, 7, 8, 14 and 1 - 5, 14 in sub_71009816B0, and the 7/8 test is
// the `u32(state - 7) < 2` range check.
static bool isShopBuySellState(s32 state) {
    return u32(state - 7) < 2;
}

static bool isShopInfoState(s32 state) {
    switch (state) {
    case 1:
    case 2:
    case 5:
    case 7:
    case 8:
    case 14:
        return true;
    default:
        return false;
    }
}

static bool isShopInfoState2(s32 state) {
    switch (state) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 14:
        return true;
    default:
        return false;
    }
}

// 0x71009816b0
// NON_MATCHING: instruction set and size agree; the reset block's store order, the 7/8 range test
// encoding (cmp #1/b.ls vs cmp #2/b.lo) and register colours differ.
bool UiShopMgr::sub_71009816B0(s32 state, s32 a2) {
    if (_30 == 0)
        return false;
    if (isShopBuySellState(state)) {
        if (_30 != 7 && _30 != 8)
            return false;
    } else if (_30 != state) {
        return false;
    }
    const bool in_set = isShopInfoState(state);
    if (isShopBuySellState(state)) {
        if (in_set && sub_7100AA8F10() && !ksys::gdt::getFlag_IsOpenShopInfo_Demo())
            sub_7100A96D24();
    } else if (in_set) {
        triggerRupeeCountScreen();
    } else if (state == 3 || state == 4) {
        sub_7100A97F80();
    }
    if (isShopInfoState2(state)) {
        if (auto* root = Root1::instance())
            root->sub_7100899CA4(Root1::FlagIdx::_0, 2);
    }
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::ShopInfo))
        screen->close(-1);
    if (isShopBuySellState(state)) {
        _30 = 0;
        _38.name.clear();
        _38._58 = 0;
        _38._5c = 0;
        _38._60 = 0;
        _38._64 = 0;
        _38._68 = -1;
        _38._6c = 0;
        _38._70 = nullptr;
        _b0 = -1;
        _c0 = 3;
        _c7 = false;
        _d0 = nullptr;
        _d8 = 0;
        _dc = 0;
        _e0 = -1;
        return true;
    }
    sub_7100982F48(sUnk_71025d7ca0[_30], a2 & 1);
    _c0 = 2;
    return true;
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

// NON_MATCHING: the original reads the state table through the shop TU's static block at 0x71025d7b40
// (+0x160 / +0x168); ours references the buffer at 0x71025d7ca0 directly (same rows as sub_7100981888).
// 0x7100984ef8
void UiShopMgr::sub_7100984EF8() {
    if (_30 == 10) {
        shop::setItemState(9);
        sub_7100985134();
    }
    switch (sUnk_71025d7ca0[_30]) {
    case 0:
        if (auto* screen = sead::DynamicCast<ScreenShopBtnList20>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList20)))
            screen->sub_7100A4CC28(_30 == 10);
        break;
    case 1:
        if (auto* screen = sead::DynamicCast<ScreenShopBtnList5>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList5)))
            screen->sub_7100A4DEB0();
        break;
    default:
        if (auto* screen = sead::DynamicCast<ScreenShopBtnList15>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList15)))
            screen->sub_7100A4B2BC();
        break;
    }
    sub_7100981888(true, _b0);
    ksys::ui::sub_7100EDC5F0();
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

// 0x71009842f8: in the horse shop states (11 - 13), registers / changes the selected horse item with the horse
// manager, then sets _c7
void UiShopMgr::sub_71009842F8() {
    if (u32(_30 - 11) > 2)
        return;
    if (!_38.name.isEmpty() && _38._68 != 12) {
        if (auto* horse_mgr = HorseMgr::instance()) {
            if (_30 == 11)
                horse_mgr->sub_7100E87340(_38.name, ksys::act::ActorHeapUtil::instance()->getBaseProcHeap());
            else if (_30 == 12)
                horse_mgr->sub_7100E87424(_38.name, ksys::act::ActorHeapUtil::instance()->getBaseProcHeap());
            else
                horse_mgr->sub_7100E87508(_38.name, ksys::act::ActorHeapUtil::instance()->getBaseProcHeap());
        }
    }
    _c7 = true;
}

// 0x71009854fc
bool UiShopMgr::sub_71009854FC(ksys::act::BaseProc* proc) {
    return _140.acquire(proc, false);
}

// 0x7100985508
void UiShopMgr::sub_7100985508() {
    _140.reset();
}


// 0x7100985510
ShopItem::ShopItem() {}

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

// inline-only in the original; name is a guess (the same mask test is inlined here and in
// sub_71009852C0): the shop states of a carry action
static bool isCarryStateMaybe(s32 state) {
    switch (state) {
    case 9:
    case 11:
    case 12:
    case 13:
        return true;
    default:
        return false;
    }
}

// 0x7100985134
bool UiShopMgr::sub_7100985134() {
    PauseMenuDataMgr* data = PauseMenuDataMgr::instance();
    if (!data || data->isNothingBeingGrabbed())
        return false;
    data->unholdGrabbedItems();
    auto* screen = sead::DynamicCast<ScreenShopBtnList20>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::ShopBtnList20));
    if (!screen)
        return true;
    screen->sub_7100A4CD70();
    const s32 item_index = screen->sub_7100A4CE28();
    if (_c0 != 2) {
        if (_b4) {
            _b4 = false;
        } else {
            sub_7100983E48(item_index, _b0, &_38);
            sub_7100982C90();
            if (!isCarryStateMaybe(_30))
                sub_7100980F48(&_38);
            if (_30 == 11 || _30 == 12 || _30 == 13)
                _c7 = false;
        }
    }
    screen->sub_7100A4CC28(1);
    screen->sub_7100A4CE68(4);
    return true;
}

// 0x71009852c0
void UiShopMgr::sub_71009852C0(bool value) {
    s32 screen_type = ksys::gdt::getFlag_Shop_ScreenType(false);
    s32 num;
    if (value) {
        if (u32(screen_type - 7) < 2)
            num = ksys::gdt::getFlag_Shop_PlacedItemStockNum(false);
        else
            num = _38._58;
    } else {
        auto* ui = UI::instance();
        if (!ui) {
            num = 1;
        } else {
            const s32 trade_num = ui->getTradeItemNum();
            num = trade_num > 1 ? trade_num : 1;
        }
    }
    shop::setTradeItemNum(num);
    const s32 price = ksys::gdt::getFlag_Shop_SelectItemPrice(false) * num;
    shop::setTradePrice(price);
    switch (screen_type) {
    case 1:
    case 3:
    case 14:
        screen_type = _30;
        break;
    default:
        break;
    }
    switch (screen_type) {
    case 1:
    case 3:
    case 7:
    case 14: {
        s32 state = 0;
        if (num >= 2) {
            const char* name;
            ksys::gdt::getFlag_Shop_SelectItemName(&name, false);
            const s32 mode = (screen_type == 3) << 1;
            state = sub_7100A90FD8(sead::SafeString(name), price, mode, num);
        }
        ksys::gdt::setFlag_Shop_CurrentItemState(state, false);
        break;
    }
    default:
        break;
    }
}

// inline-only in the original; name is a guess (0x71009853F4 inlines this state membership test, which
// shows up as the 0x2515 bit mask over the states 1, 3, 5, 9, 11 and 14).
static bool isValidShopCallState(s32 state) {
    switch (state) {
    case 1:
    case 3:
    case 5:
    case 9:
    case 11:
    case 14:
        return true;
    default:
        return false;
    }
}

// 0x71009853f4
// NON_MATCHING: the membership test lowers to a shifted-mask compare (0x4a2a, ccmp) instead of the
// original's subtract-then-test form (sub #1, mask 0x2515, lsr, tbz); the rest matches.
bool UiShopMgr::sub_71009853F4() {
    if (!isValidShopCallState(_30))
        return false;
    NpcShopData* shop = _d0;
    if (!shop)
        return false;
    switch (_30) {
    case 1:
    case 3:
        if (_d8 < 1)
            return true;
        for (s32 i = 0; i < _d8; ++i) {
            if (shop->mItems[i].count > 0)
                return false;
        }
        return true;
    case 14:
        if (shop->mItems.size() < 1)
            return true;
        for (s32 i = 0; i < shop->mItems.size(); ++i) {
            if (sub_7100A98808(sub_7100A985DC(shop->mItems[i].name)) > 0)
                return false;
        }
        return true;
    default:
        return false;
    }
}

}  // namespace uking::ui
