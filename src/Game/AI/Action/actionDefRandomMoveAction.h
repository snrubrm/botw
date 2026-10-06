#pragma once

#include "Game/AI/Action/actionRandomMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DefRandomMoveAction : public RandomMoveAction {
    SEAD_RTTI_OVERRIDE(DefRandomMoveAction, RandomMoveAction)
public:
    explicit DefRandomMoveAction(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    s32 m32(RandomMovePoints* points) override;
    void m33(void* a, ksys::phys::NavMeshCharacter* nav) override;

    // static_param at offset 0x38
    const float* mRadiusLimit_s{};
    // static_param at offset 0x40
    const float* mMaxMoveSpeed_s{};
    // static_param at offset 0x48
    const float* mMinMoveSpeed_s{};
    // static_param at offset 0x50
    const float* mMaxMoveDistance_s{};
    // static_param at offset 0x58
    const float* mMinMoveDistance_s{};
    // static_param at offset 0x60
    const float* mMaxMoveAngle_s{};
    // static_param at offset 0x68
    const bool* mIsUseBasepos_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mBasePos_d{};
    sead::Vector3f _78 = sead::Vector3f::zero;
    f32 _84 = 0;
    f32 _88 = 0;
    sead::Vector3f _8c = sead::Vector3f::zero;
    sead::Vector3f _98 = sead::Vector3f::zero;
    sead::Vector3f _a4 = sead::Vector3f::zero;
};

}  // namespace uking::action
