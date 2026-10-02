#pragma once

#include "Game/AI/Action/actionSwitchStepSliderConstraint.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwitchStepSliderConstraintOnce : public SwitchStepSliderConstraint {
    SEAD_RTTI_OVERRIDE(SwitchStepSliderConstraintOnce, SwitchStepSliderConstraint)
public:
    explicit SwitchStepSliderConstraintOnce(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(f32 value) override;
    void m33(ksys::phys::RigidBody* body, const sead::Vector3f* impulse,
             const sead::Vector3f* pos) override;
    void m34() override;

    // The switch is already linked on (ksys::act::Actor::checkLinkBasicSig); lives in the padding
    // after the base's last member.
    bool _e1 = false;
};

}  // namespace uking::action
