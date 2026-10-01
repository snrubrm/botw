#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FirstSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FirstSelect, ksys::act::ai::Ai)
public:
    explicit FirstSelect(const InitArg& arg);
    ~FirstSelect() override;
    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mResetFromDemo_s{};
    bool _40 = true;
};

}  // namespace uking::ai
