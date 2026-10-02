#pragma once

#include "Game/AI/Action/actionForkNoWeaponAttackAllTime.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkChemicalChuchuAttack : public ForkNoWeaponAttackAllTime {
    SEAD_RTTI_OVERRIDE(ForkChemicalChuchuAttack, ForkNoWeaponAttackAllTime)
public:
    explicit ForkChemicalChuchuAttack(const InitArg& arg);
    ~ForkChemicalChuchuAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const int* mLandAtkTime_s{};
    // static_param at offset 0xc8
    const float* mLandAtkRadius_s{};
    void* _d0{};
    f32 _d8 = 0.0f;
    f32 _dc = 1.0f;
    int _e0 = 0;
    void* _e8{};
    int _f0 = 0;
    void* _f8{};
    int _100 = 0;
};

}  // namespace uking::action
