#pragma once

#include "Game/AI/AI/aiNavMoveTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NavMoveNearTarget : public NavMoveTarget {
    SEAD_RTTI_OVERRIDE(NavMoveNearTarget, NavMoveTarget)
public:
    explicit NavMoveNearTarget(const InitArg& arg);
    ~NavMoveNearTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    sead::Vector3f* m34() override { return &_390; }
    void m35(sead::Vector3f* out) override;
    virtual bool m38(f32* out);

protected:
    void calc_() override;

    // static_param at offset 0x380
    const float* mTargetVMax_s{};
    // static_param at offset 0x388
    const float* mTargetVMin_s{};
    /* 0x390 */ sead::Vector3f _390;
};
KSYS_CHECK_SIZE_NX150(NavMoveNearTarget, 0x3a0);

}  // namespace uking::ai
