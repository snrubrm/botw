#pragma once

#include <prim/seadSafeString.h>
#include "Game/Actor/actWeapon.h"

namespace uking::act {
enum class CreateEquipmentSlot : u8;
}

namespace eui {
class MessageString;
}

namespace uking::ui {

enum class EquipmentSlot;
enum class PouchItemType;
class PouchItem;

struct WeaponStats {
    int durability{};
    /// Attack power (for offensive weapons) or guard power (for shields).
    int power{};
    act::WeaponModifierInfo modifier{};
    /// Bow modifier value ("add value") or 0 for weapons that are not bows.
    int bow_add_value{};
};

bool isMasterSwordItem(const PouchItem& item);

// 0x7100aa248c (CSV: ui::getMessage): looks up `label` in the message set `message_set`; returns 0
// if found.
int getMessage(const sead::SafeString& message_set, const sead::SafeString& label,
               eui::MessageString* out);

int getItemHitPointRecover(const sead::SafeString& name);

void getWeaponStats(const PouchItem& item, WeaponStats* stats);
int getBowActorInfoAddValue(const sead::SafeString& name);

int getWeaponInventoryLife(const sead::SafeString& name);
bool isMasterSwordActorName(const sead::SafeString& name);

// TODO: move these to another translation unit (TBD)
// Do not implement until the location is figured out
bool isOneHitObliteratorActorName(const sead::SafeString& name);
int getItemGeneralLife(const char* name);

// TODO: move this to yet another translation unit (TBD but not the same one as the above)
void addItemForDebug(const sead::SafeString& name, int value);

void setShowCheckPoint(s32 icon_type, const sead::SafeString& counter_name);
void setShowFlyDistance(const sead::SafeString& distance);
void setShowGolfCount(const sead::SafeString& counter_name);
void setShowRaceResult(s32 result_type);
void showInfoOverlay(s32 type);
void showRuntimeTip(s32 type);
// 0x7100a95f5c: called by PlayerCutFall::enter_ with the player's current tip type (0x54). Not
// decompiled yet.
void sub_7100A95F5C(s32 type);

void minigameScreenMove();

int countCookResultsCheck(const sead::SafeString& name, s32 effect_type);
int countCookResultsAllOk(const sead::SafeString& name);
int getItemValue(const sead::SafeString& name);

// TODO: move these to another translation unit (TBD)
// Do not implement until the location is figured out
void applyScreenFade(float progress);

act::CreateEquipmentSlot getCreateEquipmentSlot(ui::PouchItemType type);
ui::EquipmentSlot getEquipmentSlot(act::CreateEquipmentSlot slot);
bool createEquipmentFromItem(const ui::PouchItem* item, const sead::SafeString& caller);

/// 0x7100a9e660 (declared only): whether the pause menu screen exists and is not closed.
bool isPauseMenuScreenNotClosed();

}  // namespace uking::ui
