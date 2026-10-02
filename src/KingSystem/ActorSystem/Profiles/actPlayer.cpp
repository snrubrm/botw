#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace ksys::act {

// NON_MATCHING: members are not declared yet
Player::~Player() = default;

bool Player::isSurfingOnGround() const {
    return _cfc.isOnBit(0);
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: operand order of the XZ length addition (z*z + x*x in the original)
Player::Unk1 Player::x_5() {
    sead::Vector3f dir;
    _1b18.getBase(dir, 2);
    dir.normalize();
    if (sead::Vector2f(dir.x, dir.z).length() == 0.0f) {
        _1b18.getBase(dir, 1);
        dir.normalize();
    }
    return Unk1(sead::Mathf::atan2Idx(dir.x, dir.z));
}

}  // namespace ksys::act

namespace ksys::act {

s32 Player::playerWeapons_return0() {
    return 0;
}

}  // namespace ksys::act
