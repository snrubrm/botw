#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionUnk_71025afc58.h"

namespace ksys::act {
class Actor;
}

// Turn helper (vtable 0x71023c8568, ctor 0x71002a6b28): turns the owner's actor towards the target
// returned by m13, either by setting an angular velocity (IsJumpType) or by interpolating its
// matrix every frame (m16). Only instantiated through its subclass Unk_71023c84b8.
class Unk_71023c8568 : public Unk_71025afc58 {
    SEAD_RTTI_OVERRIDE(Unk_71023c8568, Unk_71025afc58)
public:
    explicit Unk_71023c8568(ksys::act::ai::ActionBase* owner);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override {}
    void loadParams_() override;
    virtual void m13(sead::Vector3f* target) {}
    virtual void m14();
    virtual void m15(ksys::act::Actor* actor, f32 time);
    virtual void m16();

    const float* mAngSpd_s{};
    const bool* mIsJumpType_s{};
    sead::SafeString _28;
    sead::Vector3f _38 = sead::Vector3f::ey;
    f32 _44 = 0.0f;
    f32 _48 = 0.0f;
    f32 _4c = 0.0f;
    f32 _50 = 0.0f;
    f32 _54 = 0.0f;
    bool _58 = false;
};
