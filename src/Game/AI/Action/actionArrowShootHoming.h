#pragma once

#include "Game/AI/Action/actionArrowShootMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ArrowShootHoming : public ArrowShootMove {
    SEAD_RTTI_OVERRIDE(ArrowShootHoming, ArrowShootMove)
public:
    explicit ArrowShootHoming(const InitArg& arg);
    ~ArrowShootHoming() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x150
    const float* mSubAngMax_s{};
    // static_param at offset 0x158
    const float* mHomingRate_s{};
    // static_param at offset 0x160
    const float* mNearDist_s{};
    // dynamic_param at offset 0x168
    ksys::act::BaseProcLink* mTargetActor_d{};
    // dynamic_param at offset 0x170
    sead::Vector3f* mHomingTargetPos_d{};
    f32 _178 = 0.0f;
    f32 _17c = 0.0f;
    f32 _180 = 0.0f;
    u8 _184[0x30]{};
    s32 _1b4 = 0;
};
KSYS_CHECK_SIZE_NX150(ArrowShootHoming, 0x1b8);

}  // namespace uking::action
