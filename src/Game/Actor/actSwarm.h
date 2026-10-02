#pragma once

#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include "Game/Actor/actEnemy.h"

namespace uking::act {

// Name from the CSV (Swarm::*): swarms of small enemies (bees, ...). vtable 0x71023d0530 (181 slots, no
// new virtuals), RTTI static 0x71025b08b8 (parent: Enemy). Factory 0x71002d4130 (CSV Swarm::construct,
// which inlines the ctor): new(0x1640).
// TODO: incomplete. Members are public: AI code reads them directly.
class Swarm : public Enemy {
    SEAD_RTTI_OVERRIDE(Swarm, Enemy)
public:
    // One member of the swarm (placeholder; the AI patterns write _60 / _68).
    struct Unit {
        u8 _0[0x5c];
        /* 0x5c */ f32 _5c;  // random 0.1-0.2 set by BeeSwarmNormal::enter_
        /* 0x60 */ sead::Vector3f _60;
        u8 _6c[0x78 - 0x6c];
        /* 0x78 */ void* _78;  // returned by vtable slot 40 for unit `idx`
    };

    explicit Swarm(const CreateArg& arg);
    ~Swarm() override;

protected:
    InitResult init_() override;
    bool startPreparingForPreDelete_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    bool m33() override { return true; }
    void m34(sead::Vector3f* pos, f32* value) override;
    void m43(bool on) override;
    void m61() override;
    void m63() override;
    void initMaybe() override;
    void m68() override;
    void calcMaybe() override;
    void updatePositionMaybe() override;
    void m74() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    bool m81(const ksys::Message& message) override;
    void setMtx(const sead::Matrix34f& mtx, bool a2, bool a3) override;
    int getExtraHeapSize() override;
    void m103() override;
    void m108() override;
    void m114() override;
    Unk_71025ae680* m178(sead::Heap* heap) override;
    // Not declared yet: slot 39 (returns the unit count, Actor declares `bool m39()`) and slot 40
    // (`(int idx)` returning _14c8[idx]->_78, Actor declares `void m40()`).

    /* 0x14c8 */ sead::Buffer<Unit*> _14c8;  // units
    // five 0x30-byte entries (first three pointers zeroed) at 0x14e0 + 0x30 * i
    /* 0x14d8 */ u8 _14d8[0x15e8 - 0x14d8];
    /* 0x15e8 */ u32 _15e8 = 0;
    /* 0x15f0 */ void* _15f0 = nullptr;
    /* 0x15f8 */ u32 _15f8 = 0;
    /* 0x1600 */ void* _1600 = nullptr;
    /* 0x1608 */ u8 _1608[0x1610 - 0x1608]{};
    /* 0x1610 */ s32 _1610 = 0;  // living unit count? (0 -> SwarmReaction deletes the actor)
    /* 0x1614 */ bool _1614 = false;
    /* 0x1618 */ Actor* _1618 = this;
    /* 0x1620 */ f32 _1620 = 0.1;
    /* 0x1624 */ f32 _1624 = 0.1;
    // Set by the SwarmPattern behaviors (pattern type / sub-type?).
    /* 0x1628 */ s32 _1628 = 0;
    /* 0x162c */ s32 _162c = 0;
    /* 0x1630 */ u32 _1630 = 0;
    /* 0x1638 */ u64 _1638 = 0;
};
KSYS_CHECK_SIZE_NX150(Swarm, 0x1640);

}  // namespace uking::act
