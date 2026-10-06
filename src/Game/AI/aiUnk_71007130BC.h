#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
}

// NPC AI helpers (TU 0x7100711000-0x7100714800, lane2 s21; placeholder names = addresses).

// 0x710071300c: the NPC stance name for `idx` ("" / "Crouch" / "Sit" / "SitOnObject"; a function-local static array,
// no bounds check).
const sead::SafeString& sub_710071300C(s32 idx);

// 0x71007130bc: null-safe: `on` -> Actor::x_6() else setEnabledTalkAndLockOn(actor, false).
void sub_71007130BC(ksys::act::Actor* actor, bool on);

// 0x7100713564: for an actor with the tag 0x207cbce1, sets the game data `<actor>_AttackedState` to
// `clamp(count, 0, 3)`.
void sub_7100713564(ksys::act::Actor* actor, s32 count);

namespace ksys::world {
class WeatherMgr;
}

namespace wm {
// 0x71010e85ec (CSV name; declaration only): the world manager's weather manager (null if there is
// no world manager).
ksys::world::WeatherMgr* getWeatherMgr();
// 0x7100ee88ac (CSV name; declaration only): whether it is raining, snowing or there is a thunderstorm.
bool isRainingOrSnowingOrThunderStorm(bool a1);
// 0x7100712418 (CSV name): forwards to isRainingOrSnowingOrThunderStorm.
bool callIsRainingOrSnowingOrThunderStorm(bool a1);
}  // namespace wm
