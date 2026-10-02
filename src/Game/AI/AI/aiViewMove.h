#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ViewMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ViewMove, ksys::act::ai::Ai)
public:
    explicit ViewMove(const InitArg& arg);
    ~ViewMove() override;

    bool isFinished() const override;

    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTurnStartAngle_s{};
    // static_param at offset 0x40
    const bool* mCheckOnce_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    f32 _50 = 0;
    f32 _54 = 0;
    u32 _58 = 0;
    bool _5c = false;
};
KSYS_CHECK_SIZE_NX150(ViewMove, 0x60);

}  // namespace uking::ai
