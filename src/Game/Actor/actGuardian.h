#pragma once

#include <container/seadBuffer.h>
#include <gsys/gsysModelAccessKey.h>
#include <limits>
#include <prim/seadBitFlag.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

// (global namespace, like the other Unk_<vtable> helpers)
// Placeholder name (vtable 0x710243c250, ctor 0x710066e07c, D2 0x710066e0ec). Guardian::_1908
// (onPreDeleteStart_ forwards to 0x710066e15c on it).
class Unk_710243c250 {
public:
    explicit Unk_710243c250(ksys::act::Actor* owner);
    virtual ~Unk_710243c250();

    // 0x710066e15c (declared only; unnamed in the CSV): registers this object with a manager's list
    // (instance pointer at GOT 0x7102579100, member at +0xb90).
    void sub_710066E15C();

    /* 0x08 */ void* _8 = nullptr;
    /* 0x10 */ void* _10 = nullptr;
    /* 0x18 */ Unk_710243c250* _18 = this;
    /* 0x20 */ void* _20 = nullptr;
    /* 0x28 */ ksys::act::BaseProcLink _28;
    /* 0x38 */ f32 _38 = std::numeric_limits<f32>::max();
    /* 0x3c */ u32 _3c;
    /* 0x40 */ s32 _40;
};
KSYS_CHECK_SIZE_NX150(Unk_710243c250, 0x48);

class Unk_7100041da4;  // actionGuardianMoveTo.h

namespace ksys::res {
class GParamListObjectGuardian;
}

namespace uking::act {

class Guardian;

// Placeholder name (vtable 0x710235a078; inherits DamageCallback's RTTI). Guardian::_18c8.
// TODO: incomplete (`call` is not decompiled).
class Unk_710235a078 : public dmg::DamageCallback {
public:
    explicit Unk_710235a078(Guardian* guardian) : mGuardian(guardian) {}

    void call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) override;

