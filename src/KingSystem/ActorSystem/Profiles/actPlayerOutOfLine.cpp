#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_7101E7C2B4.h"
#include "Game/Damage/dmgDamageMgrPlayer.h"

namespace ksys::act {

// Own file: the original calls these out of line (x_5 from sub_7100877BD8, stillAlive from m375); a
// same-file definition would be inlined into the callers.
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

bool Player::stillAlive() {
    auto* life = getLife();
    if (!life || *life > 0 || hasFairy())
        return true;
    return canUseMiphaGrace();
}

void Player::sub_7100884578() {
    if (auto* mgr = sead::DynamicCast<uking::dmg::DamageMgrPlayer>(getDamageMgr()))
        mgr->_22c = uking::sUnk_7101e7c2b0;
}

}  // namespace ksys::act
