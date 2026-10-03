#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71000b0800.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace sead {
class Heap;
}

// Unnamed classes of the reference-counted object shared by the Freeze / Ragdoll / GetUp / ForkRagdollOff /
// ForkAlwaysForceGetUp / ForkASTrgTurnGround ... actions through the "CRBOffsetUnit" AI tree
// variable. Placeholder names: Unk_7102384718 = vtable address; its parent Unk_71025b2718 is named from its RTTI
// typeInfo static like the other intermediates (its own vtable is 0x7102384748). Their virtual functions live at 0x137e88-0x1381c0.
// The bone handle with its counters embedded at +8: the original addresses the attach count relative to
// the handle (the ctor is inlined into 0x7100137a28 and stores `_a8` before the counters). Not a
// subclass of BoneHandle (the fields sit after BoneHandle's tail padding). Placeholder name.
class Unk_7102384718Handle {
public:
    // Inline only (init_ of the users): sets the root bone offset up the first time (name `Skl_Root`,
    // identity transform). Placeholder name.
    void sub_setup() {
        if (!_a8.isOn(1)) {
            mHandle.setName("Skl_Root");
            mHandle._68 = sead::Matrix34f::ident;
            mAttachCount = 0;
            _a8.set(1);
        }
    }

    // Inline only (enter_ / leave_ of the users); names are guesses. The actor is an argument of the
    // inlined function (the original loads it before the count update in the detach case).
    void sub_attach(ksys::act::Actor* actor) {
        if (mAttachCount <= 0)
            actor->boneHandleStuff(&mHandle, false);
        ++mAttachCount;
    }
    void sub_detach(ksys::act::Actor* actor) {
        if (--mAttachCount <= 0)
            actor->sub_71011DA868(&mHandle);
    }

    /* 0x00 */ ksys::act::BoneHandle mHandle;
    /* 0xa8 */ sead::BitFlag8 _a8;
    /* 0xac */ s32 mAttachCount = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102384718Handle, 0xb0);

// Intermediate class between the AI tree variable root class and Unk_7102384718; placeholder name
// from its RTTI typeInfo static (0x71025b2718). Unlike the other intermediates it has its own vtable
// (0x7102384748; D2 0x7100138170 is shared with Unk_7102384718, D0 0x71001381c0). Evidence: the
// original's checkDerivedRuntimeTypeInfo of Unk_7102384718 (0x7100137e88) compares against the
// statics 0x71025b2708, 0x71025b2718 and the root's 0x71025afb58, and the typeInfo of
// Unk_7102384718 has its own RuntimeTypeInfo::Derive vtable (0x7102384700).
class Unk_71025b2718 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b2718, Unk_71025afb58)
public:
    ~Unk_71025b2718() override = default;

    /* 0x08 */ Unk_7102384718Handle _8;
};

// Reference-counted object behind the "CRBOffsetUnit" AI tree variable (all ActionWithPosAngReduce
// subclasses: Freeze, Ragdoll, GetUpBase, ForkRagdollOff, ...). Placeholder name = vtable address
// (0x7102384718; D0 0x7100138004, RTTI functions 0x7100137e88 / 0x7100137fa8); created inline by
// Unk_71000b0800<Unk_7102384718>::acquire (0x7100137a28 is its out-of-line copy).
class Unk_7102384718 : public Unk_71025b2718 {
    SEAD_RTTI_OVERRIDE(Unk_7102384718, Unk_71025b2718)
public:
    /* 0xb8 */ s32 mRefCount = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_7102384718, 0xc0);

// Inline only (init_ of the users): sets the root bone offset up the first time. Placeholder name.
inline void setupCRBOffsetUnit(const Unk_71000b0800<Unk_7102384718>& ref) {
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*ref._0))
        unit->_8.sub_setup();
}
