#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadRingBuffer.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <mc/seadJobQueue.h>
#include <thread/seadAtomic.h>
#include <thread/seadReadWriteLock.h>
#include "Game/Actor/actGuardianRegistry.h"
#include "Game/Actor/Damage/dmgClothStiffnessMgr.h"
#include "Game/Actor/Damage/dmgUnk_7100671794.h"
#include "Game/Actor/aiUnk_71007024d4.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Resource/resHandle.h"

namespace sead {
class Heap;
}

namespace ksys::act {
class Actor;
}

// Stage flag at 0x71025c59d8 (placeholder name): set in Unk28::sub_710065CAEC and read by the damage
// distance check at 0x710065c834.
extern bool sUnk_71025C59D8;

namespace uking::act {

// FIXME: incomplete
class DamageItem {
public:
    s32 mField_0;  // the hash of the entry's name (DamageReactionTable::sub_71006681E4)
    sead::SafeArray<u8, 3> mCanTakeDamageFromType = {};
};

// Name from the CSV (DamageReactionTable::load 0x7100667de4): DamageInfoMgr + 0x5d0, the reaction table resource and
// its entries. Methods are in the TU 0x7100667de4 - 0x7100668260 (dmgDamageReactionTable.cpp).
struct DamageReactionTable {
    DamageReactionTable();
    ~DamageReactionTable();
    // 0x7100667de4: loads DamageParam/DamageReactionTable.bxml into mItems.
    bool load(sead::Heap* heap);
    // 0x71006681a4: frees the reaction entries (DamageInfoMgr destruction).
    void sub_71006681A4();
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
    // 0x7100673da4: resets the actor lists and reloads the reaction table.
    void init(sead::Heap* heap);
    // 0x7100673e24: resets the light-damage bookkeeping when a stage is loaded.
    void onLoadStage();
    // 0x710067428c (CSV DamageInfoMgr::postCalc; declared only).
    void postCalc();
    // Native readiness forwards to the reaction table at +0x5d0.
    bool isReady();
    void stubbed();
    // The heap argument is unused here; the caller still loads it (GameScene : 0x71007a8e78).
    void sub_7100673D8C(sead::Heap* heap);
    void sub_7100674058();

    using DamageItem = act::DamageItem;

    /// Boomerang remote bombs are a scrapped feature.
    static bool enableBoomerangRemoteBombs();
    // Constant results (placeholder names, lane4 s45): false, false, 7 (as s8), 1.0, 0.3, false.
    static bool sub_7100674764();
    static bool sub_710067476C();
    static s8 sub_7100674774();
    // 0x710067477c: the global byte at 0x710243C398 (true in the image).
    static bool sub_710067477C();
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
        // 0x710065cae8: empty in the original (a 4-byte return); DamageInfoMgr::init calls it first.
        void sub_710065CAE8();
        // 0x710065ce14 (BattleTensionUp::m8) / 0x710065cf08 (BattleTensionUp::m9)
        void sub_710065CE14(ksys::act::Actor* actor);
        void sub_710065CF08(ksys::act::Actor* actor);
        void sub_710065CB68();
        // 0x710065cb6c (postCalc): declaration only.
        void sub_710065CB6C();
        // 0x710065caec: resets the entries and the stage flag; called by DamageInfoMgr::onLoadStage.
        void sub_710065CAEC();
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
        // 0x71006682b8: returns true; DamageInfoMgr::init passes the heap it was given.
        bool sub_71006682B8(sead::Heap* heap);
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

    // Placeholder (only its method 0x7100672110 is known): the object at +0x630, whose first
    // member is a ring buffer of actor links.
    struct Unk_7100672110 {
        void sub_7100672110();
        /* 0x00 */ sead::RingBuffer<ksys::act::BaseProcLink> mRing;
        /* 0x18 */ u8 _18[0x148];
    };
    KSYS_CHECK_SIZE_NX150(Unk_7100672110, 0x160);

