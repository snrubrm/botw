#pragma once

#include <basis/seadTypes.h>
#include <gsys/gsysModelAccessKey.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

// Intermediate class (RTTI static 0x71025be928; nothing else is known).
class Unk_71025be928 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025be928, Unk_71025afb58)
public:
};

// Placeholder name: the (non-polymorphic) data base class of Unk_71025be918 at +8 (its inline constructor is in
// 0x7100625508). It switches the partial bones of an actor's AS slots on and off: the "main" part (`_8`: a bone
// name with the AS slot `_18`) and two parts of three bone names each (`mA` / `mB` with the slots `_50` /
// `_88`): GiantWeaponGrabAS sets them (the right / left hand), the guard state machine Unk_710001bf60 owns the
// main part. Methods 0x7100707a88 - 0x7100708308 (placeholder names).
struct Unk_71025be918Data {
    explicit Unk_71025be918Data(ksys::act::Actor* actor) : mActor(actor) {}

    // 0x7100707a88: sets the main part.
    void sub_7100707A88(s32 slot, const sead::SafeString& bone);
    // 0x7100707a9c / 0x7100707af4: set the parts A / B (`bones` points to three strings).
    void sub_7100707A9C(s32 slot, const sead::SafeString* bones);
    void sub_7100707AF4(s32 slot, const sead::SafeString* bones);
    // 0x7100707b4c: activates the parts A and B (B only if `use_b`) unless already so.
    void sub_7100707B4C(bool use_b);
    // 0x7100707ba4: applies the active parts A / B to the AS slots (partial bones on).
    void sub_7100707BA4();
    // 0x7100707e84: the common tail (re-applies the bones of the slot 0).
    void sub_7100707E84();
    // 0x7100707ff0: deactivates the parts A and B, then 0x7100707e84.
    void sub_7100707FF0();
    // 0x71007080e0: activates the part B, 0x7100707ba4, then 0x7100707e84.
    void sub_71007080E0();
    // 0x7100708124: deactivates the part B, then 0x7100707e84.
    void sub_7100708124();
    // 0x71007081b8: activates the main part, then 0x7100708214 (and 0x7100707ba4 if A and B are active).
    void sub_71007081B8();
    // 0x7100708214: applies the main part.
    void sub_7100708214();
    // 0x7100708308: deactivates the main part.
    void sub_7100708308();

    /* 0x00 */ ksys::act::Actor* mActor;
    /* 0x08 */ sead::SafeString _8;
    /* 0x18 */ s32 _18 = 0;
    /* 0x1c */ bool _1c = false;
    /* 0x20 */ sead::SafeString mA[3];
    /* 0x50 */ s32 _50 = 0;
    /* 0x54 */ bool _54 = false;
    /* 0x58 */ sead::SafeString mB[3];
    /* 0x88 */ s32 _88 = 0;
    /* 0x8c */ bool _8c = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71025be918Data, 0x90);

// Reference-counted object shared by the Giant* behaviors through the "GiantPartBoneUnit" AI tree
// variable. Placeholder name from its RTTI typeInfo static (0x71025be918).
class Unk_71025be918 : public Unk_71025be928, public Unk_71025be918Data {
    SEAD_RTTI_OVERRIDE(Unk_71025be918, Unk_71025be928)
public:
    explicit Unk_71025be918(ksys::act::Actor* actor) : Unk_71025be918Data(actor) {}

    /* 0x98 */ s32 mRefCount = 0;  // reference count (the behaviors' holders release it)
};
KSYS_CHECK_SIZE_NX150(Unk_71025be918, 0xa0);
