#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

class StalEnemyDie : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StalEnemyDie, ksys::act::ai::Action)
public:
    explicit StalEnemyDie(const InitArg& arg);
    ~StalEnemyDie() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTime_s{};
    // static_param at offset 0x28
    const float* mAngReduceRatio_s{};
    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    const bool* mForceDropWeapon_s{};
    // static_param at offset 0x40
    sead::SafeString mPreDieASName_s{};
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
    // static_param at offset 0x60
    sead::SafeString mPosBaseRagdollName_s{};
    // static_param at offset 0x70
    sead::SafeString mEnableConstraintName_s{};
    bool _80 = false;
    ksys::Timer _84;
    bool _90 = false;
};
KSYS_CHECK_SIZE_NX150(StalEnemyDie, 0x98);

}  // namespace uking::action
