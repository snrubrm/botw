#pragma once

#include "Game/AI/Action/actionRandomMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::act {
class NPC;
}

namespace uking::action {

class NPCTargetMove : public RandomMoveAction {
    SEAD_RTTI_OVERRIDE(NPCTargetMove, RandomMoveAction)
public:
    explicit NPCTargetMove(const InitArg& arg);
    ~NPCTargetMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    s32 m32(RandomMovePoints* points) override;
    virtual void m34();
    virtual sead::SafeString m35();

    // static_param at offset 0x38
    const int* mUpdateTargetPosInterval_s{};
    // static_param at offset 0x40
    const int* mWallHitTime_s{};
    // static_param at offset 0x48
    const int* mStopTime_s{};
    // static_param at offset 0x50
    const float* mGoalDistance_s{};
    // static_param at offset 0x58
    const float* mRunGoalDistance_s{};
    // static_param at offset 0x60
    const float* mDistOnFailure_s{};
    // static_param at offset 0x68
    const bool* mIsPathOptimization_s{};
    // static_param at offset 0x70
    const bool* mIsShelterFromRain_s{};
    // static_param at offset 0x78
    sead::SafeString mASKeyName_s{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mTargetPos_d{};
    // 0x98-0x178: state (not yet decompiled; enter_/calc_ use it)
    uking::act::NPC* _90;
    sead::BitFlag8 _98;
    u8 _99[0xdf];
};

}  // namespace uking::action
