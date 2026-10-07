#include "Game/UI/uiUtils.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/euiLayoutEx.h"
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAnimator.h"
#include <nn/ui2d/Parts.h>
#include "Game/UI/euiMessageString.h"
#include "Game/UI/euiMessageMgr.h"
#include <devenv/seadEnvUtil.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadStringUtil.h>
#include "Game/Actor/actPlayerCreateMgr.h"
#include "Game/Actor/actWeapon.h"
#include "Game/DLC/aocHardModeManager.h"
#include "Game/Damage/dmgInfoManager.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Sound/sndMgr.h"

namespace dlc {
bool isOneHitObliteratorActor(ksys::act::Actor* actor, bool require_active);
}

s32 getWeaponTypeId(const sead::SafeString& profile);

namespace uking::ui {

// Original global at 0x710249a788, read and reset by sub_7100A64304.
s32 sUnk_710249a788 = 13;

// 0x7100a64304
s32 sub_7100A64304() {
    const s32 result = sUnk_710249a788;
    sUnk_710249a788 = 13;
    return result;
}

// 0x7100949d18
f32 sub_7100949D18(s32 count) {
    return f32(count) * 0.25f;
}

static const char* const sUnk_710250A4B8[] = {
    "GamePadBG_00",
    "Title_00",
    "MainScreen3D_00",
    "Message3D_00",
    "AppCamera_00",
    "WolfLinkHeartGauge_00",
    "EnergyMeterDLC_00",
    "MainHorse_00",
    "MiniGame_00",
    "ReadyGo_00",
    "KeyNum_00",
    "MessageGet_00",
    "DoCommand_00",
    "SousaGuide_00",
    "GameTitle_00",
    "DemoName_00",
    "DemoNameEnemy_00",
    "MessageSp_00_NoTop",
    "ShopBG_00",
    "ShopBtnList5_00",
    "ShopBtnList20_00",
    "ShopBtnList15_00",
    "ShopInfo_00",
    "ShopHorse_00",
    "Rupee_00",
    "KologNum_00",
    "AkashNum_00",
    "MamoNum_00",
    "Time_00",
    "PauseMenuBG_00",
    "SeekPadMenuBG_00",
    "AppTool_00",
    "AppAlbum_00",
    "AppPictureBook_00",
    "AppMapDungeon_00",
    "MainScreenMS_00",
    "MainScreenHeartIchigekiDLC_00",
    "MainScreen_00",
    "MainDungeon_00",
    "ChallengeWin_00",
    "PickUp_00",
    "MessageTipsRunTime_00",
    "AppMap_00",
    "AppSystemWindowNoBtn_00",
    "AppHome_00",
    "MainShortCut_00",
    "PauseMenu_00",
    "PauseMenuInfo_00",
    "GameOver_00",
    "HardMode_00",
    "SaveTransferWindow_00",
    "MessageTipsPauseMenu_00",
    "MessageTips_00",
    "OptionWindow_00",
    "AmiiboWindow_00",
    "SystemWindowNoBtn_00",
    "ControllerWindow_00",
    "SystemWindow_01",
    "SystemWindow_00",
    "PauseMenuRecipe_00",
    "PauseMenuMantan_00",
    "PauseMenuEiketsu_00",
    "AppSystemWindow_00",
    "DLCWindow_00",
    "HardModeTextDLC_00",
    "TestButton",
    "TestPocketUIDRC",
    "TestPocketUITV",
    "BoxCursorTV",
    "FadeDemo_00",
    "StaffRoll_00",
    "StaffRollDLC_00",
    "End_00",
    "DLCSinJuAkashiNum_00",
    "MessageDialog",
    "DemoMessage",
    "MessageSp_00",
    "Thanks_00",
    "Fade",
    "KeyBoradTextArea_00",
    "LastComplete_00",
    "OPtext_00",
    "LoadingWeapon_00",
    "MainHardMode_00",
    "LoadSaveIcon_00",
    "FadeStatus_00",
    "Skip_00",
    "ChangeController_00",
    "ChangeControllerDRC_00",
    "DemoStart_00",
    "BootUp_00",
    "BootUp_00",
    "ChangeControllerNN_00",
    "AppMenuBtn_00",
    "HomeMenuCapture_00",
    "HomeMenuCaptureDRC_00",
    "HomeNixSign_00",
    "ErrorViewer_00",
    "ErrorViewerDRC_00",
};

// 0x71010ad714
const char* sub_71010AD714(u32 index) {
    return sUnk_710250A4B8[index];
}

s32 getScreenIdxByName(const char* name) {
    for (s32 i = 0; i < 99; ++i) {
        if (sead::SafeString(sUnk_710250A4B8[i]) == name)
            return i;
    }
    return 99;
}

static eui::MessageString sUnk_71025F6930(2, u"");
static eui::MessageString sUnk_71025F6940(2, u"");
static eui::MessageString sUnk_71025F6950(2, u"");

int getMessage(const sead::SafeString& message_set, const sead::SafeString& label,
               eui::MessageString* out) {
    auto* set = eui::MessageMgr::instance()->getMessageSet(message_set);
    if (!set) {
        out->assign(sUnk_71025F6940);
        return 1;
    }
    out->assign(set->tryFindMessage(label.cstr()));
    if (!out->getString()) {
        out->assign(sUnk_71025F6930);
        return 2;
    }
    if (*out->getString() == sead::SafeStringBase<char16>::cNullChar)
        out->assign(sUnk_71025F6950);
    return 0;
}

void playSound(const sead::SafeString& label, xlink2::HandleSLink* handle) {
    ksys::snd::SoundMgr::instance()->mUiSoundMgr->playSound(label, handle);
}

// NON_MATCHING: enum comparisons, static initialization and the result branches are scheduled differently.
const char* getDecimalSeparator(bool a1) {
    const auto language = sead::EnvUtil::getRegionLanguage();
    static sead::RegionLanguageID sUnk_71025F6B40[] = {
        sead::RegionLanguageID::JPja, sead::RegionLanguageID::USen,
        sead::RegionLanguageID::USes, sead::RegionLanguageID::EUen,
        sead::RegionLanguageID::EUnl, sead::RegionLanguageID::KRko,
        sead::RegionLanguageID::CNzh, sead::RegionLanguageID::TWzh,
    };
    for (const auto& entry : sUnk_71025F6B40) {
        if (language == entry)
            return a1 || language != sead::RegionLanguageID::EUnl ? "." : ",";
    }
    return ",";
}

// 0x7100aa256c
s32 setWidgetString(eui::LayoutEx* layout, const sead::SafeString& widget_name,
                    const eui::MessageString& message) {
    if (layout)
        return layout->setMessageStringForEachId(widget_name.cstr(), message, true, nullptr);
    return 0;
}

// 0x7100aa25d4
s32 setWidgetString(eui::LayoutEx* layout, const sead::SafeString& widget_name,
                     const sead::SafeString& text) {
    sead::WFixedSafeString<128> buffer;
    sead::StringUtil::convertUtf8ToUtf16(buffer.getBuffer(), buffer.getBufferSize(), text.cstr(), -1);
    eui::MessageString message(buffer.calcLength(), buffer.cstr());
    if (layout)
        return layout->setMessageStringForEachId(widget_name.cstr(), message, true, nullptr);
    return 0;
}

void createAndLoadScreenIfNeededImpl(s32 id, sead::Heap*) {
    Manager::instance()->createAndLoadScreenIfNeeded(id);
}

bool isMasterSwordItem(const PouchItem& item) {
    return item.getType() == PouchItemType::Sword && isMasterSwordActorName(item.getName());
}

bool shouldUseWeaponSword503() {
    if (ksys::evt::Manager::instance() && ksys::evt::Manager::instance()->getActiveEvent() &&
        ksys::evt::Manager::instance()->getActiveEvent()->mEventName == "Demo601_1")
        return true;
    return dlc::isOneHitObliteratorActor(ksys::act::PlayerInfo::instance()->getPlayer()->m273(), true);
}

// 0x7100a9fc20 (placeholder name): the "infinite" attack power (-111; see formatSpecialAttackPower) of the One-Hit
// Obliterator
bool sub_7100A9FC20(const sead::SafeString& name, s32* out, bool force) {
    if (!name.isEmpty() && isOneHitObliteratorActorName(name) && (force || shouldUseWeaponSword503())) {
        *out = -111;
        return true;
    }
    return false;
}

// NON_MATCHING: the compiler reverses the special-value comparisons and their branches.
bool formatSpecialAttackPower(s32 power, sead::BufferedSafeString* out) {
    if (power == 99999) {
        *out = "1";
        return true;
    }
    if (power == -111) {
        *out = "∞";
        return true;
    }
    return false;
}

int getItemGeneralLife(const char* name) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return 0;

