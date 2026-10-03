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

    // 0x7100034514: sets or clears bit 4 of _14c8.
    void sub_7100034514(bool on);
    // 0x7100035a90: switches the state _14d8 (no-op if equal; state 5 sends message 0x800000d to the
    // actor, 12 / 13 toggle the attention client; picks a new random sign for _14f0).
    void sub_7100035A90(s32 state);
    // 0x710003b090: writes _14d4.
    void sub_710003B090(u32 value);
    // 0x710003b43c / 0x710003b4c8: the target (link at Enemy::_c48._8, position _c48._18) is closer /
    // farther than a tunable (floats 15.0 / 25.0 in non-const data at 0x710235ab6c / 0x710235ab70, so
    // not definable here: clang folds a never-written static; no target: false / true). Constness is a
    // guess. m34 reads its constants (5.0 / 15.0) from the same kind of table (0x710235ae14 / 10).
    bool sub_710003B43C() const;
    bool sub_710003B4C8() const;

    /* 0x14c8 */ sead::BitFlag32 _14c8;  // flags
    /* 0x14cc */ u16 _14cc = 0;
    /* 0x14ce */ u8 _14ce;
    // 0x14d0-0x14d7 and 0x14d8-0x14df are zeroed by two 64-bit stores in the ctor; _14d4 is written
    // alone by sub_710003B090 and _14d8 / _14dc by sub_7100035A90 (so they are 32-bit fields).
    /* 0x14d0 */ u32 _14d0 = 0;
    /* 0x14d4 */ u32 _14d4 = 0;
    /* 0x14d8 */ u32 _14d8 = 0;  // state (sub_7100035A90)
    /* 0x14dc */ u32 _14dc = 0;
    /* 0x14e0 */ void* _14e0 = nullptr;
    /* 0x14e8 */ void* _14e8 = nullptr;
    /* 0x14f0 */ f32 _14f0 = 1.0f;  // +-1 (random sign, set by sub_7100035A90)
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
    // Placeholder (type and size unknown): the structure Guardian::_15a8 points to. Guardian::m34 reads a
    // position at +0; the GuardianAI accessors (0x710040e008 / 0x710040e048) copy the vectors at +0x3c /
    // +0x30 out.
    struct Unk15a8 {
        /* 0x00 */ sead::Vector3f _0;
        /* 0x0c */ u8 _c[0x30 - 0xc];
        /* 0x30 */ sead::Vector3f _30;
        /* 0x3c */ sead::Vector3f _3c;
    };
    /* 0x15a8 */ Unk15a8* _15a8 = nullptr;
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
