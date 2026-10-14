#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SetTargetPosForAngryKokko : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SetTargetPosForAngryKokko, ksys::act::ai::Ai)
public:
    explicit SetTargetPosForAngryKokko(const InitArg& arg);
    ~SetTargetPosForAngryKokko() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool sub_7100568490(sead::Vector3f* pos);

    // static_param at offset 0x38
    const int* mUpdateTargetInterval_s{};
    // static_param at offset 0x40
    const int* mMaxUpdateNum_s{};
    // static_param at offset 0x48
    const float* mAddLength_s{};
    // static_param at offset 0x50
    const float* mHeightOffset_s{};
    // static_param at offset 0x58
    const float* mRandRange_s{};
    // static_param at offset 0x60
    const float* mRandRate_s{};
    // dynamic_param at offset 0x68
    ksys::act::BaseProcLink* mTargetActor_d{};
    ksys::Timer _70;
    int _7c = 0;
};
KSYS_CHECK_SIZE_NX150(SetTargetPosForAngryKokko, 0x80);

}  // namespace uking::ai
