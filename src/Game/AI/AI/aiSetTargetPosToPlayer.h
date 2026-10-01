#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SetTargetPosToPlayer : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SetTargetPosToPlayer, ksys::act::ai::Ai)
public:
    explicit SetTargetPosToPlayer(const InitArg& arg);
    ~SetTargetPosToPlayer() override;

    bool isFailed() const override { return getCurrentChild()->isFailed(); }
    bool isFinished() const override { return getCurrentChild()->isFinished(); }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool sub_71005694B4(sead::Vector3f* pos);

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
    ksys::Timer _68;
    int _74 = 0;
};
KSYS_CHECK_SIZE_NX150(SetTargetPosToPlayer, 0x78);

}  // namespace uking::ai
