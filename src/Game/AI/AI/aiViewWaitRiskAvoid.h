#pragma once

#include "Game/AI/AI/aiViewWait.h"
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

    // Not decompiled (0x7100e63c8 / 0x71005e651c / 0x71005e66d0 / 0x71005e6ee0).
    virtual void m40();
    virtual void m41();
    virtual bool m42();
    virtual void m43();

protected:
    // 0x71005e6b84: the angle between the direction to `target` and the front (both flattened) is below FrontAngle
    bool sub_71005E6B84(const sead::Vector3f& target);
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
