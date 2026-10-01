#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/Action/actionUnk_7102451ba0.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PreAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PreAttack, ksys::act::ai::Action)
public:
    explicit PreAttack(const InitArg& arg);
    ~PreAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mTurnSpd_s{};
    // static_param at offset 0x28
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    Unk_7102451ba0 _48;
    sead::Matrix33f _70;
};

}  // namespace uking::action
