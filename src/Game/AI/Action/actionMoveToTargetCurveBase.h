#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>
#include "KingSystem/System/Timer.h"

namespace uking::action {

class MoveToTargetCurveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MoveToTargetCurveBase, ksys::act::ai::Action)
public:
    explicit MoveToTargetCurveBase(const InitArg& arg);
    ~MoveToTargetCurveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    // Called at the end of enter_.
    virtual void m32() = 0;
    // Called every frame with the distance to the target and the next position on the curve.
    virtual void m33(f32 dist, sead::Vector3f* pos) = 0;
    // Writes the target position.
    virtual void m34(sead::Vector3f* target) = 0;
    // Height of the curve's apex above the start (at least `MaxHeight`).
    virtual f32 m35(const sead::Vector3f* from, const sead::Vector3f* to);

    // static_param at offset 0x20
    const float* mMaxHeight_s{};
    // static_param at offset 0x28
    const float* mTimeScale_s{};
    // static_param at offset 0x30
    const bool* mIsDebugDrawTargetPos_s{};
    ksys::Timer _38;
    sead::Vector3f _44 = sead::Vector3f::zero;
    f32 _50 = 0;
    f32 _54 = 0;
    f32 _58 = 0;
    f32 _5c = 0;
    f32 _60 = 0;
    f32 _64 = 0;
};

KSYS_CHECK_SIZE_NX150(MoveToTargetCurveBase, 0x68);

}  // namespace uking::action
