#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"

// Placeholder name (RTTI typeInfo static 0x71025b27c8; parent Unk_71025afb58): intermediate RTTI class. Its typeInfo's
// vtable `Derive<Unk_71025b27c8>` (0x7102385110) is what Unk_71025b27b8's typeInfo is built from.
class Unk_71025b27c8 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b27c8, Unk_71025afb58)
};

// Placeholder name (RTTI typeInfo static 0x71025b27b8; parent Unk_71025b27c8): the object of the
// "WeakPointCounter" AI tree variable (ForkAITreeValWeakPointTimer sets `_8` to the Timer parameter when it
// is not running and finishes when it has run down). Only the field the users read is declared.
class Unk_71025b27b8 : public Unk_71025b27c8 {
    SEAD_RTTI_OVERRIDE(Unk_71025b27b8, Unk_71025b27c8)
public:
    /* 0x08 */ f32 _8;
};
