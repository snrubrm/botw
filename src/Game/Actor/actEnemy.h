#pragma once

#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <mc/seadJobQueue.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/physMaterialMask.h"

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
    /* 0x118 */ u32 _118;
    /* 0x11c */ u8 _11c[4];
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
    /* 0x48 */ void* _48 = nullptr;
    /* 0x50 */ void* _50 = nullptr;
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
    ~Enemy() override;

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
    void m36() override;
    void m41() override;
    Actor* m48() override;
    void m49() override;
    void killWithDropsAndEffects(int a1) override;
    bool m57() override;
    bool shouldUnload() override;
    void m63() override;
    void initMaybe() override;
    void calcMaybe() override;
    void m70() override;
    void updatePositionMaybe() override;
    void m73() override;
    void m74() override;
    void m75() override;
    void m76() override;
    void m81() override;
    void updateMtxFromPhysics() override;
    void m92() override;
    void m93(int a1, float a2) override {
        if (a1 >= _f44) {
            _f44 = a1;
            _f48 = a2;
        }
    }
    s32 m94() override { return _f40; }
    Unk_7100d3cd74* m101() override;
    void m114() override;
    void m117() override;
    void m119() override;
    HorseRideInfo* getPlayerRideInfo() override;
    Rideable* getHorseOptionsMaybe() override;
    RideableBase* m132() override;
    Unk_7100e8b2b8* getMotorcyclePriorityStuffMaybe() override;
    ksys::act::LifeRecoverInfo* getLifeRecoverInfo() override;
    void m141() override;
    bool m146() override;
    void m159() override;
    void m160() override;
    bool m162() override { return _e82 >> 9 & 1; }
    void m164() override;
    void m165() override;
    bool isGuard() override;
    bool m169() override { return _e84.isOnBit(13); }
    bool weaponDroppedByEnemy() override;
    void getEquippedItem() override;

    // FIXME: figure out return types, parameters and names
    virtual void m177();
    virtual void m178();
    virtual void m179();
    virtual void m180() {}

    // Fields are accessed directly by the AI helper functions (aiUnk_71005D6D10.cpp) and AI classes.
    /* 0xc38 */ sead::Buffer<ksys::act::BaseProcLink> _c38;  // indexed by weapon slot (m177)
    /* 0xc48 */ Unk_7100013308 _c48{this};
    /* 0xd70 */ Unk_71002dccbc _d70{this};
    /* 0xe08 */ ksys::act::BaseProcLink _e08;
    /* 0xe18 */ sead::Matrix34f _e18 = sead::Matrix34f::ident;
    /* 0xe48 */ sead::Vector3f _e48 = sead::Vector3f::zero;
    /* 0xe54 */ sead::Vector3f _e54 = sead::Vector3f::zero;
    /* 0xe60 */ u32 _e60 = 0;
    /* 0xe64 */ u8 _e64 = 0;
    /* 0xe65 */ u8 _e65 = 0;
    /* 0xe68 */ void* _e68 = nullptr;
    /* 0xe70 */ void* _e70 = nullptr;
    /* 0xe78 */ void* _e78 = nullptr;
    /* 0xe80 */ u16 _e80 = 0;
    /* 0xe82 */ u16 _e82 = 0;
    /* 0xe84 */ sead::BitFlag32 _e84;
    /* 0xe88 */ void* _e88 = nullptr;
    /* 0xe90 */ u32 _e90 = 0;
    /* 0xe98 */ sead::SafeString _e98;
    /* 0xea8 */ sead::SafeArray<ksys::act::BaseProcLink, 8> _ea8{};
    /* 0xf28 */ Actor* _f28 = this;
    /* 0xf30 */ s32 _f30 = -1;
    /* 0xf38 */ void* _f38 = nullptr;
    /* 0xf40 */ s32 _f40 = 0;
    /* 0xf44 */ s32 _f44 = -1;
    /* 0xf48 */ f32 _f48 = 0;
    /* 0xf4c */ u32 _f4c = 0;
    /* 0xf50 */ f32 _f50 = -1.0;
    /* 0xf54 */ u16 _f54 = 0;
    /* 0xf58 */ Actor* _f58 = this;
    /* 0xf60 */ Actor* _f60 = this;
    /* 0xf68 */ u8 _f68[0x1010 - 0xf68];  // BoneHandle (ctor 0x7100d3b3f0)
    /* 0x1010 */ u8 _1010[0x10b8 - 0x1010];  // BoneHandle
    /* 0x10b8 */ s64 _10b8 = -1;
    /* 0x10c0 */ u8 _10c0[0x10f8 - 0x10c0];
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
    /* 0x12d0 */ void* _12d0 = nullptr;
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
    /* 0x13c0 */ void* _13c0 = nullptr;
    /* 0x13c8 */ Unk_71023579d8 _13c8;
    /* 0x1408 */ Unk_71023579a8 _1408;
    /* 0x1448 */ Unk_7102357978 _1448;
    /* 0x1488 */ Unk_7102357948 _1488;
};
KSYS_CHECK_SIZE_NX150(Enemy, 0x14c8);

}  // namespace uking::act
