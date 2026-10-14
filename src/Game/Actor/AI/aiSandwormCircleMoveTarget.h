#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"

namespace uking::ai {

class SandwormCircleMoveTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormCircleMoveTarget, ksys::act::ai::Ai)
public:
    explicit SandwormCircleMoveTarget(const InitArg& arg);
    ~SandwormCircleMoveTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_7100558598();
    void sub_7100558774();
    void sub_7100558848();
    void sub_710055949C(sead::Vector3f* out);
    void sub_7100559954();

protected:
    // static_param at offset 0x38
    const int* mDirection_s{};
    // static_param at offset 0x40
    const float* mRadius_s{};
    // static_param at offset 0x48
    const float* mRadiusMargin_s{};
    // static_param at offset 0x50
    const float* mSpeed_s{};
    // static_param at offset 0x58
    const float* mFrontCheckLength_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    ksys::act::Unk_7100d3bce4 _68{mActor};
    f32 _80 = 0;
    f32 _84 = 1.0f;
    f32 _88 = 10.0f;
    bool _8c = false;
    bool _8d = false;
};
KSYS_CHECK_SIZE_NX150(SandwormCircleMoveTarget, 0x90);

}  // namespace uking::ai
