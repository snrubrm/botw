#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class MoveAroundTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MoveAroundTarget, ksys::act::ai::Ai)
public:
    explicit MoveAroundTarget(const InitArg& arg);
    ~MoveAroundTarget() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void sub_71004B004C();
    sead::Vector3f sub_71004B0238();
protected:
    // static_param at offset 0x38
    const int* mTurnTimeBase_s{};
    // static_param at offset 0x40
    const int* mTurnTimeRand_s{};
    // static_param at offset 0x48
    const float* mStartRange_s{};
    // static_param at offset 0x50
    const float* mEndRange_s{};
    // static_param at offset 0x58
    const float* mChangeRangeRate_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _68;
    sead::Vector3f _74;
    ksys::Timer _80;
    f32 _8c{};
    s32 _90{};
    s32 _94{};
};

}  // namespace uking::ai
