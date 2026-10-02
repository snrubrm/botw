#pragma once

#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include "Game/AI/Action/actionUnk_71023c8678.h"

// Subclass of the follow/ignite helper Unk_71023c8678 (vtable 0x7102360d20, ctor 0x710006ab54)
// embedded in FollowIgniteToBonePos: m13() returns the position given by the owner's delegate
// (bound in the owner's init_) and falls back to the owner actor's translation while no delegate
// is bound.
class Unk_7102360d20 : public Unk_71023c8678 {
    SEAD_RTTI_OVERRIDE(Unk_7102360d20, Unk_71023c8678)
public:
    explicit Unk_7102360d20(ksys::act::ai::ActionBase* owner);
    ~Unk_7102360d20() override;

    void m13(sead::Vector3f* pos) override;

    sead::AnyDelegateR<sead::Vector3f> _38;
};
KSYS_CHECK_SIZE_NX150(Unk_7102360d20, 0x58);
