#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorsePrevRiddenStatusSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorsePrevRiddenStatusSelector, ksys::act::ai::Ai)
public:
    explicit HorsePrevRiddenStatusSelector(const InitArg& arg);
    ~HorsePrevRiddenStatusSelector() override;
    void calc_() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_710043C1D4(ksys::act::ai::InlineParamPack* params);

protected:
};

}  // namespace uking::ai
