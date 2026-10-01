#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionHover.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleHover : public Hover {
    SEAD_RTTI_OVERRIDE(BattleHover, Hover)
public:
    explicit BattleHover(const InitArg& arg);
    ~BattleHover() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const float* mRotSpeed_s{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
    sead::Matrix33f _80;
};

}  // namespace uking::action
