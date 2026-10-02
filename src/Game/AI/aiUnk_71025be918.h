#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"

// Intermediate class (RTTI static 0x71025be928; nothing else is known).
class Unk_71025be928 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025be928, Unk_71025afb58)
public:
};

// Reference-counted object shared by the Giant* behaviors through the "GiantPartBoneUnit" AI tree
// variable. Placeholder name from its RTTI typeInfo static (0x71025be918); its parent class and most
// members are unknown.
class Unk_71025be918 : public Unk_71025be928 {
    SEAD_RTTI_OVERRIDE(Unk_71025be918, Unk_71025be928)
public:
    u8 _8[0x98 - 0x8];
    /* 0x98 */ s32 _98;  // reference count (the behaviors' destructors release it)
};