    // Entry of the ring buffer at +0xdb8: an expired actor link and its countdown.
    // The leading 16 bytes are unknown (the ring's producers are not decompiled yet); the countdown
    // at +0x10 is the only field postCalc touches.
    struct RingEntry {
        /* 0x00 */ u8 _0[0x10];
        /* 0x10 */ f32 mCountdown;
    };
    KSYS_CHECK_SIZE_NX150(RingEntry, 0x14);

    // 2026-10-07: original constructor 0x71006737f4 initializes the prefix at +0x790;
    // its next independent member starts at +0x868. Remaining nested lifetime is unresolved.
    struct Unk790;

    // The setup of the actor rain (Unk790 + 0x68), copied in by Unk790::sub_710067298C.
    struct Unk790Params {
        // Field names and defaults from GParamListObjectWizzrobe (MagicFall*), which
        // Unk_7102431fa8::sub_7100741E54 copies in.
        sead::FixedSafeString<64> mActorName{""};
        /* 0x58 */ f32 mIgniteRotSpd = 0.0f;  // Unk_71007024d4::_1c (radians per frame)
        /* 0x5c */ f32 mOffsetY = 6.0f;  // Unk_71007024d4::_34
        /* 0x60 */ f32 mCenterOffsetXZ = 5.0f;  // Unk_71007024d4::_30
        /* 0x64 */ f32 mRandRadius = 12.0f;  // Unk_71007024d4::_38
        /* 0x68 */ f32 mIntervalMax = 20.0f;  // frames
        /* 0x6c */ f32 mIntervalMin = 15.0f;  // frames
    };
    KSYS_CHECK_SIZE_NX150(Unk790Params, 0x70);

    // Placeholder name (vtable 0x710243c3a0, no RTTI): the actor "rain" component embedded at
    // Unk790 + 0x20. It creates the actor named by its owner's _68 around the owner's actor.
    class Unk_710243c3a0 : public Unk_71007024d4 {
    public:
        // 0x7100672b60: the position of the owner's actor.
        bool m1(sead::Vector3f* out) override;
        // 0x7100672be4: the owner's actor name.
        bool m2(sead::BufferedSafeString* out) override;
        // 0x7100672d00: links a created actor with the owner's actor.
        void m3(ksys::act::Actor* actor) override;

        /* 0x40 */ Unk790* mOwner;
    };
    KSYS_CHECK_SIZE_NX150(Unk_710243c3a0, 0x48);

