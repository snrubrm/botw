#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"

// Placeholder name (RTTI typeInfo static 0x71025b2d88; parent Unk_71025afb58): the object of the "WeakPointActiveFlag" AI
// tree variable of the GanonBeast actions / behaviors (ForkGanonBeastWeakPoint*, GanonBeastASPlayFromActiveWp,
// GanonBeastRoot, BeastGanonWPPrincessShout). Bit n of `mFlags` (+8) is set while weak point n (0 - 17) is active.
// Only the field the users read is declared (the constructor is not known).
class Unk_71025b2d88 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b2d88, Unk_71025afb58)
public:
    /* 0x08 */ u32 mFlags;
};
