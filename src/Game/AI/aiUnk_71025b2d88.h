#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"

// Placeholder name (RTTI typeInfo static 0x71025b2d98; parent Unk_71025afb58): intermediate RTTI class. Its typeInfo's
// vtable `Derive<Unk_71025b2d98>` (0x710238af18) is what Unk_71025b2d88's typeInfo is built from.
class Unk_71025b2d98 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b2d98, Unk_71025afb58)
};

// Placeholder name (RTTI typeInfo static 0x71025b2d88; parent Unk_71025b2d98): the object of the "WeakPointActiveFlag" AI
// tree variable of the GanonBeast actions / behaviors (ForkGanonBeastWeakPoint*, GanonBeastASPlayFromActiveWp,
// GanonBeastRoot, BeastGanonWPPrincessShout). Bit n of `mFlags` (+8) is set while weak point n (0 - 17) is active.
// Only the field the users read is declared (the constructor is not known).
class Unk_71025b2d88 : public Unk_71025b2d98 {
    SEAD_RTTI_OVERRIDE(Unk_71025b2d88, Unk_71025b2d98)
public:
    ~Unk_71025b2d88() override;  // out of line (lane4 s47): the key function that emits the vtable 0x710238b0e8

    /* 0x08 */ u32 mFlags;
};
