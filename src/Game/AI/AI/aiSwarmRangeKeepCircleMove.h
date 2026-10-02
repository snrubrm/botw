#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwarmRangeKeepCircleMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwarmRangeKeepCircleMove, ksys::act::ai::Ai)
public:
    explicit SwarmRangeKeepCircleMove(const InitArg& arg);
    ~SwarmRangeKeepCircleMove() override;

    bool isFailed() const override;
    bool isFinished() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_71005B205C();

protected:
    // static_param at offset 0x38
    const float* mBaseDist_s{};
    // static_param at offset 0x40
    const float* mOutDist_s{};
    // static_param at offset 0x48
    const float* mSpeed_s{};
    // static_param at offset 0x50
    const float* mUpdateCircleMoveDistance_s{};
    f32 _58 = 0;
    s32 _5c = 1;
    sead::Vector3f _60;
};
KSYS_CHECK_SIZE_NX150(SwarmRangeKeepCircleMove, 0x70);

}  // namespace uking::ai
