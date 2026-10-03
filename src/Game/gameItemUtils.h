#pragma once

namespace sead {
class Heap;
template <typename T>
class SafeStringBase;
using SafeString = SafeStringBase<char>;
}  // namespace sead
namespace uking::act {
struct WeaponModifierInfo;
}  // namespace uking::act

namespace uking {

enum class SleepAfterInit : bool {
    Yes = true,
    No = false,
};

enum class SpawnViaCarryBox : bool {
    Yes = true,
    No = false,
};

// 710073c5b4
void spawnDroppedInventoryItem(const char* name, sead::Heap* heap, int life,
                               SleepAfterInit sleep_after_init,
                               const uking::act::WeaponModifierInfo* weapon_modifiers,
                               SpawnViaCarryBox spawn_via_carry_box, float rotate_y,
                               float rotate_z);
// 0x710073bb1c (placeholder name): the comma-separated item tags SetGetFlag looks for.
const char* sub_710073BB1C();
// 0x710073bd0c (CSV removeFromInventory; declaration only): unequips the weapon `name` in the pouch
// and refreshes the main screen.
void removeFromInventory(const sead::SafeString& name);
}  // namespace uking