    struct Unk790 {
        // 0x7100672578 (postCalc): declaration only.
        void sub_7100672578();
        // 0x71006726dc; declaration only, weather availability test.
        bool sub_71006726DC(s32 weather);
        bool sub_7100672B00(ksys::act::Actor* actor) const;
        bool sub_7100672B1C(ksys::act::Actor* actor) const;
        void sub_7100672888(ksys::act::Actor* actor);
        // 0x71006727e4 (CSV name): links `proc` (status 1, weather `weather`) unless an actor is already linked.
        bool tryAcquireWizzrobeWeatherRequest(ksys::act::BaseProc* proc, s32 weather);
        // 0x710067298c: when `proc` is the linked actor, takes `params` and restarts the actor rain (status 2).
        bool sub_710067298C(ksys::act::BaseProc* proc, const Unk790Params& params);
        s32 mStatus;
        s32 _4;
        ksys::act::BaseProcLink mLink;
        /* 0x18 */ sead::Atomic<u32> mLock;  // a spin lock (0 / 1)
        /* 0x20 */ Unk_710243c3a0 _20;
        /* 0x68 */ Unk790Params mParams;
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
        // 0x710065d138 (postCalc): declaration only.
        void sub_710065D138();
        // 0x710065d0a4: empty in the original (a 4-byte return); DamageInfoMgr::init calls it first.
        void sub_710065D0A4();
        Unk450();
        ~Unk450();
        void sub_710065D0A8();
        // 2026-10-07: four 0x28-byte linked entries, ctor 0x710065cfa4;
        // the actor ID at +0x18 is distinct from the BaseProcLink's ID at +8.
        struct Entry {
            Entry() { mLink.reset(); }
            ksys::act::BaseProcLink mLink;
            s32 _10 = 0;  // BGM selection ID (BossBgm registration and 0x710065d138).
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
    /* 0x0630 */ Unk_7100672110 _630;
    /* 0x0790 */ Unk790 _790;
    /* 0x0868 */ Unk868 _868;
    /* 0x0b90 */ Unk_710243c280 mGuardianRegistry;
    // 0x7100ce0 (placeholder name): the list Enemy::m73 queries to decide whether an enemy may attack. Each
    // entry is an actor that may attack; sub_7100673444 counts the nearby ones and compares against
    // GlobalParameter's ForceNoticeEnemyCount.
    class UnkCe0 {
    public:
        // 0x18 bytes (clang pads mTag to the 8-byte alignment); mTag is written by sub_7100673064.
        // The entry constructor (inlined in init's array allocation) only runs BaseProcLink's
        // constructor and stores -1 in mTag.
        struct Entry {
            /* 0x00 */ ksys::act::BaseProcLink mLink;
            /* 0x10 */ u32 mTag = 0xffffffff;
        };
        KSYS_CHECK_SIZE_NX150(Entry, 0x18);

        // 0x7100672d4c: frees the list and allocates mCount entries on `heap`.
        void init(sead::Heap* heap);
        // 0x7100672e48 (postCalc): clears the tagged entries and counts the living ones.
        void sub_7100672E48();
        // 0x7100672f54: links `proc` into the first untagged entry (false when it is already listed).
        bool sub_7100672F54(ksys::act::BaseProc* proc);
        // 0x7100673064: stores `tag` in the entry linked to `proc` (false when it is not listed).
        bool sub_7100673064(ksys::act::BaseProc* proc, u32 tag);
        // 0x710067313c: like sub_71006732CC with the flag bits 24 and 25, and no flag parameter.
        s32 sub_710067313C(f32 radius);
        // 0x71006732cc: counts the listed actors that pass the flag test (and are nearer than `radius`
        // when it is not negative) to the player; the wrapper below passes the flag bit 25.
        s32 sub_71006732CC(f32 radius, u32 type);
        // 0x710067343c (placeholder name): tail-calls sub_71006732CC(value, 25).
        void sub_710067343C(f32 value);
        bool sub_7100673444(const sead::Vector3f& position) const;

        /* 0x00 */ sead::Buffer<Entry> mLinks;
        /* 0x10 */ u32 mCount = 0;
        /* 0x14 */ bool _14 = false;
        u8 _15[3];
        /* 0x18 */ sead::Atomic<u32> mLock;  // a spin lock (0 / 1)
    };
    KSYS_CHECK_SIZE_NX150(UnkCe0, 0x20);

    /* 0x0cd8 */ s32 _cd8 = 0;
    u8 TEMP_cdc[4];
    /* 0x0ce0 */ UnkCe0 mUnkCe0;
    /* 0x0d00 */ sead::ReadWriteLock mLock;
    /* 0x0db8 */ sead::RingBuffer<RingEntry> mRing;
    /* 0x0dd0 */ u8 TEMP_dcc[0xe98 - 0xdd0];
    /* 0x0e98 */ ClothStiffnessMgr mClothStiffnessMgr;
    /* 0x11e0 */ u8 _11e0;  // bit 0: no rain, bit 1: no snow (sub_7100674704 / 30)
    /* 0x11e1 */ u8 _11e1;
    /* 0x11e2 */ u8 _11e2;  // zeroed by init
    u8 TEMP_11e3;
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

}  // namespace uking::act
