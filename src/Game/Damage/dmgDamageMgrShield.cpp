#include "Game/Actor/actWeapon.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/Damage/dmgDamageMgrWeapon.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectShield.h"
#include "KingSystem/System/Timer.h"

bool sub_71006DE628(const ksys::act::ActorConstDataAccess& accessor, s32 type);

namespace uking::dmg {

DamageMgrShield::DamageMgrShield(ksys::act::Actor* actor) : DamageMgrWeapon(actor) {
    _68 = 0;
    _6c = 0;
    mDamageFromLife = uking::act::WeaponModifierInfo::getLifeMultiplier();
    _74 = false;
}

DamageMgrShield::~DamageMgrShield() = default;

void DamageMgrShield::resetDamage() {
    DamageManagerBase::resetDamage();
    resetStuff();
    _68 = 0;
    _6c = 0;
    _74 = false;
}

void DamageMgrShield::m50(f32 scale) {
    mDamageFromLife = s32(uking::act::WeaponModifierInfo::getLifeMultiplier() * scale);
}

}  // namespace uking::dmg

namespace uking::dmg {

void DamageMgrShield::m22() {
    u32 v1 = 0;
    u32 v2 = 0;
    u32 v4 = -1;
    u32 v5 = -1;
    u32 v3 = 0;
    if (mIsOwnedByPlayer)
        handleDamageForPlayer(&v1, &v2, &v3, &v4, &v5);
    _74 = false;
    resetStuff();

    s32 damage = 0;
    s32 df48 = 0;
    u32 minDmg = 0;
    s32 f54 = -1;
    u32 f50 = -1;
    s32 f40 = 0;
    if (mField_34 != 0)
        return;

    if (mIsOwnedByPlayer && shieldSurfDamageLogic(&damage, &df48, &minDmg, &f50, &f54, &f40)) {
        if (addDamage(2, damage, df48, minDmg, f50, f54, f40))
            mDamageType = 2;
    }

    if (shieldDamageLogic(&damage, &df48, &minDmg, &f50, &f54, &f40)) {
        if (addDamage(3, damage, df48, minDmg, f50, f54, f40))
            mDamageType = 3;
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
        if (addDamage(1, damage, df48, minDmg, f50, f54, f40))
            mDamageType = 1;
    }

    if (addDamage(4, v1, v2, v3, v4, v5, 1)) {
        _74 = true;
        mDamageType = 4;
    }

    callDamageCallbacks(0, &mDamage, &mField_48, &mMinDmg, &mField_50, &mField_54, nullptr);
}

bool DamageMgrShield::shieldDamageLogic(s32* damage, s32* df48, u32* minDmg, u32* f50, s32* f54,
                                        s32* f40) {
    // The tag hash is not identified (same tag as in DamageMgrSword::sub_71002F267C).
    constexpr u32 tag = 0x51e73965;

    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!weapon || !weapon->isParentPlayer() || !hasAttackInfo(weapon))
        return false;

    auto* info = getAttackInfo(weapon, 0);
    if (!info)
        return false;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&info->_50, &accessor);
    if (!sub_71006DE628(accessor, 0) && !(info->_18 & 1))
        return false;
    if (ksys::act::hasTag(&info->_50, tag))
        return false;

    *damage = mDamageFromLife;
    *df48 = 0;
    *minDmg = 0;
    *f50 = 5;
    *f54 = 15;
    *f40 = 1;
    return true;
}

bool DamageMgrShield::shieldSurfDamageLogic(s32* damage, s32* df48, u32* minDmg, u32* f50,
                                            s32* f54, s32* f40) {
    auto* weapon = sead::DynamicCast<uking::act::Weapon>(mActor);
    if (!weapon || !weapon->isParentPlayer())
        return false;

    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&weapon->getParentLink(), &accessor);

    if (!accessor.isShieldRideOnGround()) {
        ksys::Timer::update(&_6c, 1.0f);
        return false;
    }

    const f32 rate = weapon->getParam()->getRes().mGParamList->getShield()->mRideBreakRatio.ref();
    s32 hitDamage = 0;
    if (_6c > f32(DamageInfoMgr::sub_7100674804())) {
        const s32 life = mDamageFromLife;
        _6c = 0;
        hitDamage = s32(rate * f32(DamageInfoMgr::getShieldRideHitBaseDamage() * life));
    }

    if (accessor.isNoShieldDamageFloor())
        return false;

    if (accessor.getVelocity().length() > 0.03f) {
        const s32 baseFrame = DamageInfoMgr::getShieldRideBaseFrame();
        if (baseFrame == 0)
            return false;

        ksys::Timer::update(&_68, rate);
        if (_68 > f32(baseFrame)) {
            const f32 ratio = _68 / f32(baseFrame);
            _68 -= f32(baseFrame);
            const s32 count = s32(ratio);
            if (count >= 1) {
                *damage = mDamageFromLife * count + hitDamage;
                *df48 = 0;
                *minDmg = 0;
                *f50 = 5;
                *f54 = 15;
                *f40 = 1;
                return true;
            }
        }
    }

    if (hitDamage >= 1) {
        *damage = hitDamage;
        *df48 = 0;
        *minDmg = 0;
        *f50 = 5;
        *f54 = 15;
        *f40 = 1;
        return true;
    }
    return false;
}

}  // namespace uking::dmg
