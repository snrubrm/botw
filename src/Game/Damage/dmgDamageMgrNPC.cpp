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

ksys::phys::MaterialMask* DamageMgrNPC::m33() {
    if (getDamageType() != 0)
        return nullptr;
    auto* info = sub_71007A255C(mActor, 0);
    if (!info)
        return nullptr;
    return &info->_20;
}

// NON_MATCHING: the original tail-calls getDummyBaseProcLink() from each fallback and only builds the stack frame
// around the contact record lookup; ours merges the fallbacks into one non-tail call.
ksys::act::BaseProcLink* DamageMgrNPC::getAttacker() {
    switch (getDamageType()) {
    case 0: {
        auto* info = sub_71007A255C(mActor, 0);
        if (!info)
            return &ksys::act::getDummyBaseProcLink();
        return &info->_d8;
    }
    case 2: {
        auto* link = mActor->getImpulseBaseProcLink();
        if (!link)
            return &ksys::act::getDummyBaseProcLink();
        return &link->mLink;
    }
    default:
        return &ksys::act::getDummyBaseProcLink();
    }
}

// NON_MATCHING: the original tail-calls getDummyBaseProcLink() from each fallback and only builds the stack frame
// around the contact record lookup; ours merges the fallbacks into one non-tail call.
ksys::act::BaseProcLink* DamageMgrNPC::m37() {
    switch (getDamageType()) {
    case 0: {
        auto* info = sub_71007A255C(mActor, 0);
        if (!info)
            return &ksys::act::getDummyBaseProcLink();
        return &info->_e8;
    }
    case 2: {
        auto* link = mActor->getImpulseBaseProcLink();
        if (!link)
            return &ksys::act::getDummyBaseProcLink();
        return &link->mLink;
    }
    default:
        return &ksys::act::getDummyBaseProcLink();
    }
}

bool DamageMgrNPC::m40(s32* out) {
    *out = -1;
    if (getDamageType() != 0)
        return false;
    auto* info = sub_71007A255C(mActor, 0);
    if (!info)
        return false;
    *out = info->_bc;
    return true;
}

bool DamageMgrNPC::m41() {
    if (getDamageType() != 0)
        return false;
    auto* info = sub_71007A255C(mActor, 0);
    if (!info)
        return false;
    return info->_fc & 1;
}

// NON_MATCHING: identical except that the original does not pair the x / y stores of the scaled vector (two str
// instead of an stp) in the kind 2 path.
bool DamageMgrNPC::m32(sead::Vector3f* out) {
    switch (getDamageType()) {
    case 0: {
        auto* info = sub_71007A255C(mActor, 0);
        if (!info)
            return false;
        *out = info->_a0;
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
        auto* factor_link = mActor->getImpulseBaseProcLink();
        const f32 factor = factor_link ? factor_link->_10._8 : 0.0f;
        *out *= factor;
        return true;
    }
    case 3: {
        if (getField54() == 20)
            *out = _80 * 2400.0f;
        else
            *out = sead::Vector3f::zero;
        return true;
    }
    default:
        return false;
    }
}

s32 DamageMgrNPC::getNumCallbacks() {
    return 3;
}

void DamageMgrNPC::resetDamage() {
    DamageManagerBase::resetDamage();
    resetStuff();
    _80 = {0.0f, 0.0f, 0.0f};
}

}  // namespace uking::dmg
