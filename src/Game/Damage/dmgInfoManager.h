#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <mc/seadJobQueue.h>
#include <thread/seadReadWriteLock.h>
#include "Game/Damage/dmgClothStiffnessMgr.h"
#include "Game/Damage/dmgUnk_7100671794.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Resource/resHandle.h"

namespace ksys::act {
class Actor;
}

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
    // 0x7100674804 (CSV get10): returns the constant 10 (the interval of the shield ride hits; placeholder name).
    static int sub_7100674804();
    static f32 getCriticalAttackRatio();

    bool isTrueFormMasterSword() const;

    // Placeholders (lane4 s49): the lock-protected actor lists embedded at +0x28 (lock at +0x41c, size 0x428) and +0x450
    // (lock at +0xa0, size 0xa8). Placeholder names follow their original addresses.
    struct Unk28 {
        // 0x710065ce14 (BattleTensionUp::m8) / 0x710065cf08 (BattleTensionUp::m9)
        void sub_710065CE14(ksys::act::Actor* actor);
        void sub_710065CF08(ksys::act::Actor* actor);
        Unk28();
        ~Unk28();
        // 2026-10-07: 32 entries constructed at 0x710065c96c; link/reset, countdown,
        // rank and removal flag are independently written at offsets 0, 0x10, 0x14, 0x18.
        struct Entry {
            Entry() { mLink.reset(); }
            ksys::act::BaseProcLink mLink;
            f32 mCountdown = 0.0f;
            s32 mRank = -1;
            bool mRemove = false;
        };
        // The original removal loop advances an Entry*; destruction directly destroys all 32 entries.
        Entry mEntries[32];
        u8 _400[0xc];
        s32 _40c = 0;
        u8 _410[0xc];
        sead::JobQueueLock mLock;
        bool _420 = false;
        bool _421 = false;
        bool _422 = false;
        bool _423 = false;
    };
    // 2026-10-07: original constructor 0x71006737f4 initializes the prefix at +0x790;
    // its next independent member starts at +0x868. Remaining nested lifetime is unresolved.
    struct Unk790 {
        bool sub_7100672B00(ksys::act::Actor* actor) const;
        bool sub_7100672B1C(ksys::act::Actor* actor) const;
        void sub_7100672888(ksys::act::Actor* actor);
        s32 mStatus;
        s32 _4;
        ksys::act::BaseProcLink mLink;
        u8 _18[0xd8 - 0x18];
    };
    KSYS_CHECK_SIZE_NX150(Unk790, 0xd8);
    // Inline-only in the original; name is a guess. WizzrobeWeatherMagic::leave_
    // 0x7100600620 and WizzrobeCombat::leave_ 0x71005fc178 both address this owner.
    Unk790& get790() { return _790; }

    struct Unk450 {
        // 0x710065d5d4 (BossBgm::m9, sub_7100720A70) / 0x710065d428
        void sub_710065D5D4(ksys::act::Actor* actor);
        void sub_710065D428(ksys::act::Actor* actor, const s32& value);
        // 0x710065d674 (lane4 s50; BossBgmDamaged::m7): stores the arguments in the slot of `actor`'s entry (slots at
        // +0x18 / +0x40 / +0x68 / +0x90, stride 0x28; `a` at +0x1c, the bools at +0x24 / +0x25, `d` at +0x14).
        void sub_710065D674(ksys::act::Actor* actor, s32 a, bool b, bool c, s32 d);
        Unk450();
        ~Unk450();
        void sub_710065D0A8();
        // 2026-10-07: four 0x28-byte linked entries, ctor 0x710065cfa4;
        // the actor ID at +0x18 is distinct from the BaseProcLink's ID at +8.
        struct Entry {
            Entry() { mLink.reset(); }
            ksys::act::BaseProcLink mLink;
            f32 _10 = 0.0f;
            s32 _14 = 0;
            s32 mActorId = -1;
            s32 _1c = 0;
            s32 _20 = 0;
            bool _24 = false;
            bool _25 = false;
            bool mRemove = false;
        };
        sead::SafeArray<Entry, 4> mEntries;
        sead::JobQueueLock mLock;
        s32 _a4 = 0;
    };
    KSYS_CHECK_SIZE_NX150(Unk28::Entry, 0x20);
    KSYS_CHECK_SIZE_NX150(Unk28, 0x428);
    KSYS_CHECK_SIZE_NX150(Unk450::Entry, 0x28);
    KSYS_CHECK_SIZE_NX150(Unk450, 0xa8);
    Unk28& get28() { return _28; }
    Unk450& get450() { return _450; }

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
    /* 0x0028 */ Unk28 _28;
    /* 0x0450 */ Unk450 _450;
    /* 0x04f8 */ Unk_7100671794 _4f8;
    /* 0x05d0 */ ksys::res::Handle mReactionTable;
    /* 0x0620 */ sead::Buffer<DamageItem> mDamagesArray;
    /* 0x0630 */ u8 TEMP_630[0x790 - 0x630];
    /* 0x0790 */ Unk790 _790;
    /* 0x0868 */ u8 TEMP_868[0xd00 - 0x868];
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
