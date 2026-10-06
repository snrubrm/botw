#pragma once

#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <mc/seadJobQueue.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/Actor/actExtendedEntity.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "Game/Actor/actUnk_7100701be4.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/System/Timer.h"

namespace ksys::phys {
class NavMeshCharacter;
}  // namespace ksys::phys

namespace uking::act {

// Placeholder name (ctor 0x710070ef50, dtor 0x710070efa8 - empty, out of line).
// Embedded in Unk_7100013308 at 0x80.
class Unk_710070ef50 {
public:
    explicit Unk_710070ef50(ksys::act::Actor* actor);
    ~Unk_710070ef50();

    /* 0x00 */ ksys::act::Actor* mActor;
    /* 0x08 */ u8 _8[0x20 - 0x8];
};
KSYS_CHECK_SIZE_NX150(Unk_710070ef50, 0x20);

// Sub-object of Enemy (at 0xc48). Placeholder name: its out-of-line constructor is at
// 0x7100013308 (called from Enemy's ctor with the owning actor). Holds the current target:
// AI helpers return &_8 (target link), &_18 (target position), &_24 (matrix), &_54, &_70 and _7c.
// Methods: 0x71002dbc8c (17 callers) and neighbours.
class Unk_7100013308 {
public:
    explicit Unk_7100013308(ksys::act::Actor* actor);

    // Sets the target link, matrix (or the target actor's matrix) and position (or the target
    // actor's position) and sets _7c to 2.
    void sub_71002DBC8C(const ksys::act::BaseProcLink& link, const sead::Matrix34f* mtx,
                        const sead::Vector3f* pos);

    /* 0x000 */ ksys::act::Actor* mActor;
    /* 0x008 */ ksys::act::BaseProcLink _8;
    /* 0x018 */ sead::Vector3f _18;
    /* 0x024 */ sead::Matrix34f _24;
    /* 0x054 */ sead::Vector3f _54;
    /* 0x060 */ ksys::act::BaseProcLink _60;
    /* 0x070 */ sead::Vector3f _70;
    /* 0x07c */ s32 _7c;
    /* 0x080 */ Unk_710070ef50 _80;
    /* 0x0a0 */ void* _a0;
    /* 0x0a8 */ Unk_7102450528 _a8;
    /* 0x120 */ u8 _120;
};
KSYS_CHECK_SIZE_NX150(Unk_7100013308, 0x128);

// Placeholder name = vtable (2 slots: empty D1, D0). Embedded in Enemy at 0x1148.
class Unk_7102357908 {
public:
    explicit Unk_7102357908(ksys::act::Actor* actor) : mActor(actor) {}
    virtual ~Unk_7102357908() = default;

    /* 0x08 */ ksys::act::Actor* mActor;
    /* 0x10 */ void* _10 = nullptr;
    /* 0x18 */ void* _18 = nullptr;
    /* 0x20 */ RideableBase* _20 = nullptr;  // Enemy::m132
    /* 0x28 */ void* _28 = nullptr;
    /* 0x30 */ u32 _30 = 0;
    /* 0x38 */ ksys::act::BaseProcLink _38;
    // Placeholder (type unknown): an object with a scale (_2c, used while _10 is set) and flag bits
    // (LynelHighJumpAttack scales its jump height with it and sets flag bit 4 when it changes it).
    using Unk48 = ExtendedEntity;
    /* 0x48 */ Unk48* _48 = nullptr;
    // Placeholder (type unknown): the animal support object; the AnimalSupport behaviors set / clear
    // bits of the flags byte at +0x28 (bit 0: SetAnimalSupportNormalCalc, bit 1:
    // OnAnimalSupportNrmCalcFrontRay).
    struct Unk50 {
        struct CalcArg {
            sead::Vector3f posterior_limb_offset;
            f32 ray_cast_length;
            sead::Vector3f prior_limb_offset;
            f32 prior_ray_cast_length;
            bool enabled;
        };
        bool sub_71006F0800(const CalcArg& arg);