    al::ByamlIter iter;
    if (!info->getActorIter(&iter, name, false))
        return 0;

    s32 life = ksys::act::getGeneralLife(iter);
    const char* profile = "Dummy";
    if (iter.tryGetStringByKey(&profile, "profile") && getWeaponTypeId(profile) != -1 &&
        !info->hasTag(iter, 0x2B533845))
        life *= act::WeaponModifierInfo::getLifeMultiplier();
    return life;
}

int getItemHitPointRecover(const sead::SafeString& name) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return 0;

    al::ByamlIter iter;
    if (!info->getActorIter(&iter, name.cstr()))
        return 0;
    if (!info->hasTag(iter, ksys::act::tags::CureItem))
        return 0;
    if (!info->hasTag(iter, ksys::act::tags::CanUse))
        return 0;

    int value = ksys::act::getCureItemHitPointRecover(iter);

    using HardModeMgr = uking::aoc::HardModeManager;
    if (HardModeMgr::instance() &&
        HardModeMgr::instance()->checkFlag(HardModeMgr::Flag::EnableHardMode) &&
        HardModeMgr::instance()->isHardModeChangeOn(HardModeMgr::HardModeChange::NerfHpRestore)) {
        HardModeMgr::instance()->nerfHpRestore(&value);
    }

    return value;
}

