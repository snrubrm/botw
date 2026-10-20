#include "Game/UI/uiShopMgr.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// 0x7100982a44
bool UiShopMgr::sub_7100982A44(s32 state, NpcShopData* shop_data) {
    _d0 = shop_data;
    sub_71009821F0(state);
    return true;
}

// 0x7100982a60
bool UiShopMgr::sub_7100982A60(s32 state, s32 value) {
    _dc = value;
    sub_71009821F0(state);
    return true;
}

// NON_MATCHING: the original merges the state-9 and state-7/8 setColorChangeMaterialIndex calls into
// one block and duplicates the _38._70 tag check into both the state-10 and the other path (tail
// merging / duplication); ours keeps two calls and one shared tag check
// 0x7100982c90 (placeholder name): pushes the selected item to the shop facade.
void UiShopMgr::sub_7100982C90() {
    auto* info = ksys::act::InfoData::instance();
    shop::setSelectItemName(_38.name);
    shop::setSelectItemPrice(_38._60);
    shop::setSelectItemNum(_38._58);

    if (_30 != 10) {
        shop::setItemState(_38._68);
        if (_30 == 9) {
            if (info != nullptr) {
                _e0 = ksys::act::getItemStainColor(info, _38.name.cstr());
                shop::setColorChangeMaterialIndex(_e0);
            }
        } else if (u32(_30 - 7) < 2) {
            shop::setColorChangeMaterialIndex(_e0);
        } else if (_30 == 6) {
            sead::FixedSafeString<64> rank;
            if (*_38.name.cstr() != sead::SafeString::cNullChar)
                rank = ksys::act::getArmorNextRankName(info, _38.name.cstr());
            if (rank.isEmpty())
                ksys::gdt::resetFlag_GreatFairy_ArmorRank();
            else
                ksys::gdt::setFlag_GreatFairy_ArmorRank(
                    ksys::act::getArmorStarNum(info, rank.cstr()));
        }
    }

    if (_38._70 != nullptr && info != nullptr && _38._70->getType() == PouchItemType::Food) {
        if (info->hasTag(_38.name.cstr(), 0x30a3552e)) {
            const s32 effect = s32(sub_7100AA42AC(*_38._70));
            if (effect != -1) {
                ksys::gdt::setFlag_MsgDialogCookActorName(_38.name);
                ksys::gdt::setFlag_MsgDialogCookEffect(effect);
                return;
            }
        }
    }

    const s32 effect = ksys::gdt::getFlag_MsgDialogCookEffect();
    if (effect == -1)
        return;
    ksys::gdt::setFlag_MsgDialogCookActorName(sead::SafeString::cEmptyString);
    ksys::gdt::setFlag_MsgDialogCookEffect(-1);
}

// 0x7100982124 (placeholder name): shows the selected item's name on the shop info screen.
void UiShopMgr::sub_7100982124() {
    if (u32(_30 - 7) < 2) {
        if (auto* screen = sead::DynamicCast<ScreenShopInfo>(
                eui::ScreenMgr::instance()->getScreen(ScreenId::ShopInfo)))
            screen->sub_7100A525C8(_38.name, false);
    }
}

// 0x7100982a7c (placeholder name): fills the selected item and its state value.
bool UiShopMgr::sub_7100982A7C(s32 a1, const sead::SafeString& name, s32 price, s32 a2) {
    sub_71009821F0(a1);
    sub_7100A90938(_38.name, name);
    _38._60 = price;
    _38._64 = 0;
    _38._58 = 1;
    _38._5c = 0;
    _38._68 = sub_7100982B9C(_38);
    _e0 = a2;
    sub_7100982C90();

    s32 state = 4;
    if (auto* screen = sead::DynamicCast<ScreenShopInfo>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::ShopInfo))) {
        if (!screen->isClosed())
            state = 5;
    }
    _c0 = state;
    return true;
}

// 0x7100982b9c: the state value the shop menu shows for the selected item.
u32 UiShopMgr::sub_7100982B9C(const ShopItem& item) {
    if (_30 == 6)
        return sub_7100A91F64(item.name, item._60, _dc);
    if (_30 == 9)
        return 0;
    if (_30 == 10)
        return sub_7100A92180(item.name, item._58, _e0);

    if (u32(_30 - 0xb) <= 2)
        return item._6c == 0 ? 0 : 0xf;

    s32 type;
    if (u32(_30 - 3) < 2)
        type = 2;
    else
        type = u32(_30 - 5) < 2 || _30 == 8;

    if (_30 == 4 || _30 == 2) {
        const bool equipped = item._70 != nullptr && item._70->isEquipped();
        return sub_7100A91E84(item.name, type, item._58, equipped);
    }
    return sub_7100A90E40(item.name, item._60, type, item._58);
}

}  // namespace uking::ui
