#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace ksys::act {

// Separate TU from actPlayer.cpp: Player::m370 / m203 / m306 (inline in the header) tail-call x_34 / x_21 / x_44
// in the original (0x877550 / ...), so these must not be visible for inlining there.
void Player::x_34(f32 value, bool a2) {
    value *= 1.0f / 30.0f;
    if (!a2)
        value *= _20f0;
    decreaseStaminaForActionMaybe(value);
}

bool Player::x_21() {
    return mASList->x_1(1, 1) == "GrabPouchUpper";
}

bool Player::x_44() {
    if (_c44.isOnBit(20)) {
        if (PlayerInfo::instance()->getStaminaCurrentMax() !=
            PlayerInfo::instance()->getMaxStaminaFromPlayerActor())
            return true;
    }
    return false;
}

}  // namespace ksys::act
