#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <mc/seadJobQueue.h>
#include <thread/seadReadWriteLock.h>
#include "Game/Actor/actGuardianRegistry.h"
#include "Game/Damage/dmgClothStiffnessMgr.h"
#include "Game/Damage/dmgUnk_7100671794.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Resource/resHandle.h"

namespace ksys::act {
class Actor;
}

namespace uking::dmg {

// FIXME: incomplete
class DamageItem {
public:
    s32 mField_0;  // the hash of the entry's name (DamageReactionTable::sub_71006681E4)
    sead::SafeArray<u8, 3> mCanTakeDamageFromType;
};

// Name from the CSV (DamageReactionTable::load 0x7100667de4): DamageInfoMgr + 0x5d0, the reaction table resource and
// its entries. Methods are in the TU 0x7100667de4 - 0x7100668260 (dmgDamageReactionTable.cpp).
struct DamageReactionTable {
    void sub_71006681D4();
    bool isReady();
    void stubbed();
    // 0x71006681e4 (placeholder name): the index of the entry whose hash is calcHash(name), or -1.
    s32 sub_71006681E4(const sead::SafeString& name) const;

    /* 0x00 */ ksys::res::Handle mHandle;
    /* 0x50 */ sead::Buffer<DamageItem> mItems;
};

// FIXME: incomplete
class DamageInfoMgr {
    SEAD_SINGLETON_DISPOSER(DamageInfoMgr)
    DamageInfoMgr();
    virtual ~DamageInfoMgr();

public:
    // 0x710067428c (CSV DamageInfoMgr::postCalc; declared only).
    void postCalc();
    void sub_7100673D8C();
    // Native readiness forwards to the reaction table at +0x5d0.
    bool isReady();
    void stubbed();
    void sub_7100673D8C();
    void sub_7100674058();

    using DamageItem = dmg::DamageItem;

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
        void sub_710065CB68();
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
    // Native 668260 owner at +868, with two 16-entry groups and a JobQueueLock.
    struct Unk868 {
        struct Entry {
            ksys::act::BaseProcLink mLink;
            f32 mCountdown = 0.0f;
        };
        using Bucket = sead::SafeArray<Entry, 16>;
        Unk868();
        ~Unk868();
        void sub_71006682C0();
        void sub_71006685C0();
        void sub_7100668468();
        bool sub_71006685C4(s32 group, const ksys::act::BaseProcLink& link, f32 countdown);
        bool sub_71006686D0(s32 group, const ksys::act::BaseProcLink& link);
        bool sub_710066885C(s32 group, const ksys::act::BaseProcLink& link);
        u8 _0[0x20];
        sead::SafeArray<Bucket, 2> mBuckets;
        sead::JobQueueLock mLock;
    };
    KSYS_CHECK_SIZE_NX150(Unk868::Entry, 0x18);
    KSYS_CHECK_SIZE_NX150(Unk868::Bucket, 0x180);
    KSYS_CHECK_SIZE_NX150(Unk868, 0x328);

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
        void sub_710065D134();
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
    struct Unk11f0 {
        bool sub_7100674A94(ksys::act::Actor* actor);
        void sub_7100674B30(ksys::act::Actor* actor);
        bool sub_7100674BC0(ksys::act::Actor* actor);
        void sub_710067446C();

        /* 0x00 */ sead::SafeArray<ksys::act::BaseProcLink, 4> mLinks;
        /* 0x40 */ sead::ReadWriteLock mLock;
        /* 0xf8 */ s32 mSelectedIndex = -1;
    };
    KSYS_CHECK_SIZE_NX150(Unk11f0, 0x100);
    // Inline-only in the original; name is a guess. 7062D4/7063B8/706818/706C3C use this owner.
    Unk11f0& get11f0() { return _11f0; }

    // Inline-only in the original; name is a guess. Registration/query callers
    // 3B6B68, 3B7354, 46D9FC, 46E088, 4FEC88 and 500808 all address manager +868.
    Unk868& get868() { return _868; }
    Unk28& get28() { return _28; }
    Unk450& get450() { return _450; }
    // Inline-only in the original; name is a guess. 66E134/15C/178 address this registry.
    Unk_710243c280& getGuardianRegistry() { return mGuardianRegistry; }

    sead::Buffer<DamageItem>& getDamagesArray() { return mReactionTable.mItems; }
    const sead::Buffer<DamageItem>& getDamagesArray() const { return mReactionTable.mItems; }
    DamageReactionTable& getReactionTable() { return mReactionTable; }
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
    /* 0x05d0 */ DamageReactionTable mReactionTable;
    /* 0x0630 */ u8 TEMP_630[0x790 - 0x630];
    /* 0x0790 */ Unk790 _790;
    /* 0x0868 */ Unk868 _868;
    /* 0x0b90 */ Unk_710243c280 mGuardianRegistry;
    /* 0x0cd8 */ u8 TEMP_cd8[0xd00 - 0xcd8];
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
    /* 0x11eb */ sead::SafeArray<s8, 4> _11eb;  // per-core counters (ForceConfront behavior; Player::sub_710086C928 reads [3] signed)

private:
    /* 0x11f0 */ Unk11f0 _11f0;
};
KSYS_CHECK_SIZE_NX150(DamageInfoMgr, 0x12F0);

}  // namespace uking::dmg
