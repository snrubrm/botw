#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantChanceWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ForestGiantChanceWait, ksys::act::ai::Ai)
public:
    explicit ForestGiantChanceWait(const InitArg& arg);
    ~ForestGiantChanceWait() override;
    bool isChangeable() const override;
    void calc_() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // Roll for the "チャンス" state (0x71003d6428); falls through to sub_71003D6534.
    void sub_71003D6428();
    // Turn to the target (0x71003d6534); `a2` keeps the streak counter.
    void sub_71003D6534(bool a2);

protected:
    // inline-only in the original; name is a guess (enter_ and twice in calc_): whether the XZ
    // direction to the target is within TurnStartAngle of the actor's flattened forward direction.
    bool isTargetInFront() const;

    // static_param at offset 0x38
    const int* mChanceRate_s{};
    // static_param at offset 0x40
    const int* mCorrectRate_s{};
    // static_param at offset 0x48
    const float* mTurnStartAngle_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    s32 _58{};
    bool _5c{};
};

}  // namespace uking::ai