void getWeaponStats(const PouchItem& item, WeaponStats* stats) {
    stats->durability = item.getValue();
    auto& modifier = stats->modifier;
    modifier.fromItem(item);

    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return;

    if (item.getType() == PouchItemType::Shield) {
        stats->power = ksys::act::getWeaponCommonGuardPower(info, item.getName().cstr());
        stats->power += modifier.flags.isOn(act::WeaponModifier::AddGuard) ? modifier.value : 0;

    } else if (isMasterSwordItem(item)) {
        int power = 0;
        if (item.getValue() > 0) {
            const bool is_true_form = dmg::DamageInfoMgr::instance()->isTrueFormMasterSword();
            auto* info_ = ksys::act::InfoData::instance();
            const char* name = item.getName().cstr();
            if (is_true_form) {
                power = ksys::act::getMasterSwordTrueFormAttackPower(info_, name);
            } else {
                const auto attack = ksys::act::getAttackPower(info_, name);
                power = ksys::gdt::getFlag_MasterSword_Add_Power() + attack;
            }
        }
        stats->power = power;

    } else if (isOneHitObliteratorActorName(item.getName())) {
        stats->power = dmg::DamageInfoMgr::instance()->isOneHitObliteratorActive() ? 99999 : 1;
    } else {
        stats->power =
            ksys::act::getAttackPower(ksys::act::InfoData::instance(), item.getName().cstr());
    }

    stats->power += modifier.flags.isOn(act::WeaponModifier::AddAtk) ? modifier.value : 0;

    if (item.getType() == PouchItemType::Bow) {
        if (modifier.flags.isOn(act::WeaponModifier::AddSpreadFire))
            stats->bow_add_value = modifier.value;
        else
            stats->bow_add_value = getBowActorInfoAddValue(item.getName());
    }
}

int getBowActorInfoAddValue(const sead::SafeString& name) {
    auto* info = ksys::act::InfoData::instance();
    al::ByamlIter iter;
    if (!info)
        return 0;

    if (!info->getActorIter(&iter, name.cstr()))
        return 0;

    if (ksys::act::getBowIsLeadShot(iter))
        return ksys::act::getBowLeadShotNum(iter);

    if (ksys::act::getBowIsRapidFire(iter))
        return ksys::act::getBowRapidFireNum(iter);

    return 1;
}

