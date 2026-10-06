#pragma once

#include <math/seadMatrix.h>
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

    // 0x71000a21e8: whether the bullet's owner is a moving player (called by m39).
    bool sub_71000A21E8();

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
    // Value-initialised: the original constructor zeroes 0x150..0x1b8 with a single memset, including
    // the matrix (see TIPS "P p = P()").
    struct Tail {
        f32 _178;
        f32 _17c;
        f32 _180;
        sead::Matrix34f _184;
        s32 _1b4;
    };
    Tail mTail = Tail();
};
KSYS_CHECK_SIZE_NX150(ArrowShootHoming, 0x1b8);

}  // namespace uking::action
