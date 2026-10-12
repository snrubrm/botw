#pragma once

#include "Game/AI/Action/actionGuardianActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianStopWait : public GuardianActionBase {
    SEAD_RTTI_OVERRIDE(GuardianStopWait, GuardianActionBase)
public:
    explicit GuardianStopWait(const InitArg& arg);
    ~GuardianStopWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m0(Data* data, ksys::act::Actor* actor) override;

protected:
    void calc_() override;

    // static_param at offset 0x28
    const float* mSpeed_s{};
    // dynamic_param at offset 0x30
    float* mDynStopTime_d{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mDynStopPos_d{};
};

}  // namespace uking::action
