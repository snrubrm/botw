#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

class LynelEscapeFromTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelEscapeFromTarget, ksys::act::ai::Ai)
public:
    explicit LynelEscapeFromTarget(const InitArg& arg);
    ~LynelEscapeFromTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x7100490f58 (placeholder name; declared only): finds a position to escape to (writes `out`).
    bool sub_7100490F58(sead::Vector3f* out);

protected:
    // Inline-only in the original (name guesses; evidence: the two branches of enter_ each carry their own
    // InlineParamPack and the pack / string slots sit above the caller's `pos`).
    void changeToEscapeMove(const sead::Vector3f& pos) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("逃走移動", &pack);
    }
    void changeToCannotEscape() {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("逃走不能", &pack);
    }

    // static_param at offset 0x38
    const int* mKeepTime_s{};
    // static_param at offset 0x40
    const float* mSpaceDistMin_s{};
    // static_param at offset 0x48
    const float* mSpaceDist_s{};
    // static_param at offset 0x50
    const float* mMoveDistMin_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    f32 _60{};
    int _64{};
    int _68{};
};

}  // namespace uking::ai
