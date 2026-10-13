#pragma once

#include <prim/seadSafeString.h>

// Free functions of the AI utility code at 0x710073bb28 (placeholder names).
// 0x710073bb28: used by StartStaminaUpDemo::oneShot_ with (true, false).
void sub_710073BB28(bool a, bool b);
// 0x710073bb54: polled by IncreasePlayerMaxStamina / WaitForStaminaUpDemoEnd::calc_ until it returns true.
bool sub_710073BB54();

namespace ksys::act {
class Actor;
}

bool actorHasTagCanGetPouch(const sead::SafeString& actor_name);
bool sub_710073BB80(ksys::act::Actor* actor);

// 0x710073bce4 (CSV weaponBroken): removes the actor's weapon from the equipment and refreshes the
// main screen 3D view. 0x710073bd0c (CSV removeFromInventory) does the same for a weapon name.
void weaponBroken(ksys::act::Actor* actor);
// 0x710073bd34 (CSV masterSwordBroken).
void masterSwordBroken();
// 0x710073badc (placeholder name): plays the "mc_DoUnable" UI sound.
void sub_710073BADC();

namespace uking {
void removeFromInventory(const sead::SafeString& name);
}

namespace ksys::evt {
class Metadata;
}
namespace uking::act {
struct WeaponModifierInfo;
}

// Original source namespace is unknown; native inventory utility neighbors select this TU.
void callGetAnotherItemDemo(ksys::evt::Metadata* metadata, const sead::SafeString& actor_name,
                           bool can_get_pouch, bool another_actor, bool option,
                           uking::act::WeaponModifierInfo* modifier);
void getDemoGetAnotherActor(ksys::act::Actor* actor, const sead::SafeString& actor_name,
                           bool can_get_pouch, bool option, uking::act::WeaponModifierInfo* modifier);
