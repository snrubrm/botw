#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class SafeMoveAroundTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SafeMoveAroundTarget, ksys::act::ai::Ai)
public:
    explicit SafeMoveAroundTarget(const InitArg& arg);
    ~SafeMoveAroundTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void sub_71005553EC();
    sead::Vector3f sub_71005556F0();

    // static_param at offset 0x38
    const int* mForceTurnTimeBase_s{};
    // static_param at offset 0x40
    const int* mForceTurnTimeRand_s{};
    // static_param at offset 0x48
    const int* mForceTurnStopTimeBase_s{};
    // static_param at offset 0x50
    const int* mForceTurnStopTimeRand_s{};
    // static_param at offset 0x58
    const int* mUpdateTargetPosTime_s{};
    // static_param at offset 0x60
    const int* mUpdateNumCalc_s{};
    // static_param at offset 0x68
    const float* mStartRange_s{};
    // static_param at offset 0x70
    const float* mEndRange_s{};
    // static_param at offset 0x78
    const float* mChangeRangeRate_s{};
    // static_param at offset 0x80
    const float* mTargetOffsetDegree_s{};
    // static_param at offset 0x88
    const float* mLOSFailOffsetDegree_s{};
    // static_param at offset 0x90
    const float* mMinOffsetLength_s{};
    // dynamic_param at offset 0x98
    sead::Vector3f* mTargetPos_d{};
    u32 _a0 = 0;
    sead::Vector3f _a4;
    ksys::Timer _b0;
    ksys::Timer _bc;
    ksys::Timer _c8;
    ksys::Timer _d4;
};
KSYS_CHECK_SIZE_NX150(SafeMoveAroundTarget, 0xe0);

}  // namespace uking::ai
