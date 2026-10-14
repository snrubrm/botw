#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class DemoKokkoAngry : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoKokkoAngry, ksys::act::ai::Action)
public:
    explicit DemoKokkoAngry(const InitArg& arg);
    ~DemoKokkoAngry() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mWaitTime_s{};
    ksys::Timer _28{0, 0, 0};
    int _34 = 0;
};

}  // namespace uking::action
