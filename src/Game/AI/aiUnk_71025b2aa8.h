#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"

// Intermediate class (RTTI static 0x71025b2ab8; nothing else is known).
class Unk_71025b2ab8 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b2ab8, Unk_71025afb58)
public:
};

// Reference-counted object shared by the SimpleAtvUnit* / GanonBeast* dialog behaviors through the
// "SimpleDialogUnit" AI tree variable. Placeholder name from its RTTI typeInfo static (0x71025b2aa8);
// its parent class and most members are unknown.
class Unk_71025b2aa8 : public Unk_71025b2ab8 {
    SEAD_RTTI_OVERRIDE(Unk_71025b2aa8, Unk_71025b2ab8)
public:
    u8 _8[0x20 - 0x8];
    /* 0x20 */ s32 _20;  // reference count (the behaviors' destructors release it)
};
