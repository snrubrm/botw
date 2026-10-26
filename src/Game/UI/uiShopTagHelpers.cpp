#include "Game/UI/uiScreens.h"
#include "Game/UI/uiRecipe.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiShopCookInfo.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/Actor/resResourceShop.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectMonsterShop.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "Game/UI/euiGrammar.h"
#include <cstring>
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSystem.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073BB28.h"

// Shop tag-argument helpers (the 0x7100aa4b4c/0x7100aa4e70 tag resolvers live in this TU in the
// original: the 16-byte forwarders sit right next to them).
namespace uking::ui {

// Defined further down the TU; not decompiled yet.
s32 sub_7100A90B24(const ksys::act::ActorLinkConstDataAccess* actor,
                   ksys::act::ActorLinkConstDataAccess* accessor, s32* value);
// 0x7100a9017c: applies the purchase the shop helper resolved.
bool sub_7100A9017C(const ksys::act::ActorLinkConstDataAccess* accessor,
                    ksys::act::ActorLinkConstDataAccess* extra_accessor, s32* value);
// 0x7100a90860 (defined below): the buying price of the actor.
s32 sub_7100A90860(const ksys::act::ActorLinkConstDataAccess* accessor);
// 0x7100a90314: fills the buy-check record from the shop accessors.
bool sub_7100A90314(ShopBuyInfo* info, const ksys::act::ActorLinkConstDataAccess* accessor,
                    ksys::act::ActorLinkConstDataAccess* extra_accessor, const s32* value);
// 0x710073a6d0 (not decompiled yet)
void sub_710073A6D0(const ksys::act::ActorLinkConstDataAccess* accessor, const sead::SafeString& name);
// Defined below sub_7100A9127C.
s32 shopBuyRupeeStuff(const ksys::act::ActorLinkConstDataAccess* accessor,
                      ksys::act::ActorLinkConstDataAccess* extra_accessor, s32* value);

// NON_MATCHING: FixedSafeString construction hoists the null-character load and changes register allocation.
// 0x7100a91784
void sub_7100A91784(RecipeItems* items, const sead::SafeString& actor) {
    ksys::act::InfoData::RecipeInfo recipe;
    ksys::act::InfoData::instance()->getRecipeInfo(actor.cstr(), recipe);
    for (s32 i = 0; i < 3; ++i) {
        (*items)[i].name = recipe.items[i].name;
        (*items)[i].num = recipe.items[i].num;
    }
    sead::FixedSafeString<64> group_name;
    for (s32 i = 0; i < recipe.num_items; ++i) {
        if (ksys::act::getSameGroupActorName(&group_name, (*items)[i].name))
            (*items)[i].name = group_name;
    }
}

// 0x7100a90e40 (placeholder name): whether the shop can sell `num` of the item at `price` for the
// purchase `type` (0 = rupees, 1 = recipe, 2 = mamo). Returns 0 when it can, 1 when the count is
// zero (for a non-recipe purchase), 2 / 3 when the player lacks rupees / mamo, 6 when the recipe
// ingredients are missing and 7 when the item cannot go into the pouch.
u32 sub_7100A90E40(const sead::SafeString& name, s32 price, s32 type, s32 num) {
    if (type != 1 && num == 0)
        return 1;

    ShopBuyInfo info;
    info.type = type;
    if (type == 1)
        sub_7100A91784(&info.items, name);
    info.price = price;
    if (info.type == 2) {
        if (ksys::gdt::getFlag_CurrentMamo(false) < price)
            return 3;
    } else {
        if (ksys::gdt::getFlag_CurrentRupee(false) < price)
            return 2;
    }
    if (info.type == 1 && !sub_7100A90A34(info.items))
        return 6;
    return actorHasTagCanGetPouch(name) ? 0 : 7;
}

// 0x7100a90fd8 (placeholder name): as sub_7100A90E40, but checks the pouch entry with the pause
// menu manager (adding / removing `count` items) instead of the actor's can-get-pouch tag.
s32 sub_7100A90FD8(const sead::SafeString& name, s32 price, s32 type, s32 count) {
    ShopBuyInfo info;
    info.type = type;
    if (type == 1)
        sub_7100A91784(&info.items, name);
    info.price = price;
    if (info.type == 2) {
        if (ksys::gdt::getFlag_CurrentMamo(false) < price)
            return 3;
    } else {
        if (ksys::gdt::getFlag_CurrentRupee(false) < price)
            return 2;
    }
    if (info.type == 1 && !sub_7100A90A34(info.items))
        return 6;
    if (auto* mgr = PauseMenuDataMgr::instance()) {
        if (!mgr->checkAddOrRemoveItem(name, count, false))
            return 7;
    }
    return 0;
}

// 0x7100a9017c (placeholder name): applies the purchase the shop helper resolved: refunds the
// price into the player's current rupees / mamo and, for a recipe purchase, also uses the recipe
// ingredients.
bool sub_7100A9017C(const ksys::act::ActorLinkConstDataAccess* accessor,
                    ksys::act::ActorLinkConstDataAccess* extra_accessor, s32* value) {
    ShopBuyInfo info;
    sub_7100A90314(&info, accessor, extra_accessor, value);

    switch (info.type) {
    case 0:
        ksys::gdt::increaseFlag_CurrentRupee(-info.price);
        return true;
    case 2:
        ksys::gdt::increaseFlag_CurrentMamo(-info.price);
        return true;
    case 1:
        ksys::gdt::increaseFlag_CurrentRupee(-info.price);
        if (auto* mgr = PauseMenuDataMgr::instance()) {
            mgr->useItemFromRecipeAndSave(&info.items, 1, nullptr);
            return true;
        }
        return false;
    }
    return true;
}

// 0x7100a90314 (placeholder name): fills the buy-check record: the price and the purchase type
// (0 = rupees, 1 = recipe, 2 = mamo) plus the recipe ingredients for a recipe purchase. For a shop
// whose "Market" table holds the item, adds the table entry's price adjustment.
bool sub_7100A90314(ShopBuyInfo* info, const ksys::act::ActorLinkConstDataAccess* accessor,
                    ksys::act::ActorLinkConstDataAccess* extra_accessor, const s32* value) {
    if (!accessor->hasProc())
        return false;

    const s32 type = *value;
    switch (type) {
    case -2: {
        const sead::SafeString& name = extra_accessor->getName();
        if (name != "Npc_oasis001" && name != "Npc_LaboRobo")
            break;
        [[fallthrough]];
    }
    case 1: {
        auto* info_data = ksys::act::InfoData::instance();
        if (!info_data)
            return false;
        sead::FixedSafeString<64> group_name;
        ksys::act::getSameGroupActorName(&group_name, accessor->getName().cstr());
        info->price = ksys::act::getItemCreatingPrice(info_data, group_name.cstr());
        sub_7100A91784(&info->items, group_name);
        info->type = 1;
        return true;
    }
    case 2:
        info->price = accessor->getGParamList()->getMonsterShop()->mBuyMamo.ref();
        info->type = 2;
        return true;
    }

    info->price = sub_7100A90860(accessor);
    info->type = 0;
    if (extra_accessor->hasProc()) {
        if (auto* shop = extra_accessor->getShopData()) {
            const s32 index = shop->findTableIndexOrNormal("Market");
            if (index >= 0) {
                const auto& table = shop->getTables()[index];
                const s32 count = table.items.size();
                const auto* items = table.items.getBufferPtr();
                for (s32 i = 0; i != count; ++i) {
                    const auto& item = items[i];
                    if (item.name.ref() == accessor->getName()) {
                        info->price += item.price_adjustment.ref();
                        break;
                    }
                }
            }
        }
    }
    return true;
}

// 0x7100a90700: acquires `src` into `dst`, stores the source's value, and when the source has the
// connected-calc tag also acquires its connected calc child into `dst`.
bool sub_7100A90700(ksys::act::ActorLinkConstDataAccess* dst, ksys::act::BaseProcAccessor* out,
                    s32* value, const ksys::act::ActorLinkConstDataAccess* src) {
    dst->acquireActor(*src);
    *value = src->sub_7100D15E50();

    if (src->hasTag(0x4abb738e)) {
        ksys::act::ActorLinkConstDataAccess child;
        src->acquireConnectedCalcChild(&child);
        if (!child.hasProc())
            return false;
        dst->acquireActor(child);
    }

    sub_7100EE27B4(out, *src);
    return true;
}

// 0x7100a90860 (placeholder name): the buying price of the actor, looked up by its same-group actor name unless
// it is a "get item self" actor.
s32 sub_7100A90860(const ksys::act::ActorLinkConstDataAccess* accessor) {
    sead::FixedSafeString<64> name;
    const auto* gparam = accessor->getGParamList();
    if (!gparam->getSystem()->mIsGetItemSelf.ref() && accessor->getSameGroupActorName(&name)) {
        if (auto* info = ksys::act::InfoData::instance())
            return ksys::act::getItemBuyingPrice(info, name.cstr());
    }
    return sub_7100730FD0(accessor);
}

// 0x7100a907b4: as sub_7100A90700, with the connected calc parent instead of the child.
bool sub_7100A907B4(ksys::act::ActorLinkConstDataAccess* dst, ksys::act::BaseProcAccessor* out,
                    s32* value, const ksys::act::ActorLinkConstDataAccess* src) {
    dst->acquireActor(*src);
    ksys::act::ActorLinkConstDataAccess parent;
    src->acquireConnectedCalcParent(&parent);
    if (parent.hasProc() && parent.hasTag(0x4abb738e)) {
        *value = parent.sub_7100D15E50();
        sub_7100EE27B4(out, parent);
    } else {
        *value = src->sub_7100D15E50();
        sub_7100EE27B4(out, *src);
    }
    return true;
}

// 0x7100a90938: writes the item name, or the same-group actor name when the actor is not a
// "get item self" actor.
bool sub_7100A90938(sead::SafeString& out, const sead::SafeString& name) {
    auto* info = ksys::act::InfoData::instance();
    if (!info || ksys::act::getSystemIsGetItemSelf(info, name.cstr())) {
        out = name;
        return false;
    }
    return ksys::act::getSameGroupActorName(&out, name);
}

// 0x7100a909c0 (placeholder name): whether sub_7100A90700 succeeds and finds a proc for `src`
bool sub_7100A909C0(const ksys::act::ActorLinkConstDataAccess* src) {
    ksys::act::ActorLinkConstDataAccess actor;
    ksys::act::ActorLinkConstDataAccess accessor;
    s32 value;
    return sub_7100A90700(&actor, &accessor, &value, src) && accessor.hasProc();
}

// 0x7100a90a34
bool sub_7100A90A34(const RecipeItems& items) {
    for (s32 i = 0; i < 3; ++i) {
        s32 count = 0;
        if (!items[i].name.isEmpty()) {
            if (auto* mgr = PauseMenuDataMgr::instance())
                count = mgr->getItemCount(items[i].name, true);
        }
        if (count < items[i].num)
            return false;
    }
    return true;
}

// 0x7100a90dac (placeholder name): the value of the actor's connected-calc parent (0x10 when sub_7100A90700
// fails).
s32 sub_7100A90DAC(const ksys::act::ActorLinkConstDataAccess* accessor) {
    if (!accessor->hasProc())
        return -1;
    ksys::act::ActorLinkConstDataAccess actor;
    ksys::act::ActorLinkConstDataAccess proc_accessor;
    s32 value;
    if (!sub_7100A90700(&actor, &proc_accessor, &value, accessor))
        return 0x10;
    return sub_7100A90B24(&actor, &proc_accessor, &value);
}

// 0x7100a9139c (placeholder name): the rupee value of the actor for the shop.
s32 sub_7100A9139C(const ksys::act::ActorLinkConstDataAccess* accessor) {
    if (!accessor->hasProc())
        return -1;
    ksys::act::ActorLinkConstDataAccess actor;
    ksys::act::ActorLinkConstDataAccess proc_accessor;
    s32 value;
    sub_7100A907B4(&actor, &proc_accessor, &value, accessor);
    return shopBuyRupeeStuff(accessor, &proc_accessor, &value);
}

// 0x7100a91d4c (placeholder name): whether the player has the recipe's ingredients.
bool sub_7100A91D4C(const sead::SafeString& actor) {
    RecipeItems items;
    sub_7100A91784(&items, actor);
    return sub_7100A90A34(items);
}

// 0x7100a91c88 (placeholder name): the info overlay / cannot-buy message for the player's item state.
// NON_MATCHING: the original tests the cases in the order 7 / 6 / 2; clang 4 merges the compares into a switch
// and tests them in ascending order. Same instructions otherwise.
void sub_7100A91C88(const ksys::act::ActorLinkConstDataAccess* accessor, const s32* state) {
    switch (*state) {
    case 7: {
        if (!accessor->hasTag(0x4abb738e)) {
            showCannotPickupBuyAnyMoreMessageMaybe(accessor->getName(), true);
            return;
        }
        ksys::act::ActorLinkConstDataAccess child;
        accessor->acquireConnectedCalcChild(&child);
        if (child.hasProc())
            showCannotPickupBuyAnyMoreMessageMaybe(child.getName(), true);
        break;
    }
    case 6:
        showInfoOverlay(0x20);
        break;
    case 2:
        showInfoOverlay(0x1f);
        break;
    }
}

// 0x7100a9117c (placeholder name): reports the shop buy price of the actor.
s32 shopBuyRupeeStuff(const ksys::act::ActorLinkConstDataAccess* accessor,
                      ksys::act::ActorLinkConstDataAccess* extra_accessor, s32* value) {
    const s32 result = sub_7100A90B24(accessor, extra_accessor, value);
    if (result)
        return result;
    sub_7100A9017C(accessor, extra_accessor, value);
    sub_710073A6D0(accessor, accessor->getName());
    const sead::SafeString& name = accessor->getName();
    if (ksys::PlayReportMgr::instance()) {
        sead::FixedSafeString<64> label;
        label.format("ShopBuy_Rupee");
        if (label.isEmpty())
            return 0;
        ksys::PlayReportMgr::instance()->reportDebug(label, name);
    }
    return 0;
}

// 0x7100a9127c: reports the shop action `state` (1-5, 7) `count` times as a debug report with the item name.
// NON_MATCHING: clang 4 hoists the `count > 0` test above the `message.isEmpty()` test (both branch to the same
// epilogue); the original emits the empty test first. Same instructions otherwise.
void sub_7100A9127C(s32 state, const sead::SafeString& item_name, s32 count) {
    if (!ksys::PlayReportMgr::instance())
        return;
    sead::FixedSafeString<0x40> message;
    switch (state) {
    case 1:
    case 5:
    case 7:
        message.format("ShopBuy_Rupee");
        break;
    case 2:
        message.format("ShopSell_Rupee");
        break;
    case 3:
        message.format("ShopBuy_Mamo");
        break;
    case 4:
        message.format("ShopSell_Mamo");
        break;
    default:
        break;
    }
    if (message.isEmpty())
        return;
    if (count > 0) {
        do {
            ksys::PlayReportMgr::instance()->reportDebug(message, item_name);
        } while (--count);
    }
}

KSYS_VISIBILITY_HIDDEN ShopCookInfo sUnk_71025F6960{
    {},
    {11, sUnk_71025F6960.entries},
    {31, sUnk_71025F6960.modifier_entries},
    {},
    ":",
    {14, sUnk_71025F6960.heroSoulNameStrings},
    {sead::RegionLanguageID::JPja, sead::RegionLanguageID::USen,
     sead::RegionLanguageID::USes, sead::RegionLanguageID::EUen,
     sead::RegionLanguageID::EUnl, sead::RegionLanguageID::KRko,
     sead::RegionLanguageID::CNzh, sead::RegionLanguageID::TWzh},
    {"Obj_HeroSoul_Rito", "Obj_HeroSoul_Goron", "Obj_HeroSoul_Gerudo", "Obj_HeroSoul_Zora",
     "Obj_DungeonClearSeal", "Obj_WarpDLC", "Obj_DLC_HeroSeal_Rito", "Obj_DLC_HeroSeal_Goron",
     "Obj_DLC_HeroSeal_Gerudo", "Obj_DLC_HeroSeal_Zora", "Obj_DLC_HeroSoul_Rito",
     "Obj_DLC_HeroSoul_Goron", "Obj_DLC_HeroSoul_Gerudo", "Obj_DLC_HeroSoul_Zora"},
    {{CookEffectId::GutsRecover, "GutsRecover"},
      {CookEffectId::ExGutsMaxUp, "ExGutsMaxUp"},
      {CookEffectId::LifeMaxUp, "LifeMaxUp"},
      {CookEffectId::ResistHot, "ResistHot"},
      {CookEffectId::ResistCold, "ResistCold"},
      {CookEffectId::ResistElectric, "ResistElectric"},
      {CookEffectId::AttackUp, "AttackUp"},
      {CookEffectId::DefenseUp, "DefenseUp"},
      {CookEffectId::Quietness, "Quietness"},
      {CookEffectId::MovingSpeed, "AllSpeed"},
      {CookEffectId::Fireproof, "Fireproof"}},
    {},
    {
        {15, "ExGutsMaxUp", 0, 10},
        {2, "LifeMaxUp", 1, -1},
        {4, "ResistHot", 3, 2},
        {5, "ResistCold", 2, 2},
        {6, "ResistElectric", 4, 3},
        {10, "AttackUp", 6, 3},
        {11, "DefenseUp", 7, 3},
        {12, "Quietness", 8, 3},
        {13, "AllSpeed", 5, 3},
        {14, "GutsRecover", 18, -1},
        {16, "Fireproof", 19, 2},
        {17, "ResistLightning", 33, 1},
        {18, "SwimSpeedUp", 21, 3},
        {19, "ClimbSpeedUp", 20, 3},
        {20, "SandMoveSpeedUp", 9, 1},
        {21, "SnowMovingSpeed", 12, 1},
        {22, "ReduceAncientEnemyDamge", 11, 3},
        {24, "AddPower", 15, -1},
        {25, "AddLife", 16, -1},
        {27, "AddGuard", 31, -1},
        {26, "Critical", 17, -1},
        {28, "AddPowerPlus", 23, -1},
        {29, "AddLifePlus", 25, -1},
        {30, "AddGuardPlus", 32, -1},
        {31, "LongThrow", 26, -1},
        {32, "SpreadFire", 27, -1},
        {33, "ZoomRapid", 28, -1},
        {34, "RapidFire", 29, -1},
        {35, "SurfMaster", 30, -1},
        {36, "", 34, 1},
        {37, "ResistFreeze", 35, 1},
    },
};

// NON_MATCHING: the value test uses an equivalent compare immediate and register allocation differs.
// 0x7100aa4354
void sub_7100AA4354(const PouchItem* item, sead::BufferedSafeString* out) {
    if (item->getValue() < 1) {
        if (const char* icon = ksys::act::getMasterSwordSleepActorName(
                ksys::act::InfoData::instance(), item->getName().cstr()))
            out->copy(icon);
    } else if (act::DamageInfoMgr::instance()->isTrueFormMasterSword()) {
        if (const char* icon = ksys::act::getMasterSwordTrueFormActorName(
                ksys::act::InfoData::instance(), item->getName().cstr()))
            out->copy(icon);
    }
    if (out->isEmpty())
        out->copy(item->getName());
}

// NON_MATCHING: the effect-table loop uses a different signed-bound conversion and branch schedule.
// 0x7100aa3ea0
void sub_7100AA3EA0(const PouchItem* item, sead::BufferedSafeString* out) {
    auto* info = ksys::act::InfoData::instance();
    if (!item)
        return;
    al::ByamlIter iter;
    if (!info || !info->getActorIter(&iter, item->getName().cstr(), true))
        return;
    const bool is_dye = info->hasTag(iter, ksys::act::tags::ArmorDye);
    const bool is_medicine = info->hasTag(iter, ksys::act::tags::CookEMedicine);
    sead::FixedSafeString<64> name(item->getName());
    if (is_dye) {
        sub_7100AA3B50(name, out, item->getValue());
    } else if (is_medicine) {
        for (s32 i = 0; i < sUnk_71025F6960.effects.size(); ++i) {
            if (sUnk_71025F6960.effects[i].effect != item->getCookData().getEffect())
                continue;
            name.appendWithFormat("_%s", sUnk_71025F6960.effects[i].name.cstr());
            break;
        }
        sead::FixedSafeString<128> path;
        path.format("UI/StockItem/%s.bitemico", name.cstr());
        out->copy(path);
    } else {
        if (item->getType() == PouchItemType::Sword && item->getName() == "Weapon_Sword_070")
            sub_7100AA4354(item, &name);
        sub_7100AA3B50(name, out, -1);
    }
}

// 0x7100aa4e60
u32 sub_7100AA4E60(ShopInfoTagData* data, sead::WBufferedSafeString* out) {
    return sub_7100AA4B4C(data, data->_58, out);
}

// 0x7100aa4b4c (CSV unnamed): resolve a cook-effect shop tag into `out` (the message looked up
// under StaticMsg/CookEffect for the "<effect>_Name<suffix>" label, copied with the length
// returned). Returns 0 when the actor has the CookEffectName tag or the effect is not in the table.
u32 sub_7100AA4B4C(ShopInfoTagData* data, u32 selector, sead::WBufferedSafeString* out) {
    ksys::act::InfoData* info = ksys::act::InfoData::instance();
    if (info != nullptr) {
        if (info->hasTag(data->str.cstr(), ksys::act::tags::CookEffectName))
            return 0;
    }

    eui::Grammar::WordAttr attr;
    eui::MessageString msg;
    bool use_plural;
    if (sub_7100AA2BDC(data->str, &msg) != 0)
        use_plural = false;
    else
        use_plural = eui::Grammar::sub_7100BE39DC(&attr, msg);

    const s32 count = sUnk_71025F6960.effects.size();
    if (count < 1)
        return 0;
    const s64 n = count;
    for (s32 i = 0; i < n; ++i) {
        if (sUnk_71025F6960.effects[i].effect != CookEffectId(selector))
            continue;
        if (i < 0)
            return 0;
        sead::FixedSafeString<256> label;
        sead::SafeString suffix = "";
        if (use_plural) {
            // Note: written 1/2/3-first: clang lays the tests out back to front, so this
            // reproduces the original's 3/2/1 test order.
            if (attr._3 == 1) {
                suffix = "_Plural";
            } else if (attr._0 == 1) {
                suffix = "_Masculine";
            } else if (attr._0 == 2) {
                suffix = "_Feminine";
            } else if (attr._0 == 3) {
                suffix = "_Neuter";
            }
        }
        label.format("%s_Name%s", sUnk_71025F6960.effects[i].name.cstr(), suffix.cstr());
        eui::MessageString msg2;
        // Discarded call that really is in the target asm (the lookup result is used, not the
        // return value).
        ui::getMessage("StaticMsg/CookEffect", label, &msg2);
        const char16* str = msg2.getString();
        s32 len = s32(msg2.getLength());
        char16* dst = const_cast<char16*>(out->getStringTop());
        if (dst == str)
            return msg2.getLength();
        if (len < 0) {
            len = 0;
            for (;;) {
                if (len > 0x80000 || str[len] == sead::WSafeString::cNullChar)
                    break;
                ++len;
            }
            if (len > 0x80000)
                len = 0;
        }
        if (len >= out->getBufferSize())
            len = out->getBufferSize() - 1;
        std::memcpy(dst, str, len * sizeof(char16));
        dst[len] = sead::WSafeString::cNullChar;
        return msg2.getLength();
    }
    return 0;
}

// 0x7100aa4e70 (CSV unnamed): resolve a cook-effect shop tag with a level into `out` (the
// message looked up under StaticMsg/CookEffect for the "<effect>_<Desc>" label, copied with the
// length returned). The Desc part gains a Medicine/level suffix. Returns 0 when the effect is not
// in the table.
// NON_MATCHING: the table search, entry bind, InfoData/tag check, label/message/tail all match,
// but the level-suffix block is restructured: the original keeps branchy `level >= 1`, clamping
// `level > 3` to 3, and `level >= 2` tests around a single append, while ours proves the first
// test redundant and fuses the clamp+test into predicated append-argument computing (cinc/csel
// with an unconditional append). Six natural forms tried (nested ifs, &&-outer, u32/s32 tests,
// separate level copy); the compiler always re-derives the fused shape.
u32 sub_7100AA4E70(ShopInfoTagData* data, u32 sel_lo, u32 sel_hi, sead::WBufferedSafeString* out) {
    const s32 count = sUnk_71025F6960.effects.size();
    if (count < 1)
        return 0;
    const s64 n = count;
    for (s32 i = 0; i < n; ++i) {
        if (sUnk_71025F6960.effects[i].effect != CookEffectId(sel_lo))
            continue;
        // Dead index guard that really is in the target asm (as in sub_7100AA4B4C).
        if (i < 0)
            return 0;
        sead::FixedSafeString<256> label;
        const sead::SafeString& entry_name = sUnk_71025F6960.effects[i].name;
        {
            sead::FormatFixedSafeString<16> name("Desc");
            ksys::act::InfoData* info = ksys::act::InfoData::instance();
            if (info != nullptr) {
                if (info->hasTag(data->str.cstr(), ksys::act::tags::CookEMedicine))
                    name.format("MedicineDesc");
            }
            s32 level = sel_hi;
            if (sel_lo > 15 || ((1u << sel_lo) & 0xc004) == 0) {
                if (level >= 1) {
                    if (level > 3)
                        level = 3;
                    if (level >= 2)
                        name.appendWithFormat("_%02d", level);
                }
            }
            label.format("%s_%s", entry_name.cstr(), name.cstr());
        }
        eui::MessageString msg;
        // Discarded call that really is in the target asm (as in sub_7100AA4B4C).
        ui::getMessage("StaticMsg/CookEffect", label, &msg);
        const char16* str = msg.getString();
        s32 len = s32(msg.getLength());
        char16* dst = const_cast<char16*>(out->getStringTop());
        if (dst == str)
            return msg.getLength();
        if (len < 0) {
            len = 0;
            for (;;) {
                if (len > 0x80000 || str[len] == sead::WSafeString::cNullChar)
                    break;
                ++len;
            }
            if (len > 0x80000)
                len = 0;
        }
        if (len >= out->getBufferSize())
            len = out->getBufferSize() - 1;
        std::memcpy(dst, str, len * sizeof(char16));
        dst[len] = sead::WSafeString::cNullChar;
        return msg.getLength();
    }
    return 0;
}

// 0x7100aa5140
u32 sub_7100AA5140(ShopInfoTagData* data, sead::WBufferedSafeString* out) {
    return sub_7100AA4E70(data, data->_58, data->_5c, out);
}

// 0x7100aa2bdc (CSV unnamed): resolve the tag data's string into a message (suffix-stripped actor
// name under ActorType/<profile>, or the empty message).
u32 sub_7100AA2BDC(const sead::SafeString& actor_name, eui::MessageString* out) {
    if (actor_name.getStringTop()[0] == sead::SafeString::cNullChar) {
        const s32 len = sead::WSafeString::cEmptyString.calcLength();
        eui::MessageString empty(len, sead::WSafeString::cEmptyString.cstr());
        out->assign(empty);
        return 1;
    }
    sead::FixedSafeString<64> name;
    sub_7100AA29C4(actor_name, name);
    sead::FixedSafeString<256> set;
    const char* profile;
    ksys::act::InfoData::instance()->getActorProfile(&profile, name.cstr());
    set.format("ActorType/%s", profile);
    sead::FixedSafeString<256> label;
    label.format("%s_Name", name.cstr());
    return ui::getMessage(set, label, out);
}

// 0x7100aa29c4 (CSV unnamed): strip the "_Far" suffix from the name, reporting whether it changed.
// NON_MATCHING: the entry, both inlined calcLength loops' heads and the return match, but the
// "_Far" literal folds in our TU (immediate char compares, constant length) while the original
// scans it generically, which also perturbs the second calcLength's unrolling and the memcmp tail.
// (A same-TU literal + simple loop always folds in clang 4; the original's must be opaque.)
bool sub_7100AA29C4(const sead::SafeString& actor_name, sead::SafeString& name) {
    ksys::act::InfoData* info = ksys::act::InfoData::instance();
    if (info == nullptr) {
        name = actor_name;
        return false;
    }
    if (ksys::act::getSystemIsGetItemSelf(info, actor_name.cstr())) {
        name = actor_name;
        return false;
    }
    if (ksys::act::getSameGroupActorName(&name, actor_name))
        return true;
    const s32 len = name.calcLength();
    s32 len2 = name.calcLength();
    const char* suffix = "_Far";
    s32 suffix_len = 0;
    while (suffix[suffix_len] != '\0' && suffix_len < 0x80000)
        ++suffix_len;
    if (suffix_len >= 0x80000)
        suffix_len = 0;
    const s32 new_len = len2 - suffix_len;
    if (new_len >= 0) {
        char* tail = const_cast<char*>(name.getStringTop()) + new_len;
        if (suffix_len >= 1 && tail != suffix) {
            const s32 cmp_len = suffix_len < 0x80000 ? suffix_len : 0x80000;
            bool matched = true;
            s32 i = 0;
            for (; i < cmp_len; ++i) {
                if (tail[i] != suffix[i]) {
                    matched = false;
                    break;
                }
                if (tail[i] == '\0')
                    break;
            }
            if (matched) {
                *tail = '\0';
                len2 = new_len;
            }
        } else {
            *tail = '\0';
            len2 = new_len;
        }
    }
    return len != len2;
}

// 0x7100aa2e08 (CSV unnamed): resolve the tag data's string into a message (the empty message
// when the string is empty, else the "<profile>" / "<name>_Desc" lookup through sub_7100AA2FA0).
u32 sub_7100AA2E08(const sead::SafeString& name, eui::MessageString* out) {
    if (name.getStringTop()[0] == sead::SafeString::cNullChar) {
        const s32 len = sead::WSafeString::cEmptyString.calcLength();
        eui::MessageString empty(len, sead::WSafeString::cEmptyString.cstr());
        out->assign(empty);
        return 1;
    }
    sead::FixedSafeString<0x100> set;
    sead::FixedSafeString<0x100> label;
    sub_7100AA2FA0(name, &set, &label);
    return ui::getMessage(set, label, out);
}

// 0x7100aa2fa0 (CSV unnamed): fill `arg1` with "ActorType/<profile>" and `arg2` with
// "<name>_Desc" for the tag data's (suffix-stripped) actor name. Does nothing when the tag
// data's string is empty.
void sub_7100AA2FA0(const sead::SafeString& name, sead::BufferedSafeStringBase<char>* arg1,
                    sead::BufferedSafeStringBase<char>* arg2) {
    if (name.getStringTop()[0] == sead::SafeString::cNullChar)
        return;
    sead::FixedSafeString<64> actor_name;
    sub_7100AA29C4(name, actor_name);
    if (arg1 != nullptr) {
        const char* profile;
        ksys::act::InfoData::instance()->getActorProfile(&profile, actor_name.cstr());
        arg1->format("ActorType/%s", profile);
    }
    if (arg2 != nullptr) {
        arg2->format("%s_Desc", actor_name.cstr());
    }
}

// 0x7100aa3b50 (CSV unnamed): build the "UI/StockItem/<icon>" texture path for `name` into `out`
// (icon-actor lookup, Weapon_Sword_502/503 quirk, ".%02d" count suffix, ".bitemico" extension).
void sub_7100AA3B50(const sead::SafeString& name, sead::BufferedSafeStringBase<char>* out,
                    s32 count) {
    sead::FixedSafeString<0x80> path;
    ksys::act::InfoData* info = ksys::act::InfoData::instance();
    if (info != nullptr) {
        const char* icon = ksys::act::getItemUseIconActorName(info, name.cstr());
        if (*icon != sead::SafeString::cNullChar)
            path.format("UI/StockItem/%s", icon);
    }
    if (path.isEmpty())
        path.format("UI/StockItem/%s", name.cstr());
    if (name == "Weapon_Sword_502") {
        const char* sword =
            shouldUseWeaponSword503() ? "Weapon_Sword_503" : "Weapon_Sword_502";
        path.format("UI/StockItem/%s", sword);
    }
    if (count >= 1)
        path.appendWithFormat(".%02d", count);
    path.append(".bitemico");
    out->copy(path);
}

// NON_MATCHING: clang puts the type-0 block last instead of first, which adds three branches (240 bytes
// against 224).
// 0x7100a91e84 (placeholder name): the item's dye / stock state from its mode.
u32 sub_7100A91E84(const sead::SafeString& name, s32 type, s32 a3, bool flag) {
    auto* info = ksys::act::InfoData::instance();
    if (!info) {
        if (flag)
            return 0xe;
    } else if (type == 2) {
        const bool has = info->hasTag(name.cstr(), 0xd7c5d3b2);
        if (flag)
            return has ? 0xe : 0xd;
        if (!has)
            return 0xd;
    } else if (type == 0) {
        const bool has = info->hasTag(name.cstr(), 0x2cef9fdc);
        if (has)
            return 0xd;
        if (flag)
            return 0xe;
    } else if (flag) {
        return 0xe;
    }
    return a3 == 0 ? 0xc : 0;
}

// 0x7100a92180 (placeholder name): the stain colour state of the item, for the dye shop.
u32 sub_7100A92180(const sead::SafeString& name, s32 a2, s32 a3) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return 0xffffffff;
    if (ksys::act::getItemStainColor(info, name.cstr()) == a3)
        return a2 > 0 ? 0 : 0xb;
    return 0xa;
}

