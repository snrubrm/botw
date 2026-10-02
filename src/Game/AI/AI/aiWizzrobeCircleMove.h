#pragma once

#include "KingSystem/System/Timer.h"

#include "Game/AI/AI/aiCircleMoveTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WizzrobeCircleMove : public CircleMoveTarget {
    SEAD_RTTI_OVERRIDE(WizzrobeCircleMove, CircleMoveTarget)
public:
    explicit WizzrobeCircleMove(const InitArg& arg);
    ~WizzrobeCircleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void m35(const sead::Vector3f& target_pos) override;
    void m36(const sead::Vector3f& target_pos) override;
    f32 m37() override;

protected:
    // static_param at offset 0x68
    const float* mFinRadius_s{};
    // static_param at offset 0x70
    const float* mRadiusTimer_s{};
    // static_param at offset 0x78
    const float* mEndTimer_s{};
    // static_param at offset 0x80
    const bool* mIsAttCentral_s{};
    bool _88 = false;
    ksys::Timer _8c;
};
KSYS_CHECK_SIZE_NX150(WizzrobeCircleMove, 0x98);

}  // namespace uking::ai
