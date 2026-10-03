#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

// Intermediate class (RTTI static 0x71025b2ab8; nothing else is known).
class Unk_71025b2ab8 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b2ab8, Unk_71025afb58)
public:
};

// Placeholder name: the (non-polymorphic) data base class of Unk_71025b2aa8 at +8 (its inline
// constructor runs before the derived vtable store; 0xc..0x10 is left uninitialised).
struct Unk_71025b2aa8Data {
    // Built by SimpleAtvUnitOpenSimpleDialog (0x7100641eb8) and passed to sub_7100721DE4.
    struct Request {
        /* 0x00 */ const sead::SafeString* _0 = nullptr;  // mstxtName
        /* 0x08 */ const sead::SafeString* _8 = nullptr;  // label
        /* 0x10 */ u32 _10 = 0;                           // CloseOption
        /* 0x14 */ s32 _14 = 0;                           // Type
        /* 0x18 */ s32 _18 = -1;                          // Timer
        /* 0x20 */ ksys::act::Actor* _20 = nullptr;
    };
    KSYS_CHECK_SIZE_NX150(Request, 0x28);

    // 0x7100721de4: opens the dialog (UI::messageDialogViewStyleStuff) unless `_14` is set.
    void sub_7100721DE4(const Request* request);
    // 0x7100721e80: counts `_0` down and closes the dialog when it runs out.
    void sub_7100721E80();
    // 0x7100721efc: closes the dialog if one is open (`_10 != -1`).
    void sub_7100721EFC();
    // 0x7100721f54: same, then sets `_14`.
    void sub_7100721F54();
    // 0x7100721fb4: whether the UI has a message dialog open.
    bool sub_7100721FB4() const;

    /* 0x00 */ f32 _0 = 0;
    /* 0x04 */ u8 _4[4];
    /* 0x08 */ ksys::act::Actor* _8 = nullptr;
    /* 0x10 */ s32 _10 = -1;
    /* 0x14 */ bool _14 = false;
};

// Reference-counted object shared by the SimpleAtvUnit* / GanonBeast* dialog behaviors through the
// "SimpleDialogUnit" AI tree variable. Placeholder name from its RTTI typeInfo static (0x71025b2aa8);
// most members are unknown.
class Unk_71025b2aa8 : public Unk_71025b2ab8, public Unk_71025b2aa8Data {
    SEAD_RTTI_OVERRIDE(Unk_71025b2aa8, Unk_71025b2ab8)
public:
    using Data = Unk_71025b2aa8Data;

    /* 0x20 */ s32 mRefCount = 0;  // reference count (the behaviors' holders release it)
};
KSYS_CHECK_SIZE_NX150(Unk_71025b2aa8, 0x28);
