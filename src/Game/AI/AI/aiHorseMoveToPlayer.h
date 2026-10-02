#pragma once

#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "Game/AI/AI/aiHorseFollow.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseMoveToPlayer : public HorseFollow {
    SEAD_RTTI_OVERRIDE(HorseMoveToPlayer, HorseFollow)
public:
    SEAD_ENUM(Flag, _0, _1, _2, _3)

    explicit HorseMoveToPlayer(const InitArg& arg);
    ~HorseMoveToPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m34(sead::Vector3f* out, const sead::Vector3f& pos, const sead::Vector3f& target_pos,
             const sead::Vector3f& target_velocity, const sead::Vector3f& up) override;
    // NON_MATCHING: operand order of the `and` (the original tests `bits & mask`)
    bool m36() override { return _f0.isOffBit(Flag(Flag::_1)); }
    // NON_MATCHING: operand order of the `and` (the original tests `bits & mask`)
    bool m37() override { return _f0.isOffBit(Flag(Flag::_1)); }

protected:
    // static_param at offset 0xe0
    const float* mDistanceSuccessEndIfInterrupted_s{};
    // static_param at offset 0xe8
    const float* mDistanceResetGearInput_s{};
    sead::BitFlag8 _f0;
};
KSYS_CHECK_SIZE_NX150(HorseMoveToPlayer, 0xf8);

}  // namespace uking::ai
