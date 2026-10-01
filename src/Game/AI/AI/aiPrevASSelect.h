#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PrevASSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PrevASSelect, ksys::act::ai::Ai)
public:
    explicit PrevASSelect(const InitArg& arg);
    ~PrevASSelect() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
};

}  // namespace uking::ai
