#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

// Unnamed class of the object shared by the Octarock AI trees and actions (OctarockReloadWig,
// ForkOctarockEnterReloadWig, ...) through the "OctarockFormChangeUnit" AI tree variable. Embedded
// in OctarockRoot (constructed at +0x328 by its ctor); its functions live at
// 0x7100714294-0x7100715234. Placeholder name = vtable address (RTTI static 0x71025b3008).
// Only the members used by its users are declared.
class Unk_7102450d10 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_7102450d10, Unk_71025afb58)
public:
    explicit Unk_7102450d10(ksys::act::Actor* actor);
    ~Unk_7102450d10() override;

    // Re-evaluates the form from the actor's character controller (+0x224) and switches the
    // target bodies' contact layers (calls 0x7100714548 / 0x7100714918).
    void sub_7100714C9C();
    // 0x7100714918 (declared only): called by OctarockRoot::enter_ (the other callee of sub_7100714C9C).
    void sub_7100714918();
    // 0x7100714ed4 (declared only): called by OctarockReaction::sub_71004ED6D4 with `false`; maps the character
    // controller's value at +0x224 to a form index like sub_7100714C9C (switch over `_8` / `_30`).
    void sub_7100714ED4(bool a1);

    // Compared with the character controller's value at +0x224 (index = form).
    /* 0x08 */ sead::SafeArray<int, 10> _8;
    /* 0x30 */ int _30;
    /* 0x38 */ ksys::act::Actor* mActor;
};
KSYS_CHECK_SIZE_NX150(Unk_7102450d10, 0x40);
