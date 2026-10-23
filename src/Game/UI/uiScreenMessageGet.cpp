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
