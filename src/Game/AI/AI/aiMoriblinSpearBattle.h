#pragma once

#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class MoriblinSpearBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MoriblinSpearBattle, ksys::act::ai::Ai)
public:
    explicit MoriblinSpearBattle(const InitArg& arg);
    ~MoriblinSpearBattle() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void changeToShortRange();
    void sub_71004AA888();
    void changeToWait();
    // 0x71004aaff0 (placeholder name)
    void changeToForcedSmallAttack();
    // 0x71004ab2f4 (placeholder name)
    void changeToMidRange();

protected:
    // static_param at offset 0x38
    const float* mFarDist_s{};
    // static_param at offset 0x40
    const float* mOutDist_s{};
    // static_param at offset 0x48
    const float* mNearDist_s{};
    // static_param at offset 0x50
    const float* mBaseDist_s{};
    // static_param at offset 0x58
    const int* mWeaponIdx_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x68
    const float* mAttackStartRotate_s{};
    // static_param at offset 0x70
    const float* mForceAttackDist_s{};
    // static_param at offset 0x78
    const float* mAttackIntervalIntensity_s{};
    ksys::Timer _80{0, 0};
    Unk_7102451ba0 _90;
};

}  // namespace uking::ai
