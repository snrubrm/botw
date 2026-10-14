#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShockWave : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ShockWave, ksys::act::ai::Action)
public:
    explicit ShockWave(const InitArg& arg);
    ~ShockWave() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // 0x710024e1c8 (placeholder name): deletes the actor, or puts it to sleep for reuse when the creator
    // (bullet holder / create-arg parent) is still alive.
    void sub_710024E1C8();

    // map_unit_param at offset 0x20
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x28
    const int* mAttackAttr_m{};
    // map_unit_param at offset 0x30
    const int* mAtMinDamage_m{};
    // map_unit_param at offset 0x38
    const float* mScaleTime_m{};
    // map_unit_param at offset 0x40
    const bool* mIsReuseActor_m{};
    float _48 = 0.0f;
    float _4c = 1.0f;
};

}  // namespace uking::action
