#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRiddenStatusSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseRiddenStatusSelector, ksys::act::ai::Ai)
public:
    explicit HorseRiddenStatusSelector(const InitArg& arg);
    ~HorseRiddenStatusSelector() override;
    void calc_() override;
    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_710043EABC(ksys::act::ai::InlineParamPack* params);

protected:
};

}  // namespace uking::ai
