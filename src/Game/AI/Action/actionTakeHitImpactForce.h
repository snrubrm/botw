#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::dmg {
class DamageManager;
}

namespace uking::action {

class TakeHitImpactForce : public ActionEx {
    SEAD_RTTI_OVERRIDE(TakeHitImpactForce, ActionEx)
public:
    explicit TakeHitImpactForce(const InitArg& arg);
    // The original keeps this destructor out of line next to the subclasses' inlined copies, which a
    // defaulted destructor does not. Written like upstream's GameDataFlagSelector::~GameDataFlagSelector()
    // { ; } (commit 96101229).
    ~TakeHitImpactForce() override { ; }

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;
    virtual void m32(sead::Vector3f* dir, ksys::act::Actor* actor, uking::dmg::DamageManager* mgr);
    virtual bool m33(sead::Vector3f* dir, uking::dmg::DamageManager* mgr);
    virtual void m34() {}
    virtual void m35();
    virtual bool m36() { return true; }
    virtual bool m37() { return isFinishedAS(0, 0); }

    struct Params {
        // static_param at offset 0x20
        const float* mVelReduce_s{};
        // static_param at offset 0x28
        const float* mHighSpeedY_s{};
        // static_param at offset 0x30
        const float* mVelReduceY_s{};
        // static_param at offset 0x38
        const float* mHitImpactForceSmallSwordS_s{};
        // static_param at offset 0x40
        const float* mHitImpactForceSmallSwordL_s{};
        // static_param at offset 0x48
        const float* mHitImpactForceLargeSwordS_s{};
        // static_param at offset 0x50
        const float* mHitImpactForceLargeSwordL_s{};
        // static_param at offset 0x58
        const float* mHitImpactForceSpearS_s{};
        // static_param at offset 0x60
        const float* mHitImpactForceSpearL_s{};
    };
    Params mParams;
    ksys::VFRVec3f _68;
    f32 _8c = 0;
};

KSYS_CHECK_SIZE_NX150(TakeHitImpactForce, 0x90);

}  // namespace uking::action