    /* 0x28 */ Guardian* mGuardian;
    /* 0x30 */ f32 _30 = -std::numeric_limits<f32>::max();
    /* 0x34 */ f32 _34 = -std::numeric_limits<f32>::max();
    /* 0x38 */ f32 _38 = -std::numeric_limits<f32>::max();
};
KSYS_CHECK_SIZE_NX150(Unk_710235a078, 0x40);

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
    // lane4 s46 (placeholder names): 0x710003955c: the Guardian param. 0x7100033e10: a table of the
    // GuardianControllerType (0, 1: 6, 2: 3). 0x710003b1e4: 0xffffffff / that value * a (0 for type 0).
    const ksys::res::GParamListObjectGuardian* sub_710003955C() const;
    int sub_7100033E10() const;
    u32 sub_710003B1E4(u32 a) const;
    // 0x710003b238: (number of set bits of _14cc) / (the table value); 0 for controller type 0.
    f32 sub_710003B238() const;
    // 0x71000370b4 (placeholder name): `_15cc < 30`.
    bool sub_71000370B4() const;
    // 0x710003b2c4 / 0x710003b2ec: the Guardian param's MaxSpeed / CannonBoneName.
    f32 sub_710003B2C4() const;
    const sead::SafeString& sub_710003B2EC() const;
    // 0x710003b090: writes _14d4.
    void sub_710003B090(u32 value);
    // 0x710003b43c / 0x710003b4c8: the target (link at Enemy::_c48._8, position _c48._18) is closer /
    // farther than a tunable (floats 15.0 / 25.0 in non-const data at 0x710235ab6c / 0x710235ab70, so
    // not definable here: clang folds a never-written static; no target: false / true). Constness is a
    // guess. m34 reads its constants (5.0 / 15.0) from the same kind of table (0x710235ae14 / 10).
    bool sub_710003B43C() const;
    bool sub_710003B4C8() const;

    /* 0x14c8 */ sead::BitFlag32 _14c8;  // flags
    /* 0x14cc */ sead::BitFlag16 _14cc;  // bit i: _1528[i] is not woken up (onWakeUpRequested_)
    /* 0x14ce */ u8 _14ce = 0xff;
    // 0x14d0-0x14d7 and 0x14d8-0x14df are zeroed by two 64-bit stores in the ctor; _14d4 is written
    // alone by sub_710003B090 and _14d8 / _14dc by sub_7100035A90 (so they are 32-bit fields).
    /* 0x14d0 */ u32 _14d0 = 0;
    /* 0x14d4 */ u32 _14d4 = 0;
    /* 0x14d8 */ u32 _14d8 = 0;  // state (sub_7100035A90)
    /* 0x14dc */ f32 _14dc = 0;  // (GuardianStopWait: stop time limit)
    /* 0x14e0 */ void* _14e0 = nullptr;
    /* 0x14e8 */ void* _14e8 = nullptr;
    /* 0x14f0 */ f32 _14f0 = 1.0f;  // +-1 (random sign, set by sub_7100035A90)
    /* 0x14f8 */ ksys::act::BaseProcLink _14f8;
    /* 0x1508 */ ksys::act::BaseProcLink _1508;
    /* 0x1518 */ sead::Buffer<ksys::act::BaseProcLink> _1518;  // actors put to sleep / woken with it
    /* 0x1528 */ sead::Buffer<ksys::act::BaseProcLink> _1528;
    /* 0x1538 */ ksys::act::BaseProcLink _1538[5];
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
        // 0x7100042048: updates the navigation position (declaration only).
        void sub_7100042048();

        u8 _0[0x30];
        ksys::phys::NavMeshCharacter* _30;  // m45
        u8 _38[0x50 - 0x38];
        // The movement provider (GuardianMoveTo's second base), set in GuardianMoveTo::enter_ and cleared
        // in leave_.
        Unk_7100041da4* _50;
    };
    /* 0x15b0 */ Unk1* _15b0 = nullptr;
    /* 0x15b8 */ u32 _15b8 = 0;
    /* 0x15c0 */ void* _15c0 = nullptr;
    /* 0x15c8 */ u32 _15c8 = 0;
    /* 0x15cc */ f32 _15cc;
    /* 0x15d0 */ void* _15d0 = nullptr;
    /* 0x15d8 */ u32 _15d8 = 0;
    /* 0x15e0 */ void* _15e0 = nullptr;
    /* 0x15e8 */ u32 _15e8 = 0;
    /* 0x15f0 */ void* _15f0 = nullptr;
    /* 0x15f8 */ gsys::BoneAccessKeyEx _15f8;
    /* 0x1630 */ gsys::BoneAccessKeyEx _1630;
    /* 0x1668 */ gsys::BoneAccessKeyEx _1668;
    /* 0x16a0 */ gsys::BoneAccessKeyEx _16a0;
    /* 0x16d8 */ gsys::BoneAccessKeyEx _16d8;
    /* 0x1710 */ gsys::BoneAccessKeyEx _1710;
    /* 0x1748 */ gsys::BoneAccessKeyEx _1748;
    /* 0x1780 */ void* _1780 = nullptr;
    /* 0x1788 */ void* _1788 = nullptr;
    /* 0x1790 */ void* _1790 = nullptr;
    /* 0x1798 */ void* _1798 = nullptr;
    /* 0x17a0 */ void* _17a0 = nullptr;
    /* 0x17a8 */ void* _17a8 = nullptr;
    /* 0x17b0 */ void* _17b0 = nullptr;
    /* 0x17b8 */ u32 _17b8 = 0;
    /* 0x17bc */ u32 _17bc;
    /* 0x17c0 */ Unk_710235aba0 _17c0{this, 0x8000040};
    /* 0x17f0 */ Unk_710235abc8 _17f0{this, 0x8000006};
    /* 0x1848 */ Unk_7102450528 _1848;
    /* 0x18c0 */ void* _18c0 = nullptr;
    /* 0x18c8 */ Unk_710235a078 _18c8{this};
    /* 0x1908 */ Unk_710243c250 _1908{this};
};
KSYS_CHECK_SIZE_NX150(Guardian, 0x1950);

}  // namespace uking::act
