#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/actWeapon.h"

namespace eui {
class LayoutEx;
}

namespace uking::act {
enum class CreateEquipmentSlot : u8;
}

namespace uking::ui {
class ScreenChildEx;
}

namespace ksys::act {
class Actor;
}

namespace eui {
class MessageString;
}

namespace xlink2 {
class HandleSLink;
}

namespace uking {
class NpcShopData;
}

namespace uking::ui {

// 0x71010ad724: source namespace inferred from the screen-name lookup's UI consumers.
s32 getScreenIdxByName(const char* name);
bool getRuntimeTipFlag(s32 index);
void sub_7100A94AF0();
// 0x7100a9b2ac: sets a flag of the UI manager (`_64c4d`).
void sub_7100A9B2AC();
bool sub_7100A96688();
s32 sub_7100A968B4();
// 0x7100a9a4bc (uiMiscFacade.cpp; declaration added by lane4 s44 for CanMarkMapPin).
bool sub_7100A9A4BC();
// 0x7100a9d03c (uiMiscFacade.cpp): the number of obtained runes (remote bombs count twice).
int sub_7100A9D03C();
bool openPickUpScreen(ksys::act::Actor* actor);

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
// 0x7100aa6f90 (uiManagerFacade.cpp; declaration added by lane4 s45 for CheckMasterSwordState): 1 without a value; with
// one, 2 for the true form Master Sword and 0 otherwise.
s32 sub_7100AA6F90(const PouchItem& item);

// 0x7100aa248c (CSV: ui::getMessage): looks up `label` in the message set `message_set`; returns 0
// if found.
int getMessage(const sead::SafeString& message_set, const sead::SafeString& label,
               eui::MessageString* out);

// 0xa9bfa8 (CSV: return0; always false).
bool return0();

int getItemHitPointRecover(const sead::SafeString& name);

void getWeaponStats(const PouchItem& item, WeaponStats* stats);
int getBowActorInfoAddValue(const sead::SafeString& name);

int getWeaponInventoryLife(const sead::SafeString& name);
bool isMasterSwordActorName(const sead::SafeString& name);
// 0x7100aa7a50: the guard power (`is_shield`) or the attack power of the actor `name` (0 without actor info).
int sub_7100AA7A50(const sead::SafeString& name, bool is_shield);
// 0x7100aa7ac8: the weapon's power from getWeaponStats, multiplied by the bow's add value (at least 1) for bows.
int sub_7100AA7AC8(const PouchItem& item);
// 0x7100aa7b1c: kind 3: the shield guard power, otherwise the attack power (multiplied by the bow's add value for kind 1).
int sub_7100AA7B1C(const ksys::act::acc::Weapon& weapon, int kind);
// 0x7100aa7bac: the arrow type of the equipped bow, copied to `out` if given; false if there is none.
bool sub_7100AA7BAC(sead::BufferedSafeString* out);
// 0x7100a951b0 (uiPouchFacade.cpp)
bool sub_7100A951B0();

// TODO: move these to another translation unit (TBD)
// Do not implement until the location is figured out
bool isOneHitObliteratorActorName(const sead::SafeString& name);
int getItemGeneralLife(const char* name);
bool formatSpecialAttackPower(s32 power, sead::BufferedSafeString* out);
bool shouldUseWeaponSword503();
bool sub_7100A9FC20(const sead::SafeString& name, s32* out, bool force);

// TODO: move this to yet another translation unit (TBD but not the same one as the above)
void addItemForDebug(const sead::SafeString& name, int value);

bool setShowCheckPoint(s32 icon_type, const sead::SafeString& counter_name);
bool setShowFlyDistance(const sead::SafeString& distance);
bool setShowGolfCount(const sead::SafeString& counter_name);
bool setShowRaceResult(s32 result_type);
void openSkipScreen(bool with_button);
void showInfoOverlay(s32 type);
// 0x7100a95924 (CSV ui::showInfoOverlayWithString): opens the main screen's info overlay `type` with `text`.
void showInfoOverlayWithString(s32 type, const sead::SafeString& text);
// 0x7100a99278 (CSV recoverMasterSword)
void recoverMasterSword(bool only_if_broken, bool show_message);
// 0x710105df2c (CSV ui::playSound): plays the UI sound `label` (forwards to UiSoundMgr::playSound);
// `handle` receives the sound's handle and may be null.
void playSound(const sead::SafeString& label, xlink2::HandleSLink* handle);
void showRuntimeTip(s32 type);
// 0x7100a96568 (defined in uiScreenFacade.cpp): marks the main screen 3D view as needing a refresh.
void mainScreen3DStuff();
// 0x7100a9f53c: finds the dungeon (shrine) whose entrance is within `radius` of `pos` and stores its name in
// `out_name` (forwards to Manager::sub_7100A7F2EC). Used by DungeonEntranceRoot::enter_.
bool findDungeonNameForPositionImpl(f32 radius, sead::SafeString* out_name, const sead::Vector3f* pos);
// 0x7100a95924 (CSV ui::showInfoOverlayWithString): shows the info overlay of `type` with the extra text `text`.
// Declared only.
void showInfoOverlayWithString(s32 type, const sead::SafeString& text);
// 0x7100a95f5c: called by PlayerCutFall::enter_ with the player's current tip type (0x54). Not
// decompiled yet.
void sub_7100A95F5C(s32 type);

// 0x7100a9e358 (CSV closeFadeStatus): closes the fade status screen if it is open; returns whether it did.
bool closeFadeStatus();
// 0x7100a9e2d4 (CSV openFadeStatus): opens the fade status screen if it is closed; returns whether it did.
bool openFadeStatus();

// 0x7100aa9728 (placeholder name): sets the UI manager's byte at 0x652e8 (called by the ScreenBootUp ctor).
void sub_7100AA9728();

// 0x7100a94158: whether the UI manager exists.
bool uiManagerInitialised();

// 0x7100aa8f10 (placeholder name): bit 12 of the UI manager's flag word.
bool sub_7100AA8F10();

// 0x7100aa34a4 (placeholder name; declared only, 760 B): sets the button icon `icon` (a UI button id; 28 / 29 depend on
// the JumpButtonChange flag) on the parts pane `parts`; `name` is the icon pane's name.
void sub_7100AA34A4(void* parts, const sead::SafeString& name, s32 icon);

// 0x7100aa8f78: `actor` itself, or the player if there is none.
ksys::act::Actor* getPlayerActor(ksys::act::Actor* actor);

// 0x7100aa7d38 (placeholder name): the name of hero soul `index` (-1: the empty string) from a UI-side
// table of 16-byte SafeStrings.
const sead::SafeString& sub_7100AA7D38(s32 index);

// 0x7100aa0a5c (CSV ui::createAndLoadScreenIfNeededImpl): forwards `id` to Manager::createAndLoadScreenIfNeeded
// (the second parameter is unused; callers pass nullptr).
void createAndLoadScreenIfNeededImpl(s32 id, sead::Heap* heap);

// 0x7100aa0748 (CSV ui::createAndLoadScreen): loads the screen `id` unless it is loaded already; mode -1 loads it with
// a heap of its own (a frame heap below `heap`, or the UI heap).
bool createAndLoadScreen(s32 id, s8 target, bool a3, sead::Heap* heap, s32 mode);
// 0x7100aa08cc (CSV ui::unloadScreen)
bool unloadScreen(s32 id);
// 0x7100aa09d8
bool sub_7100AA09D8(s32 id);
// 0x7100aa0b6c / 0x7100aa0bb0 (uiMgrFacade2.cpp; placeholder names)
f32 sub_7100AA0B6C(f32 degrees);
void sub_7100AA0BB0(sead::Vector2f* vec, f32 degrees);
// 0x7100aa0c04
void sub_7100AA0C04(sead::Vector3f* pos);
// 0x7100aa0aa4 (CSV ui::getScreenWidgetMaybe): the widget `group` (index 0) of the screen `id` (null if not loaded).
ScreenChildEx* getScreenWidgetMaybe(s32 id, s32 group);

// Existing UI facade definition at 0x7100a9ef44.
void sellPictureBookDemo(s32 value);
void sellPictureBookUIEnd();
bool sellPictureBookUIEnd2();

// Existing UI facade definitions at 0x7100a9e42c, 0x7100a9e4a0 and 0x7100a9732c.
bool checkWeaponFreeSlotImpl(const sead::SafeString& name, s32 count);
int sub_7100A9E4A0(const sead::SafeString& name);
void sub_7100A9732C();
// Existing UI facade definition at 0x7100a96eb8.
void sub_7100A96EB8();
// 0x7100a9e458: declared only; delegates the signed count change to the pouch manager.
void increasePouchNumImpl(const sead::SafeString& name, s32 count);

// 0x7100aa25d4: sets matching widgets and returns their count.
s32 setWidgetString(eui::LayoutEx* layout, const sead::SafeString& widget_name, const sead::SafeString& text);
// 0x7100aa256c: the existing message-string overload.
s32 setWidgetString(eui::LayoutEx* layout, const sead::SafeString& widget_name,
                    const eui::MessageString& message);
// 0x7100aa37ec
const char* getDecimalSeparator(bool a1);

// 0x7100a6d3dc (CSV ui::getHeap; declaration only)
sead::Heap* getHeap();

// Facade functions of the 0x7100a94000-0x7100aa0000 UI wrapper TU called by AI actions (placeholder names; the
// signatures come from the callers, none is decompiled yet).
void sub_7100A94B40(bool display, bool display_ex, bool get_demo);
void sub_7100A95B44(const sead::SafeString& item_name);
bool sub_7100A96DDC(bool a1);
bool sub_7100A97024();
bool sub_7100A9C15C();
// 0xa9a644 (lane2 s21; placeholder name): forwards the actor to the manager at GOT 0x7102 57be20 (null-checked); 1.1 KB callee 0x963ce8.
void sub_7100A9A644(ksys::act::Actor* actor);
bool sub_7100A97250(bool a1);
bool sub_7100A97498();
bool sub_7100A976C4(int a1, bool a2);
bool sub_7100A97B14();
void sub_7100A98340();
void sub_7100A98358();
bool sub_7100A98558();
void sub_7100A98598();
bool sub_7100A98AE4();
bool sub_7100A98BB0();
bool sub_7100A98EE4();
bool sub_7100A98FA8();
void sub_7100A990EC();
bool sub_7100A99860();
bool sub_7100A9991C(const sead::SafeString& counter_name);
bool sub_7100A99A08();
bool sub_7100A99BB0();
bool sub_7100A99D70();
bool sub_7100A99E2C();
bool sub_7100A99FE8();
bool sub_7100A9A0A4(int value);
bool sub_7100A9A160();
void sub_7100A9A21C(const sead::Vector3f* world_pos, int scale_level);
bool sub_7100A9BAEC(int state);
bool sub_7100A9D0F4();
bool sub_7100A9D118();
bool sub_7100A9D140();
void sub_7100A9D168(float x, float y, float z);
bool sub_7100A9D1C0();
bool sub_7100A9D1E8();
int sub_7100A9D290();
void sub_7100A9D1A0(const float* levels);
void sub_7100A9D210(float x, float y);
void sub_7100A9D748();
void sub_7100A9EBB8(int menu_type);
void sub_7100A9F038();
void sub_7100A9F048(int photo_no);
void sub_7100A9F08C(const sead::SafeString& actor_name);
void sub_7100A9F4C8();
void sub_7100A9F4E0();

// More facade functions of the UI wrapper TU (placeholder names; signatures from the AI action callers).
bool sub_7100A984C0();
bool sub_7100A98498();
void sub_7100A99104();
void sub_7100A9ED74();
void sub_7100A9F46C(bool a1);
bool sub_7100A9F4AC();
bool sub_7100A992CC(s32 text_type);
bool sub_7100A993BC();
void sub_7100A9F8B0();
bool sub_7100A9F91C();
void sub_7100A9C0FC(s32 cause);
void sub_7100A98284(bool a1);
void sub_7100A9853C();
void sub_7100A98580();
void sub_7100A9826C();
void sub_7100A98394();
bool sub_7100A983DC();
void sub_7100A98408(const sead::SafeString& name);
void sub_7100A94B08();
void sub_7100A94B70(bool a1);
void sub_7100A94D54();
void sub_7100A9F0CC();
bool sub_7100A9F104();
bool sub_7100A9A938(s32 a1);
void sub_7100A9F138();
void sub_7100A9F358();
bool sub_7100A979BC();
bool sub_7100A973E0();
bool sub_7100A96F6C();
bool sub_7100A9F134();
void sub_7100A9F108();
bool sub_7100A9F458();
void sub_7100A9F410(s32 reaction_num);
void sub_7100A9F27C(bool a1);
bool sub_7100A9EBEC();
bool sub_7100A9A3F8();
bool sub_7100A94AC8();
bool sub_7100A94E08();
bool sub_7100A990BC();
void sub_7100A9E5F8(s32 category);
void sub_7100A9E584(s32 category);
void sub_7100A9E6B0(s32 type);
bool sub_7100A9E864();
bool sub_7100A9F57C(s32* out_index, const sead::Vector3f& pos, f32 radius);
void sub_7100A9A308(s32 index, bool is_player_close);
void sub_7100A97550(s32 add_num);
void sub_7100A970DC(s32 add_num);
void sub_7100A97C6C(s32 add_num, s32 type);
bool sub_7100A98514();
bool sub_7100A9E7AC();
bool sub_7100A9E91C();
bool sub_7100A98C80();
bool sub_7100A98D4C();
bool sub_7100A98E18();
void sub_7100A98474(s32 rank);
bool sub_7100A9844C();
void sub_7100A98428(NpcShopData* shop_data);
// Shop facade (uiShopFacade.cpp) and one declared-only helper (0x7100a982bc: `sub_7100A982BC(shop_data, selected)`).
void sub_7100A98370(NpcShopData* shop_data);
void sub_7100A99060(NpcShopData* shop_data);
void sub_7100A99084();
void sub_7100A990A0();
bool sub_7100A98304();
bool sub_7100A983B0();
void sub_7100A984F0(NpcShopData* shop_data);
void sub_7100A985B8(NpcShopData* shop_data);
bool sub_7100A982BC(NpcShopData* shop_data, bool selected);
bool openMinigameScreenForTimer(bool count_down);
bool minigameScreenHideTimer();
void minigameScreenUpdateTimer(s64 time_ms);

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

void uiManagerUpdateIsDungeon();

}  // namespace uking::ui

namespace wm {
// 0x7100a9d918 (uiWorldFacade.cpp)
bool isFindDungeonActivated();
// 0x7100a9d800 (CSV unnamed; declared only)
s32 sub_7100A9D800();
}  // namespace wm

