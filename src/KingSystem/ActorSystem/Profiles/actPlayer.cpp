#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

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

// NON_MATCHING: x_5() gets inlined here (it is defined in this file; the original calls it), and the
// original selects the stored speed with an integer csel
void Player::sub_7100877BD8() {
    const sead::Vector3f& translation = getASList()->sub_710115D2D4();
    f32 speed = translation.length();
    if (speed < 0.001f)
        speed = 0.0f;
    f32 value = speed;
    if (_cf4.isOnBit(27))
        value = 0.0f;
    _20bc = value;
    _20c0 = value;
    if (speed == 0.0f)
        return;
    const u32 angle = sead::Mathf::atan2Idx(translation.x, translation.z);
    _1c68 = (x_5().value + angle) & util::sUnk_7101EC6BA0;
}

s32 Player::playerWeapons_return0() {
    return 0;
}

}  // namespace ksys::act
