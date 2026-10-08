#include "Game/Damage/dmgDamageMgrNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actImpulseBaseProcLink.h"

namespace uking::dmg {

// NON_MATCHING: the original shares one `str z` between the three copy paths (sunk into a common block); ours stores
// z in each path.
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
        const sead::Vector3f* src;
        if (!link)
            src = &sead::Vector3f::zero;
        else
            src = &link->_10._10;
        *out = *src;
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

bool DamageMgrNPC::getPosition(sead::Vector3f* out) {
    switch (getDamageType()) {
    case 0: {
        auto* info = sub_71007A255C(mActor, 0);
        if (!info)
            return false;
        *out = info->_0;
        return true;
    }
    case 2: {
        auto* link = mActor->getImpulseBaseProcLink();
        const sead::Vector3f* src;
        if (!link)
            src = &sead::Vector3f::zero;
        else
            src = &link->_10._4c;
        *out = *src;
        return true;
    }
    case 3: {
        const auto& mtx = mActor->getMtx();
        out->x = mtx(0, 3);
        out->y = mtx(1, 3);
        out->z = mtx(2, 3);
        if (_80.x * _80.x + _80.y * _80.y + _80.z * _80.z > 0.0f)
            *out -= _80 * 0.4f;
        return true;
    }
    default:
        return false;
    }
}

bool DamageMgrNPC::m35(sead::Matrix34f* out) {
    switch (getDamageType()) {
    case 0: {
        auto* info = sub_71007A255C(mActor, 0);
        if (!info)
            return false;
        *out = info->_58;
        return true;
    }
    case 2: {
        auto* link = mActor->getImpulseBaseProcLink();
        const sead::Matrix34f* src;
        if (!link)
            src = &sead::Matrix34f::ident;
        else
            src = &link->_10._1c;
        *out = *src;
        return true;
    }
    default:
        *out = sead::Matrix34f::ident;
        return false;
    }
}

// NON_MATCHING: same structure; the original merges the z store of all paths (sunk) and negates z as an integer
// (eor with the sign bit) in the last path.
bool DamageMgrNPC::m31(sead::Vector3f* out) {
    switch (getDamageType()) {
    case 0: {
        auto* info = sub_71007A255C(mActor, 0);
        if (info) {
            *out = info->_94;
            return true;
        }
    }
        [[fallthrough]];
    case 3: {
        if (_80.x * _80.x + _80.y * _80.y + _80.z * _80.z > 0.0f) {
            *out = _80;
        } else {
            const auto& mtx = mActor->getMtx();
            out->set(-mtx(0, 2), -mtx(1, 2), -mtx(2, 2));
        }
        return true;
    }
    case 2: {
        auto* link = mActor->getImpulseBaseProcLink();
        const sead::Vector3f* src;
        if (!link)
            src = &sead::Vector3f::zero;
        else
            src = &link->_10._10;
        *out = *src;
        return true;
    }
    default:
        return false;
    }
}

}  // namespace uking::dmg
