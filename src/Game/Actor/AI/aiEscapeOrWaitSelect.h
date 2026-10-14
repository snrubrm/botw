#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

class EscapeOrWaitSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EscapeOrWaitSelect, ksys::act::ai::Ai)
public:
    explicit EscapeOrWaitSelect(const InitArg& arg);
    ~EscapeOrWaitSelect() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // 0x71003c9440 (placeholder name; declared only): finds the position to escape to (writes `out`).
    bool sub_71003C9440(sead::Vector3f* out);

protected:
    // Inline-only in the original (name guesses; see LynelEscapeFromTarget).
    void changeToEscapeMove(const sead::Vector3f& pos) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("逃走", &pack);
    }
    void changeToCannotEscape() {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("待機", &pack);
    }

    // static_param at offset 0x38
    const float* mEscapeRange_s{};
    // static_param at offset 0x40
    const float* mEscapeMoveDistMin_s{};
    // static_param at offset 0x48
    const float* mEscapeMoveDistMax_s{};
    // static_param at offset 0x50
    const float* mCheckBackAngle_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
