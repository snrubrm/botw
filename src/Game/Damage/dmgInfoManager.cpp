#include "Game/Damage/dmgInfoManager.h"
#include "Game/AI/aiUnk_71007130BC.h"
#include "Game/gameScene.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/World/worldWeatherMgr.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"

namespace uking::dmg {

SEAD_SINGLETON_DISPOSER_IMPL(DamageInfoMgr)

bool DamageInfoMgr::enableBoomerangRemoteBombs() {
    return false;
}

bool DamageInfoMgr::sub_7100674764() {
    return false;
}

bool DamageInfoMgr::sub_710067476C() {
    return false;
}

s8 DamageInfoMgr::sub_7100674774() {
    return 7;
}

f32 DamageInfoMgr::sub_7100674788() {
    return 1.0f;
}

f32 DamageInfoMgr::sub_7100674790() {
    return 0.3f;
}

bool DamageInfoMgr::sub_710067479C() {
    return false;
}

bool DamageInfoMgr::sub_7100674704() const {
    if (!(_11e0 & 1)) {
        if (auto* weather = wm::getWeatherMgr())
            return weather->isRaining();
    }
    return false;
}

bool DamageInfoMgr::sub_7100674730() const {
    if (!(_11e0 & 2)) {
        if (auto* weather = wm::getWeatherMgr())
            return weather->isSnowing();
    }
    return false;
}

int DamageInfoMgr::getShieldRideBaseFrame() {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global || !global->getGlobalParam())
        return 0;

    return global->getGlobalParam()->mShieldRideBaseFrame.ref();
}

int DamageInfoMgr::getShieldRideHitBaseDamage() {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global || !global->getGlobalParam())
        return 0;

    return global->getGlobalParam()->mShieldRideHitBaseDamage.ref();
}

f32 DamageInfoMgr::getCriticalAttackRatio() {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global || !global->getGlobalParam())
        return 1.0;

    return global->getGlobalParam()->mCriticalAttackRatio.ref();
}

bool DamageInfoMgr::isTrueFormMasterSword() const {
    if (mMasterSwordDisableTrueForm)
        return false;

    if (ksys::gdt::getFlag_Open_MasterSword_FullPower())
        return true;

    if (ksys::gdt::getFlag_IsInHyruleCastleArea())
        return true;

    if (ksys::gdt::getFlag_LastBossGanonBeastGenerateFlag())
        return true;

    const sead::SafeString& map = GameScene::getCurrentMapName();

    if (!ksys::gdt::getFlag_Die_PGanonElectric() && map == "RemainsElectric")
        return true;

    if (!ksys::gdt::getFlag_Die_PGanonFire() && map == "RemainsFire")
        return true;

    if (!ksys::gdt::getFlag_Die_PGanonWater() && map == "RemainsWater")
        return true;

    if (!ksys::gdt::getFlag_Die_PGanonWind() && map == "RemainsWind")
        return true;

    return mMasterSwordDetectedEvil;
}

}  // namespace uking::dmg
