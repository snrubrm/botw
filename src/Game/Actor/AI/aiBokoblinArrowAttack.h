#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BokoblinArrowAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BokoblinArrowAttack, ksys::act::ai::Ai)
public:
    explicit BokoblinArrowAttack(const InitArg& arg);

    bool isFinished() const override;

    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

protected:
    // inline-only in the original; name is a guess (enter_ and calc_ (three times) repeat it): 静止 with the target
    // position.
    void changeToStay();
    // 0x7100330328 (placeholder name): whether the ray from the equipped weapon to the target hits the ground.
    bool sub_7100330328();

    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mBackWalkStartDist_s{};
    // static_param at offset 0x48
    const float* mBackWalkEndDist_s{};
    // static_param at offset 0x50
    const float* mCliffCheckDist_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
