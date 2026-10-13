#pragma once

#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"

namespace ksys::phys {
class RigidBody;
class SphereRigidBody;
class CollisionInfo;
class InstanceSet;
class RigidBodyFromShape;
}

namespace gsys {
class Model;
class ModelAnimation;
}

namespace ksys::res {
class ResDerived;
class Unk_71024f9958;
}

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
        SEAD_RTTI_BASE(Unit)
    public:
        Unit();
        virtual ~Unit();
        virtual bool m4(Swarm* owner, sead::Heap* heap);
        bool sub_71002D9588(sead::Heap* heap);
        virtual void m5();
        virtual void m6();
        virtual void m7();
        virtual void m8();
        virtual bool m9();
        virtual void m10();

        /* 0x08 */ sead::Matrix34f _8;  // unit pose (SwarmFlyAttack reads the translation)
        // 2D9344 constructs VFRVec3f here; C37D4 writes value/prev_value, 729FAC reads mean.
        /* 0x38 */ ksys::VFRVec3f _38;
        /* 0x5c */ f32 _5c;  // random 0.1-0.2 set by BeeSwarmNormal::enter_
        /* 0x60 */ sead::Vector3f _60;
        /* 0x6c */ sead::Vector3f _6c;
        /* 0x78 */ gsys::Model* _78;  // effect model (m63 plays it for every unit)
        /* 0x80 */ s32 _80;
        /* 0x88 */ sead::Buffer<ksys::res::ResDerived> _88;
        /* 0x98 */ sead::Buffer<ksys::res::Unk_71024f9958> _98;
        /* 0xa8 */ gsys::ModelAnimation* _a8;
        /* 0xb0 */ Swarm* _b0;  // the owner (Swarm::sub_71002D484C)
        /* 0xb8 */ u16 _b8;  // state flags (bit 1: active; bits 1-3 are rewritten by the two functions below)
        /* 0xbc */ f32 _bc;  // model opacity, initialized to 1 by the unit constructor
        u8 _c0[0xd4 - 0xc0];

        // 0x71002daa98 (SwarmPatternMovingSphere::m8): unless bit 1 is set, replaces bits 2 / 3 with 8.
        void sub_71002DAA98();
        // 0x71002daa58: applies opacity to this unit's model without fading.
        void sub_71002DAA58(f32 opacity);
        // 0x71002daa78 (SwarmPatternMovingSphere::m9): if bit 1 is set, replaces bits 1-3 with 4 and clears _bc.
        void sub_71002DAA78();
        // Full 2D93E8 copies a Matrix33 into the pose rotation; 72A514 / 72A5F8 supply it.
        void sub_71002D93E8(const sead::Matrix33f& rotation);
        // 2D7668 passes the unit position in its owner's space.
        void sub_71002D9434(const sead::Vector3f& position);
        // SwarmAreaDamaged consumes all three owner-space position components.
        void sub_71002D94C8(sead::Vector3f* out) const;
        // 0x71002da3a0 (declared only; 320 B): material animation (name, frame) of the unit; called for every unit by
        // sub_710072A778.
        bool sub_71002DA3A0(f32 frame, const sead::SafeString& name);
    };

    KSYS_CHECK_SIZE_NX150(Unit, 0xd8);

    // The "Tgt" rigid body of a swarm unit (0x28 bytes; placeholder; SetThroughArrow reads _20).
    struct UnitBody {
        u8 _0[0x18];
        /* 0x18 */ Unit* _18;
        /* 0x20 */ ksys::phys::RigidBody* _20;
    };

    explicit Swarm(const CreateArg& arg);
    ~Swarm() override;

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    void sub_71002D47D4(const sead::SafeString& name);
    // 0x71002d484c (placeholder name): marks `unit` (one of ours) as gone: bit 0 of _b8 and one fewer in _1610.
    void sub_71002D484C(Unit* unit);

protected:
    InitResult init_() override;
    bool startPreparingForPreDelete_() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void preDelete2_(const PreDeleteArg& arg) override;

