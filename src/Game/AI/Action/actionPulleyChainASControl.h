#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace uking::action {

class PulleyChainASControl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PulleyChainASControl, ksys::act::ai::Action)
public:
    explicit PulleyChainASControl(const InitArg& arg);
    ~PulleyChainASControl() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    void sub_7100223114();

    // static_param at offset 0x20
    const int* mTargetIdx_s{};
    // static_param at offset 0x28
    const int* mSeqBankIdx_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // 223060 zeros both vectors; 223114 transforms two pulley heights by the home matrix.
    sead::Vector3f mStartPosition{0.0f, 0.0f, 0.0f};
    sead::Vector3f mEndPosition{0.0f, 0.0f, 0.0f};
};

}  // namespace uking::action
