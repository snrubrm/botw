#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiTUStatics.h"
#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTagProcessor.h"
#include "Game/UI/uiUI.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

}  // namespace uking::ui

namespace uking::ui {

// 0x7100a23ed8 (CSV eui::LayoutEx::findPane<TextBoxEx>; the body is an out-of-line DynamicCast of a tag processor to
// the game's TagProcessor, placeholder name)
TagProcessor* sub_7100A23ED8(nn::font::TagProcessorBase<u16>* processor) {
    return nn::font::DynamicCast<TagProcessor>(processor);
}

// 0x7100a233ec
ScreenChild* sub_7100A233EC(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247a6d8(layout_ex);
}

}  // namespace uking::ui

namespace uking::ui {

// 0x71025ef948: the MessageGet_00 screen's icon panes, indexed by the icon id the lookup below maps.
struct MessageGetIcon {
    s32 id;
    sead::SafeString pane;
};
static MessageGetIcon sUnk_71025ef948[14] = {
    {0, "Pa_IconKagoG_00"},
    {1, "Pa_IconKagoR_00"},
    {2, "Pa_IconKagoY_00"},
    {3, "Pa_IconKagoB_00"},
    {4, "Pa_IconDungeonClear_00"},
    {5, "Pa_IconWarpDLC_00"},
    {6, "PaIconDLCAkashiG_00"},
    {7, "PaIconDLCAkashiR_00"},
    {8, "PaIconDLCAkashiY_00"},
    {9, "PaIconDLCAkashiB_00"},
    {10, "Pa_IconDLCKagoG_00"},
    {11, "Pa_IconDLCKagoR_00"},
    {12, "Pa_IconDLCKagoY_00"},
    {13, "Pa_IconDLCKagoB_00"},
};
static sead::Buffer<MessageGetIcon> sUnk_71025ef938(sUnk_71025ef948);

// 0x7100a25474 (placeholder name): the icon table index of `id`, -1 when the icon is not listed.
s32 sub_7100A25474(s32 id) {
    for (s32 i = 0; i < 14; ++i) {
        if (sUnk_71025ef938[i].id == id)
            return i;
    }
    return -1;
}

// 0x7100a24a40 (placeholder name): fills the item info panel (and the two number panels) from the
// displayed pouch item: the weapon stats for weapons, the armour defence for armour pieces, the
// cooking info for food, the hit point recover for materials and the hero soul icons for key items.
// NON_MATCHING: the instructions are the same, but our clang lays the weapon arm's equipped-item
// stats block out of line (the original keeps it inline) and colours the spilled locals differently,
// which also rotates the callee-saved registers.
void ScreenMessageGet::sub_7100A24A40(Unk_710247a6d8* panel, Unk_710247adc8* numbers,
                                      const PouchItem* item, const sead::SafeString& name, u32 type) {
    _36f0.str.clear();
    _36f0._58 = -1;
    _36f0._5c = 1;
    if (!panel)
        return;
    PauseMenuDataMgr* mgr = PauseMenuDataMgr::instance();
    ksys::act::InfoData* info = ksys::act::InfoData::instance();
    if (!mgr || !info)
        return;

    const sead::SafeString* display = item ? &item->getName() : &name;
    if (type == u32(PouchItemType::Arrow)) {
        panel->sub_71009B0EEC(0);
    } else if (type <= u32(PouchItemType::Shield)) {
        panel->sub_71009B0EEC(1);
        const PouchItem* equipped = mgr->getEquippedItem(PouchItemType(type));
        const u32 category =
            type == u32(PouchItemType::Bow) ? 1 : 2 * (type == u32(PouchItemType::Shield));
        s32 old_value = 0;
        s32 value = 0;
        s32 old_number = 0;
        s32 number = 0;
        if (item) {
            WeaponStats stats;
            getWeaponStats(*item, &stats);
            value = stats.power;
            number = stats.bow_add_value;
            if (equipped && !item->isEquipped()) {
                WeaponStats equipped_stats;
                getWeaponStats(*equipped, &equipped_stats);
                old_value = equipped_stats.power;
                old_number = equipped_stats.bow_add_value;
            }
        } else {
            value = sub_7100AA7A50(*display, type == u32(PouchItemType::Shield));
            if (type == u32(PouchItemType::Bow))
                number = getBowActorInfoAddValue(*display);
        }
        if (name == "Weapon_Sword_080" || name == "Weapon_Sword_081") {
            value = ksys::act::getAttackPower(ksys::act::InfoData::instance(), display->cstr()) +
                    ksys::gdt::getFlag_100enemy_SwordPower_StartTmp(false);
        }
        s32 override = 0;
        if (sub_7100A9FC20(name, &override, true)) {
            value = override;
        } else {
            const sead::SafeString equipped_name =
                equipped ? equipped->getName() : sead::SafeString::cEmptyString;
            if (sub_7100A9FC20(equipped_name, &override, false))
                old_value = override;
        }
        numbers->sub_71009B2380(category, old_value, value, old_number, number);
        _3770 = s32(type);
        _3774 = u32(value);
        _3778 = u32(number);
        if (item)
            panel->sub_71009B0FCC(item);
        else
            panel->sub_71009B1024();
    } else if (sub_7100A82E28(s32(type))) {
        panel->sub_71009B0EEC(2);
        u32 category = type == u32(PouchItemType::ArmorHead) ? 3 : 4;
        if (type == u32(PouchItemType::ArmorLower))
            category = 5;
        s32 old_value = 0;
        if (_3780.isEmpty()) {
            const PouchItem* equipped = mgr->getEquippedItem(PouchItemType(type));
            if (equipped)
                old_value = ksys::act::getArmorDefenceAddLevel(info, equipped->getName().cstr());
        } else {
            old_value = ksys::act::getArmorDefenceAddLevel(info, _3780.cstr());
        }
        const s32 value = ksys::act::getArmorDefenceAddLevel(info, display->cstr());
        numbers->sub_71009B2380(category, old_value, value, 0, 0);
        _3770 = s32(type);
        _3774 = u32(value);
        if (item)
            panel->sub_71009B102C(item);
        else
            panel->sub_71009B108C(*display);
    } else if (type == u32(PouchItemType::Material)) {
        al::ByamlIter iter;
        if (info->getActorIter(&iter, display->cstr(), true) &&
            info->hasTag(iter, 0x14185415)) {
            panel->sub_71009B0EEC(3);
            panel->sub_71009B10EC(getItemHitPointRecover(*display));
        } else {
            panel->sub_71009B0EEC(0);
        }
    } else if (type == u32(PouchItemType::Food)) {
        if (!item) {
            panel->sub_71009B0EEC(0);
        } else {
            panel->sub_71009B0EEC(3);
            CookingInfo cook;
            al::ByamlIter iter;
            if (info->getActorIter(&iter, display->cstr(), true) &&
                info->hasTag(iter, 0x30a3552e)) {
                sub_7100AA4810(*item, &cook);
                _36f0.str.copy(name);
                _36f0._58 = u32(cook.effect);
                _36f0._5c = u32(cook.level);
            } else {
                cookingStuff_0(*display, &cook);
            }
            panel->sub_71009B1148(cook);
        }
    } else {
        panel->sub_71009B0EEC(0);
        if (type == u32(PouchItemType::KeyItem)) {
            const s32 soul = sub_7100AA46F0(*display);
            if (soul != -1) {
                const s32 icon = sub_7100A25474(soul);
                if (icon >= 0) {
                    _37d8[icon].sub_710093372C(false);
                    _37d8[icon].sub_7100933850(true, false);
                    _3770 = 9;
                }
            }
        }
    }

    if (_36f0.str.isEmpty())
        panel->sub_71009B0C34(name);
    else
        panel->sub_71009B0CF4(name);
}

// 0x7100a2511c (placeholder name): updates the two equipment number panels from the displayed item
// type: the hero soul icons for key items, the weapon stats for weapons and the armour defence for
// the armour pieces (number set 0 / 1 / 2 by the weapon category).
// NON_MATCHING: the instructions are the same, but the weapon category's `category = 1` / `= 0`
// blocks are placed inline in the original and after the return in ours.
void ScreenMessageGet::sub_7100A2511C() {
    if (!sub_7100A9BA48())
        return;
    if (_3770 == -1)
        return;

    PauseMenuDataMgr* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return;

    if (_3770 == s32(PouchItemType::KeyItem)) {
        if (!sub_7100A9BA78(2))
            return;
        sead::FixedSafeString<64> name;
        sub_7100AA29C4(UI::instance()->_40, name);
        const s32 soul = sub_7100AA46F0(name);
        if (soul == -1)
            return;
        const s32 icon = sub_7100A25474(soul);
        if (icon < 0)
            return;
        if (icon == 5) {
            _37d8[5].sub_7100933850(UiSubsys1::instance()->get4b8(), false);
        } else if (u32(icon - 6) <= 3) {
            _37d8[icon].sub_7100933850(true, false);
        } else {
            _37d8[icon].sub_7100933850(mgr->isHeroSoulEnabled(name), false);
        }
        return;
    }

    s32 old_value = 0;
    s32 value = 0;
    s32 old_number = 0;
    s32 number = 0;
    u32 category = 0;
    if (sub_7100A82E28(_3770)) {
        if (!sub_7100A9BA78(1))
            return;
        sead::FixedSafeString<64> name;
        sub_7100AA29C4(UI::instance()->_40, name);
        if (auto* info = ksys::act::InfoData::instance()) {
            if (_3780.getStringTop()[0] == sead::SafeString::cNullChar) {
                const PouchItem* item = mgr->getEquippedItem(PauseMenuDataMgr::getType(name));
                if (item)
                    old_value = ksys::act::getArmorDefenceAddLevel(info, item->getName().cstr());
            } else {
                old_value = ksys::act::getArmorDefenceAddLevel(info, _3780.cstr());
            }
        }
        value = _3774;
        category = _3770 == s32(PouchItemType::ArmorHead) ? 3 : 4;
        if (_3770 == s32(PouchItemType::ArmorLower))
            category = 5;
    } else {
        if (u32(_3770) > 3)
            return;
        if (_3770 == s32(PouchItemType::Arrow))
            return;
        if (!sub_7100A9BA78(0))
            return;
        value = _3774;
        number = _3778;
        if (const PouchItem* item = mgr->getEquippedItem(PouchItemType(_3770))) {
            WeaponStats stats;
            getWeaponStats(*item, &stats);
            old_value = stats.power;
            old_number = stats.bow_add_value;
        }
        switch (PouchItemType(_3770)) {
        case PouchItemType::Bow:
            category = 1;
            break;
        case PouchItemType::Shield:
            category = 2;
            break;
        default:
            category = 0;
            break;
        }
    }
    _3670[0].view.sub_71009B2380(category, old_value, value, old_number, number);
    _3670[1].view.sub_71009B2380(category, old_value, value, old_number, number);
}

}  // namespace uking::ui
