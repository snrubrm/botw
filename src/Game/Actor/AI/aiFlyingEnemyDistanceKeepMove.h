#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FlyingEnemyDistanceKeepMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FlyingEnemyDistanceKeepMove, ksys::act::ai::Ai)
public:
    explicit FlyingEnemyDistanceKeepMove(const InitArg& arg);
    ~FlyingEnemyDistanceKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    virtual void m34(sead::Vector3f* out) = 0;
    virtual void m35(sead::Vector3f* out, const sead::Vector3f& dir);
    virtual void m36(sead::Vector3f* out);
    // 0x71003d2500 (placeholder name)
    bool sub_71003D2500();
    // 0x71003d25f8 (placeholder name)
    bool sub_71003D25F8();
    // 0x71003d26f0 (placeholder name): moves BaseDist away from the position of m36 on the ground plane.
    void changeToAdjustPosition();

    bool sub_71003D1F88();
    // 0x71003d1c48 (placeholder name): keeps the actor between NearDist / FarDist and the height band around the
    // target (移動 / 位置調整 / height adjust); false when nothing changed.
    bool sub_71003D1C48();
    // 0x71003d20b0 (placeholder name): the 位置調整 target position.
    bool sub_71003D20B0(sead::Vector3f* out);
    // 0x71003d2880 (placeholder name): the mean direction away from the (up to 10) awareness entries within `range`,
    // scaled by range / count; false without awareness
    bool sub_71003D2880(f32 range, sead::Vector3f* out);

protected:
    struct Params {
        // static_param at offset 0x38
        const float* mLostDistance_s{};
        // static_param at offset 0x40
        const float* mAngleRange_s{};
        // static_param at offset 0x48
        const float* mSpaceDistance_s{};
        // static_param at offset 0x50
        const float* mNearDist_s{};
        // static_param at offset 0x58
        const float* mFarDist_s{};
        // static_param at offset 0x60
        const float* mBaseDist_s{};
        // static_param at offset 0x68
        const float* mBaseHeight_s{};
        // static_param at offset 0x70
        const float* mLowHeight_s{};
        // static_param at offset 0x78
        const float* mHighHeight_s{};
    };
    Params mParams;
};

}  // namespace uking::ai
