#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

class EnemyNotice : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNotice, ksys::act::ai::Ai)
public:
    explicit EnemyNotice(const InitArg& arg);
    void calc_() override;
    bool isFinished() const override;
    bool isFailed() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // Inline-only in the original (name guess; evidence: the param pack sits above calc_'s `pos` on the stack).
    void changeToChase() {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("追跡", &pack);
    }

    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x40
    const float* mTurnStartAngle_s{};
};

}  // namespace uking::ai
