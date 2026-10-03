#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace ksys::act {
class Actor;
}

// Object shared by the Lynel body behaviors through the "LynelBodyControlUnit" AI tree variable.
// Placeholder name from its RTTI typeInfo static (0x71025ba778; parent: Unk_71025afb58); size and most
// members are unknown.
class Unk_71025ba778 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025ba778, Unk_71025afb58)
public:
    // 0x710070f79c: (LynelBodyFitToGroundNormal::m8) attaches the "Man_Spine_1" bone handle to the actor
    // if needed and sets bit 1 of `_8`.
    void sub_710070F79C(ksys::act::Actor* actor);
    // 0x710070f820: (LynelBodyFitToGroundNormal::m9; the actor argument is unused) clears bit 1 of `_8`.
    void sub_710070F820(ksys::act::Actor* actor);

    /* 0x08 */ u8 _8;  // flags; bit 1: body fitting to the ground normal enabled
    /* 0x09 */ u8 _9[0xc - 0x9];
    /* 0x0c */ f32 _c;  // set to 1 / 0 by LynelStandBody::m8 / m9
    /* 0x10 */ u8 _10[0x100 - 0x10];
    /* 0x100 */ ksys::act::BoneHandle _100;  // "Man_Spine_1"
    /* 0x1a8 */ f32 _1a8;  // the CorrectAngleMax of LynelBodyFitToGroundNormal
};
