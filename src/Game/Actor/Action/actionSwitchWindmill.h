#pragma once

#include <gsys/gsysModelAccessKey.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace uking::action {

class SwitchWindmill : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwitchWindmill, ksys::act::ai::Action)
public:
    explicit SwitchWindmill(const InitArg& arg);
    ~SwitchWindmill() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;

    gsys::BoneAccessKeyEx _20;
    ksys::act::BoneHandle _58;
    // static_param at offset 0x100
    const float* mSwRadTh_s{};
    // static_param at offset 0x108
    const float* mSwRadAllowance_s{};
    // static_param at offset 0x110
    const float* mRotAccel_s{};
    // static_param at offset 0x118
    const float* mMaxRotSpeed_s{};
    // static_param at offset 0x120
    sead::SafeString mTargetNodeName_s{};
    f32 _130 = 0;
    f32 _134 = 0;
};
KSYS_CHECK_SIZE_NX150(SwitchWindmill, 0x138);

}  // namespace uking::action
