#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CapturedActDeadSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CapturedActDeadSelector, ksys::act::ai::Ai)
public:
    explicit CapturedActDeadSelector(const InitArg& arg);
    ~CapturedActDeadSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsPlayerPut_m{};
    // aitree_variable (via RootAi::getAITreeVariable2) at offset 0x40
    bool* mIsDrop_a{};
};

}  // namespace uking::ai
