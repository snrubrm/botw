#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <limits>
#include <math/seadVector.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::phys {
class RigidBody;
}

namespace uking::act {

// Name from the CSV (BeamBase::*, from the vtable analysis; the namespace is a guess). Direct child of
// DynamicActor: the RTTI static 0x71025ae570 is initialised with the Derive<DynamicActor> vtable. The
// base of the Beam actor (CSV Beam::*, new(0xc98), RTTI static 0x71025ae560, which adds two 8-byte members
// at 0xc88 / 0xc90). ctor 0x710000228c (CSV BeamBase::ctor), vtable GOT 0x2578da0 (166 slots: DynamicActor's
// 163 + m163 / m164 / m165). The accessor `acc::BeamBase` (0x7100003d30 getBeamLevel) casts to this class.
// Layout from the ctor; the constructor and the virtual functions are not decompiled yet.
// Members are public: AI code reads them directly (PriestBossBeamExplode reads `_c68`).
class BeamBase : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(BeamBase, DynamicActor)
public:
    explicit BeamBase(const CreateArg& arg);
    ~BeamBase() override;

    // 0x7100002080: never unloads.
    bool shouldUnload(s32* a1) override { return false; }

    void initMaybe() override;
    /* 163 */ virtual void m163();
    /* 164 */ virtual void m164(void* arg);
    // The position of the beam (the actor's translation).
    /* 165 */ virtual void m165(sead::Vector3f* out);
    /* 166 */ virtual void m166() {}

    // 0x710000395c: called by PriestBossEyeBeam::sub_710051459C right after creating the beam: locks
    // `_b90._0`, `_b90._40` acquires `shooter`, `_be0` searches `bone` in the shooter's model, `_c18 = *offset`.
    // 0x7100003804 (declared only; lane1 s25): the same without the offset (LastBossBeamAttackRoot).
    void sub_7100003804(ksys::act::Actor* shooter, const sead::SafeString& bone);
    void sub_710000395C(ksys::act::Actor* shooter, const sead::SafeString& bone,
                        const sead::Vector3f* offset);

    // A critical section followed by a link (the dtor keeps &_b90 and &_b90._40 in registers across the inlined
    // ~BoneAccessKeyEx call): the shooter that sub_7100003804 / sub_710000395C fill in together with _be0 / _c18.
    struct Unk_b90 {
        /* 0x00 */ sead::CriticalSection _0;
        /* 0x40 */ ksys::act::BaseProcLink _40;  // the shooter
    };
    /* 0xb90 */ Unk_b90 _b90;
    /* 0xbe0 */ gsys::BoneAccessKeyEx _be0;  // the bone in the shooter's model
    /* 0xc18 */ sead::Vector3f _c18 = sead::Vector3f::zero;  // offset
    /* 0xc24 */ f32 _c24 = std::numeric_limits<f32>::max();
    /* 0xc28 */ ksys::act::BaseProcLink _c28;
    /* 0xc38 */ ksys::act::BaseProcLink _c38;
    /* 0xc48 */ sead::Vector3f _c48{0.0f, 0.0f, 0.0f};
    /* 0xc54 */ u8 _c54[4];
    /* 0xc58 */ sead::Vector2f _c58{0.0f, 0.0f};
    /* 0xc60 */ f32 _c60 = 0;
    /* 0xc64 */ u8 _c64[4];
    /* 0xc68 */ sead::Vector3f _c68 = sead::Vector3f::zero;  // a position (the beam's target / hit point)
    /* 0xc78 */ u64 _c78 = 0;
    /* 0xc80 */ f32 _c80 = 1.0f;
    /* 0xc84 */ sead::Atomic<u32> _c84 = 0;
};
KSYS_CHECK_SIZE_NX150(BeamBase, 0xc88);

}  // namespace uking::act

namespace uking::act {

// Name from the CSV (Beam::*; the namespace is a guess). Factory 0x7100001c20: new(0xc98) + inlined ctor (two
// pointer members). RTTI static 0x71025ae560.
// TODO: incomplete (m84 = 396 B, reflect / hit handling, is not written).
class Beam : public BeamBase {
    SEAD_RTTI_OVERRIDE(Beam, BeamBase)
public:
    explicit Beam(const CreateArg& arg);
    // Empty body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229): the
    // original keeps the vtable stores in Beam's D1 / D0 before calling BeamBase's destructor.
    ~Beam() override { ; }

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    void initMaybe() override;
    void m165(sead::Vector3f* out) override;

    /* 0xc88 */ ksys::phys::RigidBody* _c88 = nullptr;  // the main body
    /* 0xc90 */ ksys::phys::RigidBody* _c90 = nullptr;  // the "Atk" group's "AtkBody"
};
KSYS_CHECK_SIZE_NX150(Beam, 0xc98);

}  // namespace uking::act
