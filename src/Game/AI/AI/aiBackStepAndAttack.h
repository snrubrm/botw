#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

class BackStepAndAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BackStepAndAttack, ksys::act::ai::Ai)
public:
    explicit BackStepAndAttack(const InitArg& arg);
    ~BackStepAndAttack() override;
    bool isFinished() const override;

    bool isFailed() const override;
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // inline-only in the original; name is a guess. Evidence: enter_ and calc_ each repeat this
    // pack + addVec3 + changeChild sequence three times and the target keeps the Vector3f local
    // above the pack on the stack.
    void changeChildWithTargetPos(const char* name) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild(name, &pack);
    }

    // 0x7100326b38: finds a back step position away from the target (probes three angles with line checks).
    bool sub_7100326B38(sead::Vector3f* out_pos);

    // static_param at offset 0x38
    const int* mBackStepMax_s{};
    // static_param at offset 0x40
    const int* mTurnRepeatMax_s{};
    // static_param at offset 0x48
    const float* mBackStepMinDist_s{};
    // static_param at offset 0x50
    const float* mBackStepDist_s{};
    // static_param at offset 0x58
    const float* mFrontAngle_s{};
    // static_param at offset 0x60
    const float* mNoBackStepRange_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    int _70{};
    int _74{};
};

}  // namespace uking::ai
