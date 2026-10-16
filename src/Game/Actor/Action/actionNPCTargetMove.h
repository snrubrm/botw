#pragma once

#include "KingSystem/Utils/Unk_7100e726a8.h"
#include "KingSystem/Utils/Unk_7100e7277c.h"

#include "Game/Actor/Action/actionRandomMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"

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

    // 0x7100204e40 (placeholder name): plays the wait AS that fits the key of ASList slot 59 (Sit / SitOnObject /
    // Crouch / default).
    void sub_7100204E40();
    void sub_7100206280();
    bool sub_71002065FC();
    // 0x7100205ba8 (placeholder name): true once the NPC has been stuck against a wall for WallHitTime seconds.
    bool sub_7100205BA8();
    // 0x7100205ce4 (placeholder name): sets AS parameter 9 to the signed horizontal angle (degrees) between the
    // actor's front and the navmesh character's velocity.
    void sub_7100205CE4();

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
    uking::act::NPC* _90{};
    sead::BitFlag8 _98;
    sead::FixedSafeString<32> _a0;
    u8 _d8[0xe4 - 0xd8]{};
    // Whole enter_ initializes all three fields; the rain helper resets and updates this timer.
    ksys::Timer _e4{};
    // Stuck timer: runs while the NPC barely moves against a wall (sub_7100205BA8).
    ksys::Timer _f0{};
    u8 _fc[0x120 - 0xfc]{};
    f32 _120;
    f32 _124;
    // Same swim helpers and defaults as NpcSwimMove (_a0 / _e0 there).
    Unk_7100e726a8 _128;
    Unk_7100e7277c _168;
};

}  // namespace uking::action
