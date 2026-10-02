#pragma once

#include <prim/seadBitFlag.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::act {

// Name from the CSV (Guardian::*). vtable 0x710235a560 (181 slots, no new virtuals), RTTI static
// 0x71025af268 (parent: Enemy). ctor 0x7100032570 (CSV Guardian::ctor), factory 0x71000323fc:
// new(0x1950).
// TODO: incomplete. Members are public: AI code (and the GuardianComponent functions) read them.
class Guardian : public Enemy {
    SEAD_RTTI_OVERRIDE(Guardian, Enemy)
public:
    explicit Guardian(const CreateArg& arg);
    // CSV Guardian::construct: the actor factory function.
    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
    ~Guardian() override;

protected:
    void onDeleteRequested_(DeleteReason reason) override;
    void onSleepRequested_(SleepWakeReason reason) override;
    void onWakeUpRequested_(SleepWakeReason reason) override;
    void onEnterSleep_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    bool m33() override;
    void m34(sead::Vector3f* pos, f32* value) override;
    void m44() override;
    ksys::phys::NavMeshCharacter* m45() override;
    void initMaybe() override;
    void calcMaybe() override;
    void updatePositionMaybe() override;
    void m73() override;
    bool m80(const ksys::MessageAck& ack) override;
    bool m81(const ksys::Message& message) override;
    void updateMtxFromPhysics() override;

    /* 0x14c8 */ sead::BitFlag32 _14c8;  // flags
    /* 0x14cc */ u16 _14cc = 0;
    /* 0x14ce */ u8 _14ce;
    /* 0x14d0 */ void* _14d0 = nullptr;
    /* 0x14d8 */ void* _14d8 = nullptr;
    /* 0x14e0 */ void* _14e0 = nullptr;
    /* 0x14e8 */ void* _14e8 = nullptr;
    /* 0x14f0 */ u32 _14f0;
    /* 0x14f8 */ ksys::act::BaseProcLink _14f8;
    /* 0x1508 */ ksys::act::BaseProcLink _1508;
    /* 0x1518 */ u32 _1518 = 0;
    /* 0x1520 */ void* _1520 = nullptr;
    /* 0x1528 */ u32 _1528 = 0;
    /* 0x1530 */ void* _1530 = nullptr;
    /* 0x1538 */ ksys::act::BaseProcLink _1538;
    /* 0x1548 */ ksys::act::BaseProcLink _1548;
    /* 0x1558 */ ksys::act::BaseProcLink _1558;
    /* 0x1568 */ ksys::act::BaseProcLink _1568;
    /* 0x1578 */ ksys::act::BaseProcLink _1578;
    /* 0x1588 */ void* _1588 = nullptr;
    /* 0x1590 */ void* _1590 = nullptr;
    /* 0x1598 */ void* _1598 = nullptr;
    /* 0x15a0 */ u32 _15a0 = 0;
    /* 0x15a8 */ sead::Vector3f* _15a8 = nullptr;  // m34 reads a position through it
    struct Unk1 {
        u8 _0[0x30];
        ksys::phys::NavMeshCharacter* _30;  // m45
    };
    /* 0x15b0 */ Unk1* _15b0 = nullptr;
    /* 0x15b8 */ u32 _15b8 = 0;
    /* 0x15c0 */ void* _15c0 = nullptr;
    /* 0x15c8 */ u32 _15c8 = 0;
    /* 0x15cc */ u32 _15cc;
    /* 0x15d0 */ void* _15d0 = nullptr;
    /* 0x15d8 */ u32 _15d8 = 0;
    /* 0x15e0 */ void* _15e0 = nullptr;
    /* 0x15e8 */ u32 _15e8 = 0;
    /* 0x15f0 */ void* _15f0 = nullptr;
    // seven gsys::BoneAccessKeyEx (0x15f8-0x1780), message senders (Unk_7102357d20 family) from
    // 0x17c0, BaseProcLinks 0x17d8 / 0x1808 / 0x1818 / 0x1850 / 0x1880 / 0x1890, object 0x1908
    // (onPreDeleteStart_ forwards to 0x710066e15c on it)
    /* 0x15f8 */ u8 _15f8[0x1950 - 0x15f8];
};
KSYS_CHECK_SIZE_NX150(Guardian, 0x1950);

}  // namespace uking::act
