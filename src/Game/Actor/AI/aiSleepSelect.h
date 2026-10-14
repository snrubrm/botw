#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SleepSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SleepSelect, ksys::act::ai::Ai)
public:
    explicit SleepSelect(const InitArg& arg);
    ~SleepSelect() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
