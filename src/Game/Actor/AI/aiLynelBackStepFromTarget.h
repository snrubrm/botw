#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

class LynelBackStepFromTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelBackStepFromTarget, ksys::act::ai::Ai)
public:
    explicit LynelBackStepFromTarget(const InitArg& arg);
    ~LynelBackStepFromTarget() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x710048cebc (placeholder name; declared only): finds the position to back step to (writes `out`).
    bool sub_710048CEBC(sead::Vector3f* out);

protected:
    // Inline-only in the original (name guesses; see LynelEscapeFromTarget).
    void changeToEscapeMove(const sead::Vector3f& pos) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("バックステップ", &pack);
    }
    void changeToCannotEscape() {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("後退不能", &pack);
    }

    // static_param at offset 0x38
    const float* mMoveDistMin_s{};
    // static_param at offset 0x40
    const float* mMoveDist_s{};
    // static_param at offset 0x48
    const float* mAddCheckAngle_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
