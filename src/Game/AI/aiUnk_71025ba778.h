#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"

// Object shared by the Lynel body behaviors through the "LynelBodyControlUnit" AI tree variable.
// Placeholder name from its RTTI typeInfo static (0x71025ba778; parent: Unk_71025afb58); size and most
// members are unknown.
class Unk_71025ba778 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025ba778, Unk_71025afb58)
public:
    /* 0x08 */ u8 _8[0xc - 0x8];
    /* 0x0c */ f32 _c;  // set to 1 / 0 by LynelStandBody::m8 / m9
};
