#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsFireBattleStepSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsFireBattleStepSelector, ksys::act::ai::Ai)
public:
    explicit RemainsFireBattleStepSelector(const InitArg& arg);
    ~RemainsFireBattleStepSelector() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    int _38 = 0;
    int _3c = 0;
};
KSYS_CHECK_SIZE_NX150(RemainsFireBattleStepSelector, 0x40);

}  // namespace uking::ai
