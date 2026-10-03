#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SystemSetWindAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SystemSetWindAction, ksys::act::ai::Action)
public:
    explicit SystemSetWindAction(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    void* _20{};
    // dynamic_param at offset 0x28
    float* mWindDirX_d{};
    // dynamic_param at offset 0x30
    float* mWindDirY_d{};
    // dynamic_param at offset 0x38
    float* mWindDirZ_d{};
    // dynamic_param at offset 0x40
    float* mWindPower_d{};
    // dynamic_param at offset 0x48
    bool* mIsAutoWind_d{};
};

}  // namespace uking::action
