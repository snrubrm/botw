#include "Game/Damage/dmgDamageMgrNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actImpulseBaseProcLink.h"

namespace uking::dmg {

// NON_MATCHING: the original shares one `str z` between the three copy paths (tail merged); ours stores z in each
// path. Also the csel of the zero vector has the opposite condition.
bool DamageMgrNPC::getAttackPos(sead::Vector3f* out) {
    switch (getDamageType()) {
    case 0: {
        auto* info = sub_71007A255C(mActor, 0);
        if (!info)
            return false;
        *out = info->_c;
        return true;
    }
    case 2: {
        auto* link = mActor->getImpulseBaseProcLink();
        *out = !link ? sead::Vector3f::zero : link->_10._10;
        return true;
    }
    case 3: {
        if (_80.x * _80.x + _80.y * _80.y + _80.z * _80.z > 0.0f) {
            *out = _80;
        } else {
            const auto& mtx = mActor->getMtx();
            out->set(-mtx(0, 2), -mtx(1, 2), -mtx(2, 2));
        }
        return true;
    }
    default:
        return false;
    }
}

}  // namespace uking::dmg
