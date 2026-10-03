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

// Facade functions of the 0x7100a94000-0x7100aa0000 UI wrapper TU called by AI actions (placeholder names; the
// signatures come from the callers, none is decompiled yet).
void sub_7100A94B40(bool display, bool display_ex, bool get_demo);
void sub_7100A95B44(const sead::SafeString& item_name);
bool sub_7100A96DDC(bool a1);
bool sub_7100A97024();
bool sub_7100A97250(bool a1);
bool sub_7100A97498();
bool sub_7100A976C4(int a1, bool a2);
bool sub_7100A97B14();
void sub_7100A98340();
void sub_7100A98358();
bool sub_7100A98558();
void sub_7100A98598();
void sub_7100A98AE4();
void sub_7100A98BB0();
void sub_7100A98EE4();
bool sub_7100A98FA8();
void sub_7100A990EC();
void sub_7100A99860();
void sub_7100A9991C(const sead::SafeString& counter_name);
void sub_7100A99A08();
void sub_7100A99BB0();
void sub_7100A99D70();
bool sub_7100A99E2C();
void sub_7100A99FE8();
void sub_7100A9A0A4(int value);
void sub_7100A9A160();
void sub_7100A9A21C(const sead::Vector3f* world_pos, int scale_level);
void sub_7100A9D748();
void sub_7100A9EBB8(int menu_type);
void sub_7100A9F038();
void sub_7100A9F048(int photo_no);
void sub_7100A9F08C(const sead::SafeString& actor_name);
void sub_7100A9F4C8();
void sub_7100A9F4E0();

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