// 0x7100a91e40 (CSV unnamed): the item count for `name` (0 when the name is empty or there is no
// pouch manager).
s32 sub_7100A91E40(const sead::SafeString& name, bool count_equipped) {
    if (name.isEmpty())
        return 0;
    auto* mgr = PauseMenuDataMgr::instance();
    if (mgr == nullptr)
        return 0;
    return mgr->getItemCount(name, count_equipped);
}

// 0x7100aa69b4
// NON_MATCHING: the string copy hoists the null-character load and changes saved registers.
s32 sub_7100AA69B4(s32 message_id, eui::MessageString* out) {
    s32 index = -1;
    const s32 count = sUnk_71025F6960.modifiers.size();
    for (s32 i = 0; i != count; ++i) {
        if (sUnk_71025F6960.modifiers[i].id == message_id) {
            index = i;
            break;
        }
    }
    if (index < 0)
        return 2;
    sead::FixedSafeString<256> label(sUnk_71025F6960.modifiers[index].name);
    label.append("_Name");
    return getMessage("StaticMsg/SpecialStatus", label, out);
}

}  // namespace uking::ui

// Emits the Delegate2R vtable (0x71024987e0) + invoke (0x7100a534e8) + clone (0x7100a5351c).
template class sead::Delegate2R<uking::ui::ScreenShopInfo,
                                const sead::MessageSet<char16>::TagInfo*,
                                sead::WBufferedSafeString*, u32>;
