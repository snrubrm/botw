#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class DefWanderAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DefWanderAI, ksys::act::ai::Ai)
public:
    explicit DefWanderAI(const InitArg& arg);
    ~DefWanderAI() override;
    bool isChangeable() const override;
    bool isFinished() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mFinishChangeCount_s{};
    // static_param at offset 0x40
    const float* mChangeWaitRate_s{};
    // static_param at offset 0x48
    const float* mMaxWaitTime_s{};
    // static_param at offset 0x50
    const float* mMinWaitTime_s{};
    // static_param at offset 0x58
    const bool* mCheckWaitIsChangable_s{};
    sead::Vector3f _60;
    ksys::Timer _6c;
    int _78{};
};

}  // namespace uking::ai
