#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/Utils/Types.h"

// Velocity / rotation "vibration" checker; a non-polymorphic base class of Unk_71025b7698 (placeholder
// name; at offset 0x8 of the objects, its address is what the AI code passes to its methods).
struct Unk_71025b7698_Data {
    // 0x710071f494: init(s32 check_time, f32), 0x710071f47c: reset()
    void sub_710071F494(s32 check_time, f32 value);
    void sub_710071F47C();

    /* 0x00 */ f32 _0 = 5;
    /* 0x04 */ f32 _4 = 5;
    /* 0x08 */ s32 _8 = 5;
    /* 0x0c */ s32 _c = 5;
    /* 0x10 */ bool _10 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71025b7698_Data, 0x14);

// Intermediate class between the AI tree variable root class and Unk_71023ea3f8; placeholder name
// from its RTTI typeInfo static (0x71025b7698); see Unk_71025b0588.
// Evidence for the class: the original's checkDerivedRuntimeTypeInfo of Unk_71023ea3f8
// (0x71003ad980) compares against the statics 0x71025b7688, 0x71025b7698 and the root's
// 0x71025afb58, and the typeInfo of Unk_71023ea3f8 has its own RuntimeTypeInfo::Derive vtable
// (GOT 0x7102585108 -> 0x71023d6cc0, not the root's 0x710235ff20).
class Unk_71025b7698 : public Unk_71025afb58, public Unk_71025b7698_Data {
    SEAD_RTTI_OVERRIDE(Unk_71025b7698, Unk_71025afb58)
public:
    using Data = Unk_71025b7698_Data;
};

// Reference-counted object behind the "RefVelRotVibrateCheckerforAI" AI tree variable
// (NavMoveTarget, EnemyRangeKeepMove). Placeholder name = vtable address (0x71023ea3f8; D2
// 0x7100115fec is the empty function shared with other classes, D0 0x71003adafc a delete thunk, RTTI
// functions 0x71003ad980 / 0x71003adaa0). Built inline by
// Unk_71025afb58Ref<Unk_71023ea3f8>::acquire.
class Unk_71023ea3f8 : public Unk_71025b7698 {
    SEAD_RTTI_OVERRIDE(Unk_71023ea3f8, Unk_71025b7698)
public:
    /* 0x1c */ s32 mRefCount = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71023ea3f8, 0x20);
