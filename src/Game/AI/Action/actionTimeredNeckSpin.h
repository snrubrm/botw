#pragma once

#include "KingSystem/System/VFRValue.h"
#include "Game/AI/Action/actionNeckSpin.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TimeredNeckSpin : public NeckSpin {
    SEAD_RTTI_OVERRIDE(TimeredNeckSpin, NeckSpin)
public:
    explicit TimeredNeckSpin(const InitArg& arg);
    ~TimeredNeckSpin() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    struct Params {
        // static_param at offset 0x68
        const int* mTime_s{};
        // static_param at offset 0x70
        const float* mSpinSpeedRatio_s{};
        // static_param at offset 0x78
        const float* mInitSpinSpeed_s{};
    };
    Params mParams;
    ksys::VFRValue _80;
    f32 _8c = 0.0f;
    f32 _90 = 0.0f;
    f32 _94 = 0.0f;
};
KSYS_CHECK_SIZE_NX150(TimeredNeckSpin, 0x98);

}  // namespace uking::action