        /* 0x00 */ u8 _0[0x28];
        /* 0x28 */ u8 _28;
    };
    /* 0x50 */ Unk50* _50 = nullptr;
    /* 0x58 */ u32 _58 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102357908, 0x60);

// Message listeners embedded in Enemy (base vtable 0x7102357210). Placeholder names = vtables.
class Unk_7102357a08 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}
};

class Unk_7102357a38 : public Unk_7102357210 {
public:
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    u32 _34;
    f32 _38 = 0;
};

// Payload of the message handled by Unk_71023579d8 (sender unknown; placeholder name = listener vtable).
struct Unk_71023579d8_Payload {
    bool _0;
    sead::JobQueueLock mLock;
};

class Unk_71023579d8 : public Unk_7102357210 {
public:
    ~Unk_71023579d8() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023579d8_Payload _34;
};

// Payload of the message handled by Unk_71023579a8 (sender unknown; placeholder name = listener vtable).
struct Unk_71023579a8_Payload {
    bool _0;
    sead::JobQueueLock mLock;
};

class Unk_71023579a8 : public Unk_7102357210 {
public:
    ~Unk_71023579a8() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_71023579a8_Payload _34;
};

// Payload of the message handled by Unk_7102357978 (sender unknown; placeholder name = listener vtable).
struct Unk_7102357978_Payload {
    bool _0;
    sead::JobQueueLock mLock;
};

class Unk_7102357978 : public Unk_7102357210 {
public:
    ~Unk_7102357978() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102357978_Payload _34;
};

// Payload of the message handled by Unk_7102357948 (sender unknown; placeholder name = listener vtable).
struct Unk_7102357948_Payload {
    bool _0;
    sead::JobQueueLock mLock;
};

class Unk_7102357948 : public Unk_7102357210 {
public:
    ~Unk_7102357948() override;
    bool m2(const ksys::Message& message) override;
    void m3() override {}

    Unk_7102357948_Payload _34;
};

// Name from the CSV (Enemy::*); vtable 0x7102357300 (181 slots), RTTI 0x71025ae7d0.
// Base of Dragon, GelEnemy, GiantEnemy, Guardian, LastBoss, Sandworm, SiteBoss, Swarm (EnemyBase)
// and WolfLink (their checkDerivedRuntimeTypeInfo all test this RTTI before PlayerOrEnemy's).
// TODO: incomplete. Factory size 0x14c8 (Enemy::construct).
class Enemy : public ksys::act::PlayerOrEnemy {
    SEAD_RTTI_OVERRIDE(Enemy, ksys::act::PlayerOrEnemy)
public:
    explicit Enemy(const CreateArg& arg);
    // CSV Enemy::construct: the actor factory function.
    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
    ~Enemy() override;
    // 0x7100018a9c: declaration-only start timer update for this Enemy and its linked weapons.
    void sub_7100018A9C(f32 time);
    // 0x7100016494 (declaration only; unnamed in the CSV, lane5 s3): raises the arrow shoot counter at +0x11a0
    // (clamped by getArrowEnemyShootNumForDelete of the current weapon); called by ShootArrow::m33.
    void sub_7100016494();
    bool sub_71000198E4(ksys::act::Actor* actor);
    // 0x7100016284 / 0x71000161a4 (declaration only, lane1 s39; placeholder names): queries on the weapon slot
    // `idx` (the second calls the first and checks the held weapon).
    bool sub_7100016284(s32 idx);
    bool sub_71000161A4(s32 idx);
    void sub_7100019C58(ksys::act::Actor* actor);
    void sub_7100019D38(const ksys::act::BaseProcLink& link);

protected:
    InitResult init_() override;
    bool startPreparingForPreDelete_() override;
    void onDeleteRequested_(DeleteReason reason) override;
    void onEnterSleep_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg&) override;
    void preDelete2_(const PreDeleteArg& arg) override;
    IsSpecialJobTypeResult isSpecialJobType_(ksys::act::JobType type) override;

