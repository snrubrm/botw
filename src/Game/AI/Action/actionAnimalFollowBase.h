#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class AnimalFollowBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnimalFollowBase, ksys::act::ai::Action)
public:
    explicit AnimalFollowBase(const InitArg& arg);
    ~AnimalFollowBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual float m32();
    // The link of the leader (none by default).
    virtual ksys::act::BaseProcLink* m33();
    // Sets / clears the rideable's flag 21 (set for 0); empty by default.
    virtual void m34(const s32* value) {}

    // static_param at offset 0x20
    const int* mUseGearType_s{};
    // static_param at offset 0x28
    const float* mWaitDistanceToLeader_s{};
    // static_param at offset 0x30
    const float* mGear1DistanceToLeader_s{};
    // static_param at offset 0x38
    const float* mGear2DistanceToLeader_s{};
    // static_param at offset 0x40
    const float* mGear3DistanceToLeader_s{};
    // static_param at offset 0x48
    const float* mDistanceFactorAtGearDown_s{};
    // static_param at offset 0x50
    const float* mWaitDistanceIncreaseDistance_s{};
    // static_param at offset 0x58
    const float* mWaitDistanceIncreasePerFrame_s{};
    // static_param at offset 0x60
    const float* mAutoStopAndTurnDistance_s{};
    // static_param at offset 0x68
    const float* mDesiredDirAngleDeltaSecMax_s{};
    // static_param at offset 0x70
    const float* mNavMeshCharacterRadiusScale_s{};
    // static_param at offset 0x78
    const bool* mCanUseHorseGearInput_s{};
    // static_param at offset 0x80
    const bool* mIsAutoGearDownEnabled_s{};
    // static_param at offset 0x88
    const bool* mIsEndAtAutoStop_s{};
    // static_param at offset 0x90
    const bool* mUseMinRadius_s{};
    // static_param at offset 0x98
    const bool* mIsAvoidNavMeshActor_s{};
    // static_param at offset 0xa0
    const bool* mIsTargetPosEqualToLeaderPos_s{};
    // dynamic_param at offset 0xa8
    sead::Vector3f* mTargetPos_d{};
    s32 _b0 = -1;
    f32 _b4 = 0;
    f32 _b8 = 0;
    bool _bc = false;
};

KSYS_CHECK_SIZE_NX150(AnimalFollowBase, 0xc0);

}  // namespace uking::action
