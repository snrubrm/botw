#pragma once

#include <xlink2/xlink2HandleELink.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossDie : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossDie, ksys::act::ai::Action)
public:
    explicit SiteBossDie(const InitArg& arg);
    ~SiteBossDie() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    bool isFinished() const override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    // static_param at offset 0x20
    const float* mWarpWaitTime_s{};
    // static_param at offset 0x28
    const bool* mIsUseYAxisSignal_s{};
    xlink2::HandleELink _30;
    int _40 = 0;
    int _44 = 0;
    int _48 = 0;
};

}  // namespace uking::action