public:
    s32 getMaxLife() override;
    Actor* m31() override;
    void m36(const sead::Vector3f& a1, const sead::Vector3f& a2, bool a3, bool a4, bool a5) override;
    void m41(sead::Matrix34f* mtx) override;
    Actor* m48() override;
    bool m49() override;
    void killWithDropsAndEffects(int a1) override;
    // Declaration only; ownership follows the current Enemy label and caller.
    void incrementDefeatedCount();
    // 0x7100731064 (CSV name): counts a defeated giant / sandworm (GiantEnemy / Sandworm kills).
    void incrementGiantOrSandwormDefeatCount();
    bool m57() override;
    bool shouldUnload(s32* a1) override;
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void m70() override;
    void updatePositionMaybe() override;
    void m73() override;
    void m74() override;
    void m75() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    bool m81(const ksys::Message& message) override;
    void updateMtxFromPhysics() override;
    void m92(ksys::phys::RigidBody* body) override;
    void m93(int a1, float a2) override {
        if (a1 >= _f44) {
            _f44 = a1;
            _f48 = a2;
        }
    }
    s32 m94() override { return _f40; }
    Unk_7100d3cd74* m101() override;
    void m114() override;
    void m117(ksys::act::Unk117* arg) override;
    void* m119() override;
    HorseRideInfo* getPlayerRideInfo() override;
    Rideable* getHorseOptionsMaybe() override;
    RideableBase* m132() override;
    Unk_7100e8b2b8* getMotorcyclePriorityStuffMaybe() override;
    ksys::act::LifeRecoverInfo* getLifeRecoverInfo() override;
    Actor* m141(const s32* index) override;
    bool m146() override;
    Unk_71025ae680* m159() override { return _e78; }
    void m160() override;
    bool m162() override { return _e82 >> 9 & 1; }
    bool m164(s32 idx, ksys::act::Actor* weapon, bool a3, bool a4) override;
    bool m165(sead::BufferedSafeString* out) override;
    bool isGuard() override;
    bool m169() override { return _e84.isOnBit(13); }
    bool weaponDroppedByEnemy() override;
    const char* getEquippedItem() override;

    // FIXME: figure out return types, parameters and names
    // Equips `weapon` in slot `idx` (the original asks getWeapons() first).
    virtual bool m177(s32 idx, ksys::act::Actor* weapon);
    // 0x7100731cd8 (CSV Enemy::setDroppedWeaponFlag; declared only).
    void setDroppedWeaponFlag();
    // 0x7100015438 (placeholder name, lane4 s45; called by PriestBossActorNormalRoot::m35): acquires `weapon` in
    // slot `idx` and sets _e82 bit 12.
    void sub_7100015438(s32 idx, ksys::act::Actor* weapon);
    // Creates the object returned by DynamicActor slot 159 (_e78).
    virtual Unk_71025ae680* m178(sead::Heap* heap);
    void setNecklaceFlag(s32 index);

    virtual void m179();
    virtual void m180() {}

    // Forwarders to the parts object _1128. Inline-only in the original; names are a guess (the
    // forwarded method's name). Codegen evidence: ~25 AI functions compute the name / heap / proc
    // arguments before `enemy + 0x1128`, which a direct `enemy->_1128.f(args)` call cannot reproduce.
    bool sub_7100D3CED8(const sead::SafeString& name, sead::Heap* heap) {
        return _1128.sub_7100D3CED8(name, heap);
    }
    bool sub_7100D3CFEC(const sead::SafeString& name) { return _1128.sub_7100D3CFEC(name); }
    bool sub_7100D3D108(const sead::SafeString& name, ksys::act::BaseProc* proc) {
        return _1128.sub_7100D3D108(name, proc);
    }
    bool sub_7100D3D1E0(const sead::SafeString& name, const ksys::act::BaseProcLink& link) {
        return _1128.sub_7100D3D1E0(name, link);
    }
    bool sub_7100D3D2B4(const sead::SafeString& name) { return _1128.sub_7100D3D2B4(name); }
    ksys::act::BaseProcLink& getActorPartsActor(const sead::SafeString& name) {
        return _1128.getActorPartsActor(name);
    }

    // Fields are accessed directly by the AI helper functions (aiUnk_71005D6D10.cpp) and AI classes.
    /* 0xc38 */ sead::Buffer<ksys::act::BaseProcLink> _c38;  // indexed by weapon slot (m177)
    /* 0xc48 */ Unk_7100013308 _c48{this};
    /* 0xd70 */ Unk_71002dccbc _d70{this};
    // Passed as a whole to 0x710039dd0c (EnemyNormal), which stores its address as a link.
    /* 0xe08 */ ksys::act::Unk_71006e4478 _e08;
    /* 0xe68 */ ksys::Timer _e68;
    /* 0xe74 */ f32 _e74 = 0;  // written by NoticeTurn::leave_
    /* 0xe78 */ Unk_71025ae680* _e78 = nullptr;  // m159, created by m178
    /* 0xe80 */ sead::BitFlag8 _e80;  // bit idx: weapon slot idx is equipped (m164 / m177)
    /* 0xe81 */ sead::BitFlag8 _e81;
    /* 0xe82 */ u16 _e82 = 0;
    /* 0xe84 */ sead::BitFlag32 _e84;
    /* 0xe88 */ void* _e88 = nullptr;
    /* 0xe90 */ u32 _e90 = 0;
    /* 0xe98 */ sead::SafeString _e98;
    /* 0xea8 */ sead::SafeArray<ksys::act::BaseProcLink, 8> _ea8{};
    // Placeholder (offset of Enemy's pointer to it): heap object (0x20 bytes, `new (heap, 8)`) built
    // by Enemy's init 0x71000139.. with the actor's NavMeshCharacter (m45()); deleted in preDelete2_.
    // Returned by sub_71005E2BCC; AI code (LynelNavMoveNoStop, ForestGiantRoam, ...) sets _8.
    struct Unk_12d0 {
        // 0x7100710f04 (CSV nullsub_2335; declared only): empty.
        void sub_7100710F04();
        // 0x7100710f08 (declared only; lane2 s20): `if (_0) { _8 = -1; _c = 0; }` (one 8-byte store).
        void sub_7100710F08();
        // 0x7100710f28 (declared only; lane2 s20): advances the state `_8` (0 -> 1 -> 2 -> 3) from the character's
        // flags (_294 / _296, _220) under its critical section.
        void sub_7100710F28();

        /* 0x00 */ ksys::phys::NavMeshCharacter* _0;
        /* 0x08 */ s32 _8 = -1;
        /* 0x0c */ s32 _c = -1;
        /* 0x10 */ sead::Vector3f _10 = sead::Vector3f::zero;
    };

    // Placeholder name (no vtable, inline ctor; only method 0x7100001aa4, called by ~20 enemy AI
    // functions with this + 0xf28). Picks the next attack interval kind (_8: 0 / 1 / 2, the short /
    // middle / long ranges of the actor's GParamList AttackInterval) and returns a random time in that
    // range multiplied by `scale`.
    struct Unk_7100001aa4 {
        explicit Unk_7100001aa4(Actor* actor) : mActor(actor) {}

        int sub_7100001AA4(f32 scale);

        Actor* mActor;
        s32 _8 = -1;
    };
    /* 0xf28 */ Unk_7100001aa4 _f28{this};

    // inline-only in the original; name is a guess (lane1 s22). Evidence: `time = _f28.sub_7100001AA4(
    // scale); _e68 = Timer(time, time)` is inlined, with the scale argument evaluated first, in
    // EnemyBattle::sub_7100381ED4, AssassinFieldShooterBattleBase::enter_, MoriblinSpearBattle,
    // EnemySkyArrowAttack::m35, RodEnemyFindPlayer::calc_, GanonBeastWait and others.
    void startAttackInterval(f32 scale) {
        const s32 time = _f28.sub_7100001AA4(scale);
        _e68 = ksys::Timer(time, time);
    }
    /* 0xf38 */ void* _f38 = nullptr;
    /* 0xf40 */ s32 _f40 = 0;
    /* 0xf44 */ s32 _f44 = -1;
    /* 0xf48 */ f32 _f48 = 0;
    /* 0xf4c */ f32 _f4c = 0;  // compared with the global ForceTired / ForceTiredNoSight / ForceWarpReturn LOD counts
    /* 0xf50 */ f32 _f50 = -1.0;
    /* 0xf54 */ sead::BitFlag16 _f54;
    /* 0xf58 */ Actor* _f58 = this;
    /* 0xf60 */ Unk_7100701be4 _f60{this};  // eyelid controller (EyeBlink / CloseEye / DieEye)
    /* 0x10f8 */ HorseRideInfo* _10f8 = nullptr;  // getPlayerRideInfo
    /* 0x1100 */ ksys::act::BaseProcLink _1100;
    /* 0x1110 */ u8 _1110[0x1128 - 0x1110];  // list head + count
    /* 0x1128 */ Unk_7100d3cd74 _1128{this};
    /* 0x1148 */ Unk_7102357908 _1148{this};
    /* 0x11a8 */ sead::CriticalSection _11a8;
    /* 0x11e8 */ ksys::act::BaseProcLink _11e8;
    /* 0x11f8 */ sead::Matrix34f _11f8 = sead::Matrix34f::ident;
    /* 0x1228 */ sead::Vector3f _1228 = sead::Vector3f::zero;
    /* 0x1234 */ sead::Vector3f _1234 = sead::Vector3f::zero;
    /* 0x1240 */ u32 _1240 = 0;
    /* 0x1244 */ u8 _1244 = 0;
    /* 0x1245 */ u8 _1245 = 0;
    /* 0x1246 */ u8 _1246[0x1248 - 0x1246];
    /* 0x1248 */ u8 _1248 = 0;
    /* 0x1250 */ void* _1250 = nullptr;
    /* 0x1258 */ Unk_7102357a08 _1258;
    /* 0x1290 */ Unk_7102357a38 _1290;
    /* 0x12d0 */ Unk_12d0* _12d0 = nullptr;
    /* 0x12d8 */ void* _12d8 = nullptr;
    /* 0x12e0 */ sead::Matrix34f _12e0 = sead::Matrix34f::ident;
    /* 0x1310 */ f32 _1310 = 0.0;
    /* 0x1314 */ f32 _1314 = 1.0;
    /* 0x1318 */ f32 _1318 = 0.0;
    /* 0x131c */ f32 _131c = 1.0;
    /* 0x1320 */ f32 _1320 = 1.0;
    /* 0x1324 */ f32 _1324 = 1.0;
    /* 0x1328 */ void* _1328 = nullptr;
    /* 0x1330 */ void* _1330 = nullptr;
    /* 0x1338 */ u32 _1338 = 0;
    /* 0x1340 */ ksys::phys::MaterialMask _1340{0u};
    /* 0x1358 */ ksys::phys::MaterialMask _1358{0u};
    /* 0x1370 */ u8 _1370[0x13a0 - 0x1370];
    /* 0x13a0 */ u32 _13a0 = 2;
    /* 0x13a4 */ u8 _13a4 = 6;
    /* 0x13a8 */ ksys::act::BaseProcLink _13a8;
    /* 0x13b8 */ u8 _13b8 = 0;
    /* 0x13b9 */ u8 _13b9 = 0;
    /* 0x13c0 */ ksys::act::LifeRecoverInfo* _13c0 = nullptr;
    /* 0x13c8 */ Unk_71023579d8 _13c8;
    /* 0x1408 */ Unk_71023579a8 _1408;
    /* 0x1448 */ Unk_7102357978 _1448;
    /* 0x1488 */ Unk_7102357948 _1488;
};
KSYS_CHECK_SIZE_NX150(Enemy, 0x14c8);

}  // namespace uking::act
