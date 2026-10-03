#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <limits>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

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
    /* 0xb90 */ sead::CriticalSection _b90;
    /* 0xbd0 */ ksys::act::BaseProcLink _bd0;
    /* 0xbe0 */ gsys::BoneAccessKeyEx _be0;
    /* 0xc18 */ sead::Vector3f _c18 = sead::Vector3f::zero;
    /* 0xc24 */ f32 _c24 = std::numeric_limits<f32>::max();
    /* 0xc28 */ ksys::act::BaseProcLink _c28;
    /* 0xc38 */ ksys::act::BaseProcLink _c38;
    /* 0xc48 */ sead::Vector3f _c48{0.0f, 0.0f, 0.0f};
    /* 0xc54 */ u8 _c54[4];
    /* 0xc58 */ sead::Vector3f _c58{0.0f, 0.0f, 0.0f};
    /* 0xc64 */ u8 _c64[4];
    /* 0xc68 */ sead::Vector3f _c68 = sead::Vector3f::zero;  // a position (the beam's target / hit point)
    /* 0xc78 */ u64 _c78 = 0;
    /* 0xc80 */ f32 _c80 = 1.0f;
    /* 0xc84 */ u32 _c84 = 0;
};
KSYS_CHECK_SIZE_NX150(BeamBase, 0xc88);

}  // namespace uking::act