int getWeaponInventoryLife(const sead::SafeString& name) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return 0;
    const int life = ksys::act::getGeneralLife(info, name.cstr());
    return act::WeaponModifierInfo::getLifeMultiplier() * life;
}

// NON_MATCHING: register allocation only (the original keeps the result in x3 and the current pane in x0)
// 0x7100aa0cb4 (placeholder name): follows the names of `entries` down the pane tree of `layout`; the last pane found
// (null if one is missing, or if the first name is empty)
nn::ui2d::Pane* sub_7100AA0CB4(eui::LayoutEx* layout, const WidgetPathEntry* entries, s32 count) {
    nn::ui2d::Pane* pane = layout->mPane;
    nn::ui2d::Pane* found = nullptr;
    for (s32 i = 0; i < count; ++i) {
        const char* name = entries[i].name;
        if (name[0] == sead::SafeString::cNullChar)
            break;
        pane = pane->FindPaneByName(name, true);
        if (!pane)
            return nullptr;
        found = pane;
    }
    return found;
}

// 0x7100aa0d40 (placeholder name): the same through the parts layouts
nn::ui2d::Parts* sub_7100AA0D40(nn::ui2d::Layout* layout, const WidgetPathEntry* entries, s32 count) {
    nn::ui2d::Parts* parts = nullptr;
    for (s32 i = 0; i < count; ++i) {
        const char* name = entries[i].name;
        if (name[0] == sead::SafeString::cNullChar)
            break;
        parts = layout->FindPartsPaneByName(name);
        if (!parts)
            return nullptr;
        layout = parts->mPartsLayoutLink.layout;
    }
    return parts;
}

// 0x7100aa1d5c (placeholder name): restarts `layout` (when it is stopped / closed) and lets its animator continue from
// the one of `other`
void sub_7100AA1D5C(eui::LayoutEx* layout, eui::LayoutEx* other, bool a3) {
    if (!layout)
        return;
    if (layout->_91 == 3 || layout->_91 == 0) {
        if (a3)
            layout->sub_7100BDDE7C(false, 0, true);
        else
            layout->sub_7100BDDE7C(false, 1, true);
    }
    if (other && layout->_70 && other->_91 && other->_70)
        layout->_70->ContinueFrom(*other->_70);
}

// 0x7100aa16e8 (placeholder name): whether `pane` and all of its ancestors are visible (false for null)
bool sub_7100AA16E8(const nn::ui2d::Pane* pane) {
    if (!pane)
        return false;
    do {
        if (!pane->IsVisible())
            return false;
        pane = pane->GetParent();
    } while (pane);
    return true;
}

// 0x7100aa7a50
int sub_7100AA7A50(const sead::SafeString& name, bool is_shield) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return 0;
    if (is_shield)
        return ksys::act::getWeaponCommonGuardPower(info, name.cstr());
    return ksys::act::getAttackPower(info, name.cstr());
}

// 0x7100aa7ac8
int sub_7100AA7AC8(const PouchItem& item) {
    WeaponStats stats;
    getWeaponStats(item, &stats);
    int power = stats.power;
    if (item.getType() == PouchItemType::Bow)
        power *= sead::Mathi::max(stats.bow_add_value, 1);
    return power;
}

// 0x7100aa7b1c
int sub_7100AA7B1C(const ksys::act::acc::Weapon& weapon, int kind) {
    if (kind == 3)
        return sub_71002F0CB4(weapon);

    int power = weapon.getAttackPower();
    if (kind == 1) {
        int value;
        auto* modifier = sub_71002F05D8(weapon);
        if (modifier && modifier->flags.isOn(act::WeaponModifier::AddSpreadFire))
            value = modifier->value;
        else
            value = getBowActorInfoAddValue(weapon.getName());
        power *= sead::Mathi::max(value, 1);
    }
    return power;
}

// NON_MATCHING: the original peels the first iteration of the inlined calcLength loop (it knows the first character is
// not NUL from the isEmpty check); ours re-tests it
// 0x7100aa7bac
bool sub_7100AA7BAC(sead::BufferedSafeString* out) {
    auto* mgr = PauseMenuDataMgr::instance();
    if (!mgr)
        return false;
    auto* name = mgr->getEquippedItemName(PouchItemType::Bow);
    if (!name)
        return false;
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return false;
    const char* arrow_name = ksys::act::getBowArrowName(info, name->cstr());
    if (!arrow_name)
        return false;
    if (sead::SafeString(arrow_name).isEmpty())
        return false;
    if (out)
        out->copy(arrow_name);
    return true;
}

