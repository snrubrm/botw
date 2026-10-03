#pragma once

#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
class BaseProc;
}  // namespace ksys::act

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

// 0x71008bad74 (CSV name): calls Demo006_0 at the player's matrix.
bool callPlayerGameOverDemo(ksys::act::Actor* player);

}  // namespace uking
