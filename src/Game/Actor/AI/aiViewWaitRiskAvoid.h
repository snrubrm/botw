#pragma once

#include <math/seadMatrix.h>

#include "Game/Actor/AI/aiViewWait.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class ViewWaitRiskAvoid : public ViewWait {
    SEAD_RTTI_OVERRIDE(ViewWaitRiskAvoid, ViewWait)
public:
    explicit ViewWaitRiskAvoid(const InitArg& arg);
    ~ViewWaitRiskAvoid() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m35() override;

    // 0x71005e66d0: m42 (decompiled, m).
    virtual void m40();
    // 0x71005e651c: starts (or retargets) the sideways avoid move; `dir` is -1 / 1 (RotDir).
    virtual void m41(s8 dir);
    virtual bool m42();
    virtual bool m43(sead::Vector3f* out);

protected:
    // 0x71005e6b84: the angle between the direction to `target` and the front (both flattened) is below FrontAngle
    bool sub_71005E6B84(const sead::Vector3f& target);
    // 0x71005e6d10 (unnamed in the CSV; used by m42): adds `amount` to `*side` (subtracts it when the actor at `mtx` is
    // on the other side of `dir`), scaled down to 0 once the angle between `dir` and the flattened direction from
    // `mtx` to the actor exceeds SpaceAngle. Skipped beyond `dist` + 1 unless `force`.
    void sub_71005E6D10(f32* side, const sead::Vector3f& dir, const sead::Matrix34f& mtx, bool force, f32 amount,
                        f32 dist);
    // static_param at offset 0x60
    const int* mAvoidFrame_s{};
    // static_param at offset 0x68
    const float* mFrontAngle_s{};
    // static_param at offset 0x70
    const float* mSpaceAngle_s{};
    // static_param at offset 0x78
    const float* mSpaceDist_s{};
    ksys::Timer _80;
};
KSYS_CHECK_SIZE_NX150(ViewWaitRiskAvoid, 0x90);

}  // namespace uking::ai
