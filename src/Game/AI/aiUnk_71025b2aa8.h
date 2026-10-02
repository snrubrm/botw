#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/Utils/Types.h"

// Intermediate class (RTTI static 0x71025b2ab8; nothing else is known).
class Unk_71025b2ab8 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b2ab8, Unk_71025afb58)
public:
};

// Placeholder name: the (non-polymorphic) data base class of Unk_71025b2aa8 at +8 (its inline
// constructor runs before the derived vtable store; 0xc..0x10 is left uninitialised).
struct Unk_71025b2aa8Data {
    /* 0x00 */ u32 _0 = 0;
    /* 0x04 */ u8 _4[4];
    /* 0x08 */ u64 _8 = 0;
    /* 0x10 */ s32 _10 = -1;
    /* 0x14 */ bool _14 = false;
};

// Intermediate class between the AI tree variable root class and Unk_71025b2aa8; placeholder name
// from its RTTI typeInfo static (0x71025b2ab8). Evidence: the original's checkDerivedRuntimeTypeInfo
// of Unk_71025b2aa8 (0x7100147774) compares against the statics 0x71025b2aa8, 0x71025b2ab8 and the
// root's 0x71025afb58, and the typeInfo of Unk_71025b2aa8 uses its own RuntimeTypeInfo::Derive
// vtable (0x7102388008, not the root's 0x710235ff20).
class Unk_71025b2ab8 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b2ab8, Unk_71025afb58)
};

// Reference-counted object shared by the SimpleAtvUnit* / GanonBeast* dialog behaviors through the
// "SimpleDialogUnit" AI tree variable. Placeholder name from its RTTI typeInfo static (0x71025b2aa8);
// most members are unknown.
class Unk_71025b2aa8 : public Unk_71025b2ab8, public Unk_71025b2aa8Data {
    SEAD_RTTI_OVERRIDE(Unk_71025b2aa8, Unk_71025b2ab8)
public:
    /* 0x20 */ s32 mRefCount = 0;  // reference count (the behaviors' holders release it)
};
KSYS_CHECK_SIZE_NX150(Unk_71025b2aa8, 0x28);
