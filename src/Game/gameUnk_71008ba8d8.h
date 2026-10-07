#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
class BaseProc;
}  // namespace ksys::act

namespace ksys {
struct MesTransceiverId;
enum MessageType : u32;
}  // namespace ksys

namespace uking {
class CookItem;
}

namespace ksys::evt {
class BaseProcLinkForEvent;
}

// Event call helpers of the game's event utility TU (0x71008ba108-0x71008bb270, with evt::S7Movie,
// GameScene::callSceneStartDemo, callPlayerRespawnEvent, ...).

namespace ksys::evt {

// 0x71008ba8d8 / 0x71008ba9ac (CSV evt::callEvent_0 / evt::callEvent): build a Metadata for
// event / entry point and call it through evt::Manager (false if there is no Manager). `a4` / `a5`
// set the Metadata's skip-startable-air-check and _13 flags; the matrix overload passes `mtx` and
// uses the "Timeline" type when the entry point is empty.
bool callEvent(act::BaseProc* proc, const sead::SafeString& event, const sead::SafeString& entry,
               bool a4, bool a5);
bool callEvent(act::BaseProc* proc, const sead::SafeString& event, const sead::SafeString& entry,
               const sead::Matrix34f& mtx, bool a5, bool a6);

}  // namespace ksys::evt

namespace uking {

// 0x71008badcc (CSV name; declared only, lane3 s15): the player's respawn event (PlayerHellStartWait::calc_).
bool callPlayerRespawnEvent(ksys::act::Actor* player);

// 0x71008bb56c (CSV callDemo007_1; lane3 s18): calls Demo007_1 for `proc` (FireWood, CookPotRoot).
bool callDemo007_1(ksys::act::BaseProc* proc);

// 0x71008bb274 / 0x71008bb46c (CSV callDemo005_0 / callDemo616_0; lane2 s45, declared only; the signature is read from
// the UI caller sub_7100A9ED78, the result is unused): demo calls for `player` with two strings (map names).
bool callDemo005_0(ksys::act::Actor* player, const sead::SafeString& a, const sead::SafeString& b);
bool callDemo616_0(ksys::act::Actor* player, const sead::SafeString& a, const sead::SafeString& b);

// 0x71008bad74 (CSV name): calls Demo006_0 at the player's matrix.
bool callPlayerGameOverDemo(ksys::act::Actor* player);

// 0x71008baae0 (CSV GameScene::callSceneStartDemo; lane2 s46): callEvent without a proc.
bool callSceneStartDemo(const sead::SafeString& event, const sead::SafeString& entry,
                        const sead::Matrix34f& mtx, bool a4, bool a5);

// 0x71008bb0b4 / 0x71008bb14c (CSV callDemo049_controlsDemo / callDemo025_1_E3Exit; lane2 s46): call the demo at the
// player's matrix (false without a player).
bool callDemo049_controlsDemo(const sead::SafeString& entry);
bool callDemo025_1_E3Exit();

}  // namespace uking

// 0x71008bb1e0 (CSV callCookingDemo; declared in aiCookPotRoot.h as well; the item parameters are unused).
bool callCookingDemo(ksys::act::Actor* actor, const uking::CookItem* a, const uking::CookItem* b);

// 0x71008ba664 / 0x71008ba670 / 0x71008ba67c (CSV getStr_CurrentActorName / getStr_SharpWeaponAddValue /
// getStr_SharpWeaponAddType; lane2 s46): constant event parameter names.
const sead::SafeString& getStr_CurrentActorName();
const sead::SafeString& getStr_SharpWeaponAddValue();
const sead::SafeString& getStr_SharpWeaponAddType();
// 0x71008ba688 (CSV isDemo000Or002; lane2 s46): whether the event of `link` is Demo000_0 or Demo002_0.
bool isDemo000Or002(const ksys::evt::BaseProcLinkForEvent& link);
// 0x71008ba750 (CSV eventMgrHasActiveEvent): without the null check of the Manager.
bool eventMgrHasActiveEvent();
// 0x71008ba760 (placeholder name): the EventSystem's sub_71008AC118() (false without an EventSystem).
bool sub_71008BA760();
// 0x71008ba8ac (placeholder name): sends `type` to `dest` through the Manager (nothing without one).
void sub_71008BA8AC(const ksys::MesTransceiverId& dest, ksys::MessageType type);
// 0x71008bacb8 (placeholder name): calls the Timeline event `event` without entry point or proc (false if empty).
bool sub_71008BACB8(const sead::SafeString& event);
// 0x71008ba7d8 (CSV isActiveEventDemo000Or001Or002)
bool isActiveEventDemo000Or001Or002();
// 0x71008bb7d8 / 0x71008bb878 (placeholder names): whether the active flow is playing / the name of the active event
// (empty without one).
bool sub_71008BB7D8();
const sead::SafeString& sub_71008BB878();

// Global-namespace event state checks of the same TU (lane2 s45, declared only; placeholder names except the CSV one).
bool sub_71008BB600();
bool sub_71008BB804();
bool sub_71008BB830();
bool someEventMgrCheck();
