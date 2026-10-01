#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IchigekiHeartDecrease : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(IchigekiHeartDecrease, ksys::act::ai::Action)
public:
    explicit IchigekiHeartDecrease(const InitArg& arg);
    ~IchigekiHeartDecrease() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mUseFrame_d{};
    // dynamic_param at offset 0x28
    int* mIsUseConstSpeed_d{};
    float _30 = 0.0f;
    int _34 = 0;
    int _38 = 0;
};

}  // namespace uking::action
