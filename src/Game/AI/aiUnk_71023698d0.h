#pragma once

#include <basis/seadTypes.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/Utils/Types.h"

// Position-history "vibration" checker; a non-polymorphic base class of Unk_71025b0588 (placeholder
// name; at offset 0x8 of the objects, its address is what the AI code passes to its methods).
struct Unk_71025b0588_Data {
    /* 0x00 */ sead::Vector3f _0[10];
    /* 0x78 */ f32 _78 = 10;
    /* 0x7c */ f32 _7c = 0;
    /* 0x80 */ f32 _80 = 0;
    /* 0x84 */ f32 _84 = 1;
    /* 0x88 */ f32 _88 = 10;
    /* 0x8c */ bool _8c = false;
    /* 0x90 */ sead::BoundBox3f _90;
};
KSYS_CHECK_SIZE_NX150(Unk_71025b0588_Data, 0xa8);

// Intermediate class between the AI tree variable root class and Unk_71023698d0; placeholder name
// from its RTTI typeInfo static (0x71025b0588). Its data base class is constructed before the
// derived vtable store in the original's object creation (0x71000b0800), and AI code converts
// object pointers to the data base class (+0x8) after the type check.
// Evidence for the class: the original's checkDerivedRuntimeTypeInfo of Unk_71023698d0
// (0x71000b14d4) compares against the statics 0x71025b0578, 0x71025b0588 and the root's
// 0x71025afb58, and the typeInfo of Unk_71023698d0 has its own RuntimeTypeInfo::Derive vtable
// (0x71023698b8, not the root's 0x710235ff20).
class Unk_71025b0588 : public Unk_71025afb58, public Unk_71025b0588_Data {
    SEAD_RTTI_OVERRIDE(Unk_71025b0588, Unk_71025afb58)
public:
    using Data = Unk_71025b0588_Data;
};

// Reference-counted object behind the "RefPosVibrateChecker" / "RefPosVibrateCheckerForAI" AI tree
// variables (BackFlip, JumpMainRigidBody, Sandworm*, LevelFlyMoveBase, MoveMainRigidBody,
// NavMoveTarget, EnemyRangeKeepMove ...). Placeholder name = vtable address (0x71023698d0; D2
// 0x71000b1654 is an empty function shared with other classes, D0 0x71000b1650 a delete thunk, RTTI
// functions 0x71000b14d4 / 0x71000b15f4). Created (inline constructor) by
// Unk_71025afb58Ref<Unk_71023698d0>::acquire (0x71000b0800).
class Unk_71023698d0 : public Unk_71025b0588 {
    SEAD_RTTI_OVERRIDE(Unk_71023698d0, Unk_71025b0588)
public:
    /* 0xb0 */ s32 mRefCount = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71023698d0, 0xb8);
