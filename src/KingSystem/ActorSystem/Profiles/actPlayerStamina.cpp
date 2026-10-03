#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace ksys::act {

// Separate TU from actPlayer.cpp: Player::m370 (inline in the header) tail-calls x_34 in the original
// (0x877550), so x_34 must not be visible for inlining there.
void Player::x_34(f32 value, bool a2) {
    value *= 1.0f / 30.0f;
    if (!a2)
        value *= _20f0;
    decreaseStaminaForActionMaybe(value);
}

}  // namespace ksys::act
