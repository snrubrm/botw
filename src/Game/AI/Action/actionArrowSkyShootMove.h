#pragma once
#include "KingSystem/System/Timer.h"

#include "Game/AI/Action/actionArrowShootMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ArrowSkyShootMove : public ArrowShootMove {
    SEAD_RTTI_OVERRIDE(ArrowSkyShootMove, ArrowShootMove)
public:
    explicit ArrowSkyShootMove(const InitArg& arg);
    ~ArrowSkyShootMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    void m33() override;
    bool m34(sead::Vector3f* pos, bool* a, bool* b, sead::Vector3f* vel) override;
    bool m40() override;

    // static_param at offset 0x150
    const int* mInterval_s{};
    // static_param at offset 0x158
    const float* mSkyShootDist_s{};
    // dynamic_param at offset 0x160
    ksys::act::BaseProcLink* mTargetActor_d{};
    // dynamic_param at offset 0x168
    sead::Vector3f* mPosOffset_d{};
    s8 _170 = -1;
    ksys::Timer _174{0, 0};
    sead::Vector3f _180{0, 0, 0};

    // 0x71000a6808: casts a ray from `start` up to `end` against terrain / trees; true (and the hit
    // position in `out_hit`) if it hits. `end` arrives in registers as an HFA.
    bool sub_71000A6808(sead::Vector3f end, sead::Vector3f* out_hit, const sead::Vector3f& start);
};

}  // namespace uking::action
