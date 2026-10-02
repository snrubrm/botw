#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TwnObjDlcFlightTrainingTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TwnObjDlcFlightTrainingTarget, ksys::act::ai::Ai)
public:
    explicit TwnObjDlcFlightTrainingTarget(const InitArg& arg);
    ~TwnObjDlcFlightTrainingTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mLimitTime_s{};
    f32 _40 = 0;
    bool _44 = true;
    bool _45 = false;
};
KSYS_CHECK_SIZE_NX150(TwnObjDlcFlightTrainingTarget, 0x48);

}  // namespace uking::ai
