#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NavMeshTurnAwayFromHitPos : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NavMeshTurnAwayFromHitPos, ksys::act::ai::Ai)
public:
    explicit NavMeshTurnAwayFromHitPos(const InitArg& arg);
    ~NavMeshTurnAwayFromHitPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void sub_71004B56B4();

protected:
    // static_param at offset 0x38
    const int* mNumLOSCheckMax_s{};
    // static_param at offset 0x40
    const float* mLOSCheckLength_s{};
    // static_param at offset 0x48
    const bool* mMoveToSafePosAfterTurn_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mHitPos_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    sead::Vector3f _60{0, 0, 0};
};
KSYS_CHECK_SIZE_NX150(NavMeshTurnAwayFromHitPos, 0x70);

}  // namespace uking::ai
