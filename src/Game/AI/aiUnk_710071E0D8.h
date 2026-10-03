#pragma once

namespace ksys::act {
class Actor;
}  // namespace ksys::act

// Free helper at 0x710071e0d8 (unnamed in the CSV; the TU around 0x710071e000 is not identified). Called
// by PriestBossFastWarpAttack::enter_ / leave_.
// Sets the gravity of the actor's "Body" rigid body set to 0 (`hover`) or 1, and switches its character
// controller's motion type (hover / default) and gravity accordingly.
void sub_710071E0D8(bool hover, ksys::act::Actor* actor);
