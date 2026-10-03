#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71000b0800.h"
#include "Game/AI/aiUnk_71023da520.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/Utils/Types.h"


// Placeholder name = constructor address (0x71006f3044; no real name known). Beam helper embedded in
// NeckSpinBeam (+0xb8), BeamosStaticBeam (+0xa8) and ForkGanonBeastBeamShoot (+0x68): spawns the beam
// actor (named by the actions' "BeamActorName" / "BeamActorKey" params) and keeps the BaseProcLink
// to it in the shared "BeamActorLink" AI tree variable (Unk_71023da520). Only the constructor is
// decompiled; the destructor (0x71006f3140, which releases `_80`) and the other methods below are
// declared only.
class Unk_71006f3044 {
public:
    explicit Unk_71006f3044(ksys::act::Actor* actor);
    // 0x71006f3140 (declared only): deletes the beam actor, releases `_80`.
    ~Unk_71006f3044();

    /* 0x00 */ u32 _0 = 0;
    /* 0x04 */ u32 _4 = 0;
    /* 0x08 */ ksys::act::Actor* mActor;
    /* 0x10 */ sead::Vector3f _10 = sead::Vector3f::zero;
    /* 0x1c */ sead::Vector3f _1c = sead::Vector3f::ez;
    /* 0x28 */ sead::FixedSafeString<64> _28;
    /* 0x80 */ Unk_71000b0800<Unk_71023da520> _80;
    /* 0x88 */ Unk_710244ffe8 _88;
    /* 0xa0 */ Unk_7102450010 _a0;
    /* 0xb8 */ bool _b8 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71006f3044, 0xc0);
