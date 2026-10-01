#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class GuardianMiniGroggy : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniGroggy, ksys::act::ai::Ai)
public:
    explicit GuardianMiniGroggy(const InitArg& arg);
    ~GuardianMiniGroggy() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mChanceTime_s{};
    // static_param at offset 0x40
    sead::SafeString mRestartASName_s{};
    // static_param at offset 0x50
    sead::SafeString mDefaultASName_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _68{0, 0};
    bool _74{};
    bool _75{};
    int _78 = -1;
};

}  // namespace uking::ai
