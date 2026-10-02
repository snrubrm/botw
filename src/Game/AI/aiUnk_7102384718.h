#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/Utils/Types.h"

// Intermediate class between the AI tree variable root class and Unk_7102384718; placeholder name
// from its RTTI typeInfo static (0x71025b2718). Unlike the other intermediates it has its own vtable
// (0x7102384748; D2 0x7100138170 is shared with Unk_7102384718, D0 0x71001381c0) and constructs a
// BoneHandle (0x7100d3b3f0). Evidence: the original's checkDerivedRuntimeTypeInfo of
// Unk_7102384718 (0x7100137e88) compares against the statics 0x71025b2708, 0x71025b2718 and the
// root's 0x71025afb58, and the typeInfo of Unk_7102384718 has its own RuntimeTypeInfo::Derive
// vtable (0x7102384700).
class Unk_71025b2718 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b2718, Unk_71025afb58)
public:
    /* 0x08 */ ksys::act::BoneHandle _8;
    /* 0xb0 */ bool _b0 = false;
    /* 0xb4 */ u32 _b4 = 0;
};

// Reference-counted object behind the "CRBOffsetUnit" AI tree variable (all ActionWithPosAngReduce
// subclasses: Freeze, Ragdoll, GetUpBase, ForkRagdollOff, ...). Placeholder name = vtable address
// (0x7102384718; D0 0x7100138004, RTTI functions 0x7100137e88 / 0x7100137fa8); created inline by
// Unk_71025afb58Ref<Unk_7102384718>::acquire (0x7100137a28 is its out-of-line copy).
class Unk_7102384718 : public Unk_71025b2718 {
    SEAD_RTTI_OVERRIDE(Unk_7102384718, Unk_71025b2718)
public:
    /* 0xb8 */ s32 mRefCount = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102384718, 0xc0);
