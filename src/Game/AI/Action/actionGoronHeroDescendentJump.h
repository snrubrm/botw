#pragma once

#include "Game/AI/Action/actionMoveToTargetCurveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GoronHeroDescendentJump : public MoveToTargetCurveBase {
    SEAD_RTTI_OVERRIDE(GoronHeroDescendentJump, MoveToTargetCurveBase)
public:
    explicit GoronHeroDescendentJump(const InitArg& arg);
    ~GoronHeroDescendentJump() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32() override;
    void m33(f32 dist, sead::Vector3f* pos) override;
    void m34(sead::Vector3f* target) override;
    f32 m35(const sead::Vector3f* from, const sead::Vector3f* to) override;
    // 0x710018e9a8 (declaration only): ground ray cast below the actor.
    bool sub_710018E9A8(f32 dist);

    // dynamic_param at offset 0x68
    bool* mIsIntoCannon_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mJumpTargetPos_d{};
};

}  // namespace uking::action