bool isMasterSwordActorName(const sead::SafeString& name) {
    return name == "Weapon_Sword_070";
}

act::CreateEquipmentSlot getCreateEquipmentSlot(ui::PouchItemType type) {
    switch (type) {
    case ui::PouchItemType::Sword:
        return act::CreateEquipmentSlot::WeaponSword;
    case ui::PouchItemType::Bow:
        return act::CreateEquipmentSlot::WeaponBow;
    case ui::PouchItemType::Shield:
        return act::CreateEquipmentSlot::WeaponShield;
    case ui::PouchItemType::ArmorHead:
        return act::CreateEquipmentSlot::ArmorHead;
    case ui::PouchItemType::ArmorUpper:
        return act::CreateEquipmentSlot::ArmorUpper;
    case ui::PouchItemType::ArmorLower:
        return act::CreateEquipmentSlot::ArmorLower;
    default:
        return act::CreateEquipmentSlot::Length;
    }
}

ui::EquipmentSlot getEquipmentSlot(act::CreateEquipmentSlot slot) {
    switch (slot) {
    case act::CreateEquipmentSlot::WeaponSword:
        return ui::EquipmentSlot::WeaponRight;
    case act::CreateEquipmentSlot::WeaponShield:
        return ui::EquipmentSlot::WeaponLeft;
    case act::CreateEquipmentSlot::WeaponBow:
        return ui::EquipmentSlot::WeaponBow;
    case act::CreateEquipmentSlot::ArmorHead:
        return ui::EquipmentSlot::ArmorHead;
    case act::CreateEquipmentSlot::ArmorUpper:
        return ui::EquipmentSlot::ArmorUpper;
    case act::CreateEquipmentSlot::ArmorLower:
        return ui::EquipmentSlot::ArmorLower;
    default:
        return ui::EquipmentSlot::Invalid;
    }
}

bool createEquipmentFromItem(const ui::PouchItem* item, const sead::SafeString& caller) {
    if (!item) {
        return false;
    }

    auto* mgr = act::CreatePlayerEquipActorMgr::instance();
    if (!mgr) {
        return false;
    }

    auto type = item->getType();
    auto slot = getCreateEquipmentSlot(type);
    int slot_idx = (int)slot;

    if (slot <= act::CreateEquipmentSlot::WeaponBow) {
        act::WeaponModifierInfo modifier(*item);
        mgr->requestCreateWeapon(slot_idx, item->getName(), item->getValue(), &modifier, caller);
        return true;
    }

    if (slot <= act::CreateEquipmentSlot::ArmorLower) {
        mgr->requestCreateArmor(slot_idx, item->getName(), item->getValue(), caller);
        return true;
    }

    return false;
}

// NON_MATCHING: equipment countdown loops keep additional bounds comparisons.
void addItemForDebug(const sead::SafeString& name, int value) {
    if (name.isEmpty())
        return;
    auto* pouch = PauseMenuDataMgr::instance();
    const auto type = PauseMenuDataMgr::getType(name, nullptr);
    if (type == PouchItemType::Arrow) {
        while (value > 0) {
            pouch->addNonDefaultItem(name, 1, nullptr);
            --value;
        }
    } else if (type <= PouchItemType::Shield) {
        while (value > 0) {
            pouch->addNonDefaultItem(
                name, ksys::act::getGeneralLife(ksys::act::InfoData::instance(), name.cstr()),
                nullptr);
            --value;
        }
    } else if (type <= PouchItemType::ArmorLower) {
        while (value > 0) {
            pouch->addNonDefaultItem(name, -1, nullptr);
            --value;
        }
    } else {
        pouch->addNonDefaultItem(name, value, nullptr);
    }
    ksys::gdt::Manager::instance()->onChangedByDebug();
}

bool sub_7100A9F458() {
    return Unk_71025d6ac0::instance()->sub_71009685AC(0);
}

}  // namespace uking::ui
