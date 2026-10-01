#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace ksys::act {

// NON_MATCHING: members are not declared yet
Player::~Player() = default;

bool Player::isSurfingOnGround() const {
    return _cfc.isOnBit(0);
}

}  // namespace ksys::act
