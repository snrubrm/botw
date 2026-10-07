#include "Game/Actor/actWeapon.h"
#include "Game/Damage/dmgDamageMgrWeapon.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponCommon.h"

bool sub_71006DE628(const ksys::act::ActorConstDataAccess& accessor, s32 type);

namespace uking::dmg {

DamageMgrSword::DamageMgrSword(ksys::act::Actor* actor) : DamageMgrWeapon(actor) {
    mDamageFromLife = uking::act::WeaponModifierInfo::getLifeMultiplier();
    _6c = 0;
    _70 = false;
}

// NON_MATCHING: the original compares the loaded byte with zero (`cmp w8, #0; cset w8, ne`) before the store
void DamageMgrSword::resetDamage() {
    DamageManagerBase::resetDamage();
    resetStuff();
    const auto* param = mActor->getParam()->getRes().mGParamList->getWeaponCommon();
    _6c = param && param->mIsBlunt.ref();
}

void DamageMgrSword::m50(f32 scale) {
    mDamageFromLife = s32(uking::act::WeaponModifierInfo::getLifeMultiplier() * scale);
}

bool DamageMgrSword::m54() {
    return hasAttackInfo(mActor);
}

bool DamageMgrSword::getPosition(sead::Vector3f* out) {
    if (getDamageType() == 1) {
        if (auto* info = getAttackInfo(mActor, 0)) {
            out->x = info->_0.x;
            out->y = info->_0.y;
            out->z = info->_0.z;
            return true;
        }
    }
    return false;
}

bool DamageMgrSword::getAttackPos(sead::Vector3f* out) {
    if (getDamageType() == 1) {
        if (auto* info = getAttackInfo(mActor, 0)) {
            out->x = info->_c.x;
            out->y = info->_c.y;
            out->z = info->_c.z;
            return true;
        }
    }
    return false;
}

ksys::phys::MaterialMask* DamageMgrSword::m33() {
    if (getDamageType() == 1) {
        auto* info = getAttackInfo(mActor, 0);
        if (!info)
            return nullptr;
        return &info->_20;
    }
    return nullptr;
}

}  // namespace uking::dmg

namespace uking::dmg {

void DamageMgrSword::m22() {
    u32 v1 = 0;
    u32 v2 = 0;
    u32 v4 = -1;
    u32 v5 = -1;
    u32 v3 = 0;
    if (mIsOwnedByPlayer)
        handleDamageForPlayer(&v1, &v2, &v3, &v4, &v5);
    resetStuff();
    if (mField_34 != 0)
        return;

    s32 damage = 0;
    s32 df48 = 0;
    u32 minDmg = 0;
    s32 f54 = -1;
    u32 f50 = -1;
    s32 f40 = 0;
    if (mIsOwnedByPlayer) {
        if (sub_71002F267C(&damage, &df48, &minDmg, &f50, &f54, &f40)) {
            callDamageCallbacks(0, &damage, &df48, &minDmg, &f50, &f54, nullptr);
            if (addDamage(1, damage, df48, minDmg, f50, f54, f40))
                mDamageType = 1;
        }
    }

    auto* chemical = mActor->getChemicalStuff();
    if (chemical && chemical->_c0 == 3) {
        auto* life = mActor->getLife();
        damage = life ? *life : 1;
        df48 = 0;
        minDmg = 0;
        f50 = 9;
        f54 = 30;
        f40 = 1;
        if (addDamage(2, damage, df48, minDmg, f50, f54, f40))
            mDamageType = 2;
    }

    if (addDamage(3, v1, v2, v3, v4, v5, 1))
        mDamageType = 3;

    if (m52() && mDamage >= 1) {
        auto* life = mActor->getLife();
        mDamage = life ? *life : 1;
    }

    callDamageCallbacks(1, &mDamage, &mField_48, &mMinDmg, &mField_50, &mField_54, nullptr);
}

}  // namespace uking::dmg

namespace uking::dmg {

bool DamageMgrSword::sub_71002F267C(s32* damage, s32* df48, u32* minDmg, u32* f50, s32* f54,
                                    s32* f40) {
    // The tag hash is not identified.
    constexpr u32 tag = 0x51e73965;

    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);

    if (weapon && hasAttackInfo(weapon) && (weapon->_e50 & 2) && weapon->_d68 == weapon->_d70) {
        auto* info = getAttackInfo(weapon, 0);
        if (!info)
            return false;

        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&info->_50, &accessor);
        if (!sub_71006DE628(accessor, _6c) && !(info->_18 & 1))
            return false;
        if (ksys::act::hasTag(&info->_50, tag))
            return false;

        s32 value;
        s32 priority;
        if (weapon->isThrowingBreakWeapon() &&
            (ksys::act::isEnemyProfile(&info->_50) || ksys::act::isPreyOrSwarm(&info->_50))) {
            auto* life = weapon->getLife();
            value = life ? *life : 1;
            priority = 30;
        } else {
            value = mDamageFromLife;
            priority = 15;
        }
        *damage = value;
        *df48 = 0;
        *minDmg = 0;
        *f50 = 5;
        *f54 = priority;
        *f40 = 1;
        return true;
    }

    if (!m54())
        return false;

    if (weapon && hasAttackInfo(weapon)) {
        if (auto* info = getAttackInfo(weapon, 0)) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&info->_50, &accessor);
            if (!sub_71006DE628(accessor, _6c) && !(info->_18 & 1))
                return false;
            if (ksys::act::hasTag(&info->_50, tag))
                return false;
        }
    }

    *damage = mDamageFromLife;
    *df48 = 0;
    *minDmg = 0;
    *f50 = 5;
    *f54 = 15;
    *f40 = 1;
    return true;
}

}  // namespace uking::dmg
