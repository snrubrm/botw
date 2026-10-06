#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <thread/seadReadWriteLock.h>
#include "Game/Damage/dmgClothStiffnessMgr.h"
#include "Game/Damage/dmgUnk_7100671794.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Resource/resHandle.h"

namespace uking::dmg {

// FIXME: incomplete
class DamageInfoMgr {
    SEAD_SINGLETON_DISPOSER(DamageInfoMgr)
    DamageInfoMgr();
    virtual ~DamageInfoMgr();

public:
    // 0x710067428c (CSV DamageInfoMgr::postCalc; declared only).
    void postCalc();

    // FIXME: incomplete
    class DamageItem {
    public:
        s32 mField_0;  // unknown
        sead::SafeArray<u8, 3> mCanTakeDamageFromType;
    };

    /// Boomerang remote bombs are a scrapped feature.
    static bool enableBoomerangRemoteBombs();
    // Constant results (placeholder names, lane4 s45): false, false, 7 (as s8), 1.0, 0.3, false.
    static bool sub_7100674764();
    static bool sub_710067476C();
    static s8 sub_7100674774();
    static f32 sub_7100674788();
    static f32 sub_7100674790();
    static bool sub_710067479C();
    static int getShieldRideBaseFrame();
    static int getShieldRideHitBaseDamage();
    static f32 getCriticalAttackRatio();

    bool isTrueFormMasterSword() const;

    sead::Buffer<DamageItem>& getDamagesArray() { return mDamagesArray; }
    const sead::Buffer<DamageItem>& getDamagesArray() const { return mDamagesArray; }
    f32 getMasterSwordSearchEvilDist() const { return mMasterSwordSearchEvilDist; }
    bool isMasterSwordDetectedEvil() const { return mMasterSwordDetectedEvil; }
    bool isMasterSwordDisableTrueForm() const { return mMasterSwordDisableTrueForm; }
    // Written inline by ForceMasterSwordFakeMode / ResetMasterSwordForceState (name is a guess).
    void setMasterSwordDisableTrueForm(bool value) { mMasterSwordDisableTrueForm = value; }
    bool isOneHitObliteratorActive() const { return mOneHitObliteratorActive; }
    // Written inline by DeadlyBlowWeaponRoot::sub_710035C57C (lane1 s28; name is a guess).
    void setOneHitObliteratorActive(bool value) { mOneHitObliteratorActive = value; }

    // lane1 s21: the nearest-enemies list / attack permission limiter (EnemyBattle and others).
    Unk_7100671794& get4f8() { return _4f8; }
    // lane4 s30 (lane1 request): the cloth stiffness resource cache at +0xe98 (ChuchuRoot).
    ClothStiffnessMgr& getClothStiffnessMgr() { return mClothStiffnessMgr; }

    // 0x7100674704 / 0x7100674730 (declaration only; lane2 s22, WeatherReactionCheck): whether it is raining /
    // snowing (`!(byte[0x11e0] & 1) && wm::getWeatherMgr() && getWeatherMgr()->isRaining()` / bit 2 and
    // isSnowing()). Placeholder names.
    bool sub_7100674704() const;
    bool sub_7100674730() const;

private:
    /* 0x0028 */ u8 TEMP_8[0x4f8 - 0x28];
    /* 0x04f8 */ Unk_7100671794 _4f8;
    /* 0x05d0 */ ksys::res::Handle mReactionTable;
    /* 0x0620 */ sead::Buffer<DamageItem> mDamagesArray;
    /* 0x0630 */ u8 TEMP_630[0xd00 - 0x630];
    /* 0x0d00 */ sead::ReadWriteLock mLock;
    /* 0x0db8 */ u8 TEMP_db8[0xe98 - 0xdb8];
    /* 0x0e98 */ ClothStiffnessMgr mClothStiffnessMgr;
    /* 0x11e0 */ u8 _11e0;  // bit 0: no rain, bit 1: no snow (sub_7100674704 / 30)
    u8 TEMP_11e1[0x11e4 - 0x11e1];
    /* 0x11e4 */ f32 mMasterSwordSearchEvilDist;
    /* 0x11e8 */ bool mMasterSwordDetectedEvil;
    /* 0x11e9 */ bool mMasterSwordDisableTrueForm;
    /* 0x11ea */ bool mOneHitObliteratorActive;

public:
    /* 0x11eb */ sead::SafeArray<u8, 4> _11eb;  // per-core counters (ForceConfront behavior)

private:
    /* 0x11f0 */ ksys::act::BaseProcLink _11f0;
    /* 0x1200 */ ksys::act::BaseProcLink _1200;
    /* 0x1210 */ ksys::act::BaseProcLink _1210;
    /* 0x1220 */ ksys::act::BaseProcLink _1230;
    /* 0x1230 */ sead::ReadWriteLock mProcLinkLock;
    /* 0x12e8 */ void* _12e8;
};
KSYS_CHECK_SIZE_NX150(DamageInfoMgr, 0x12F0);

}  // namespace uking::dmg
