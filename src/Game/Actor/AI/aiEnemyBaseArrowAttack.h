#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyBaseArrowAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyBaseArrowAttack, ksys::act::ai::Ai)
public:
    explicit EnemyBaseArrowAttack(const InitArg& arg);

    bool isFinished() const override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void loadParams_() override;

    void changeToPrepare();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mIntervalIntensity_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
