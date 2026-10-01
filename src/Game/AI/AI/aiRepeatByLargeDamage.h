#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RepeatByLargeDamage : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RepeatByLargeDamage, ksys::act::ai::Ai)
public:
    explicit RepeatByLargeDamage(const InitArg& arg);
    ~RepeatByLargeDamage() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool _38{};
};

}  // namespace uking::ai
