#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalRndMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalRndMove, ksys::act::ai::Ai)
public:
    explicit AnimalRndMove(const InitArg& arg);
    ~AnimalRndMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34(const sead::Vector3f* pos);
    virtual bool m35();

    bool sub_710030B070(const sead::Vector3f& pos);
    // 0x710030ae5c (placeholder name): whether the nav mesh goal is within SearchNextPathRadius (at most 0.4 of the
    // territory) of the actor; true when there is no goal or it is outside 1.1 of the territory around home.
    bool sub_710030AE5C();

protected:
    // static_param at offset 0x38
    const float* mSearchNextPathRadius_s{};
    // static_param at offset 0x40
    const float* mRadiusLimit_s{};
    // static_param at offset 0x48
    const float* mForwardDirDistCoefficient_s{};
    // static_param at offset 0x50
    const float* mDirRandomMinRatio_s{};
    // static_param at offset 0x58
    const float* mDirRangeAngle_s{};
    // static_param at offset 0x60
    const float* mRejectDistRatio_s{};
    // static_param at offset 0x68
    const float* mContinueAddSearchAngle_s{};
    // static_param at offset 0x70
    const float* mContinueReduceDistRatio_s{};
    // static_param at offset 0x78
    const float* mContinueReduceRejectDistRatio_s{};
    // map_unit_param at offset 0x80
    const float* mTerritoryArea_m{};
    // map_unit_param at offset 0x88
    const bool* mEnableNoEntryAreaCheck_m{};
    // aitree_variable at offset 0x90
    float* mFramesStuckOnTerrain_a{};
    // aitree_variable at offset 0x98
    bool* mIsStuckOnTerrain_a{};
    s32 _a0{};
    bool _a4 = true;
};

}  // namespace uking::ai