public:
    bool m33() override { return true; }
    void m34(sead::Vector3f* pos, f32* value) override;
    void m43(bool on) override;
    void m61(f32 rate) override;
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
    void m114(bool, bool) override;
    Unk_71025ae680* m178(sead::Heap* heap) override;
    // Slot 39 (overrides Actor's `bool m39()`): true while the swarm has units.
    bool m39() override;
    // Slot 40 (Actor declares `void* m40()`): _14c8[idx]->_78. Takes an index, so it hides the base
    // signature instead of overriding it; our toolchain puts it in a new end slot.
    void* m40(s32 idx);

    /* 0x14c8 */ sead::Buffer<Unit*> _14c8;  // units
    // 0x71002d56b4 constructs the sphere body and its collision information. The four
    // records are indexed with a 0x30 stride by 0x71002d47d8.
    struct BodyInfo {
        bool sub_71002D56B4(Actor* actor, sead::Heap* heap, ksys::phys::InstanceSet* instance,
                            ksys::phys::RigidBodyFromShape* shape);
        bool sub_71002D481C() const;
        f32 sub_71002D5F30() const;
        void sub_71002D5F44(const sead::Vector3f& position);
        void sub_71002D71C8(bool paused);

        /* 0x00 */ sead::Vector3f _0;
        /* 0x0c */ sead::Vector3f _c;
        /* 0x18 */ ksys::phys::SphereRigidBody* _18 = nullptr;
        /* 0x20 */ Actor* _20 = nullptr;
        /* 0x28 */ ksys::phys::CollisionInfo* _28 = nullptr;
    };
    static_assert(sizeof(BodyInfo) == 0x30);
    bool sub_71002D47D8(s32 idx) const;

    /* 0x14d8 */ ksys::as::ASList* _14d8 = nullptr;
    /* 0x14e0 */ ksys::as::ASList* _14e0 = nullptr;
    /* 0x14e8 */ ksys::as::ASList* _14e8 = nullptr;
    /* 0x14f0 */ ksys::as::ASList* _14f0 = nullptr;
    /* 0x14f8 */ sead::SafeArray<BodyInfo, 4> _14f8;
    /* 0x15b8 */ sead::Matrix34f _15b8;  // the inverse of the actor matrix (setMtx)
    /* 0x15e8 */ sead::Buffer<UnitBody> _15e8;
    /* 0x15f8 */ sead::Buffer<UnitBody> _15f8;
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

// The two unit variants allocated by Swarm::prepareInit_.
class Unk_71023d0d08 : public uking::act::Swarm::Unit {
    SEAD_RTTI_OVERRIDE(Unk_71023d0d08, uking::act::Swarm::Unit)
public:
    Unk_71023d0d08();
    ~Unk_71023d0d08() override;
};
KSYS_CHECK_SIZE_NX150(Unk_71023d0d08, 0xd8);

class Unk_71023d0e08 : public uking::act::Swarm::Unit {
    SEAD_RTTI_OVERRIDE(Unk_71023d0e08, uking::act::Swarm::Unit)
public:
    Unk_71023d0e08();
    ~Unk_71023d0e08() override;
    bool m4(uking::act::Swarm* owner, sead::Heap* heap) override;
    void m6() override;
    void m7() override;
    void m8() override;
    void m10() override;

    void sub_71002DAE8C();
    void sub_71002DAEDC();
    void sub_71002DB2EC();

    // The timer reuses the base's four bytes of tail padding.
    /* 0xd4 */ ksys::Timer _d4;
    /* 0xe0 */ f32 _e0;
    /* 0xe4 */ f32 _e4;
    /* 0xe8 */ f32 _e8;
    /* 0xec */ f32 _ec;
    /* 0xf0 */ f32 _f0;
    /* 0xf4 */ s32 _f4;
};
KSYS_CHECK_SIZE_NX150(Unk_71023d0e08, 0xf8);
