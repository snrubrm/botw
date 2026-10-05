#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyEscapeMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyEscapeMove, ksys::act::ai::Ai)
public:
    explicit EnemyEscapeMove(const InitArg& arg);
    ~EnemyEscapeMove() override;
    bool isChangeable() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x40
    const f32* mBehindCheckDist_s{};
    // The remaining native tail is not modeled.
};

}  // namespace uking::ai
