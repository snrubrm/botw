#pragma once

#include "KingSystem/System/VFRValue.h"
#include "Game/AI/Action/actionFreeMoveToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FreeMoveToNearGround : public FreeMoveToTarget {
    SEAD_RTTI_OVERRIDE(FreeMoveToNearGround, FreeMoveToTarget)
public:
    explicit FreeMoveToNearGround(const InitArg& arg);
    ~FreeMoveToNearGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32(ksys::phys::CharacterController* controller) override;
    f32 m36() override;
    void m37(f32 speed, ksys::phys::CharacterController* controller) override;

    // static_param at offset 0xd0
    const float* mReduceSpeedRateWithWind_s{};
    // static_param at offset 0xd8
    const float* mWindVelocityLimit4Reduce_s{};
    ksys::Timer _e0;
    ksys::VFRValue _ec;
    f32 _f8 = 0;
};

}  // namespace uking::action
