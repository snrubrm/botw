#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RandomMoveAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RandomMoveAction, ksys::act::ai::Action)
public:
    explicit RandomMoveAction(const InitArg& arg);
    ~RandomMoveAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsSuccessWhenGoalReached_s{};
    sead::Vector3f _28 = sead::Vector3f::zero;
    f32 _34 = 0;
};

KSYS_CHECK_SIZE_NX150(RandomMoveAction, 0x38);

}  // namespace uking::action
