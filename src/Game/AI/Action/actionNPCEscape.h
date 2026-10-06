#pragma once

#include "Game/AI/Action/actionRandomMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::act {
class NPC;
}

namespace uking::action {

class NPCEscape : public RandomMoveAction {
    SEAD_RTTI_OVERRIDE(NPCEscape, RandomMoveAction)
public:
    explicit NPCEscape(const InitArg& arg);
    ~NPCEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    s32 m32(RandomMovePoints* points) override;

    // static_param at offset 0x38
    const int* mWallHitTime_s{};
    // static_param at offset 0x40
    const int* mStopTime_s{};
    // static_param at offset 0x48
    const float* mMaxDistance_s{};
    // static_param at offset 0x50
    const float* mMinDistance_s{};
    // static_param at offset 0x58
    const float* mAngularRange_s{};
    // static_param at offset 0x60
    const float* mVerticalEscapeSpeed_s{};
    // static_param at offset 0x68
    const bool* mIsTurnToTargetPos_s{};
    // static_param at offset 0x70
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x88
    sead::Vector3f* mTargetVel_d{};
    sead::Vector3f _90 = sead::Vector3f::zero;
    sead::Vector3f _9c = sead::Vector3f::zero;
    uking::act::NPC* _a8 = nullptr;
    void* _b0 = nullptr;
    s32 _b8 = 0;
    // map_unit_param at offset 0xc0
    const float* mTerritoryArea_m{};
};
KSYS_CHECK_SIZE_NX150(NPCEscape, 0xc8);

}  // namespace uking::action
