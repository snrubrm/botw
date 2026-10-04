#pragma once

#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASHoldLegTurn : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASHoldLegTurn, ksys::act::ai::Action)
public:
    explicit ForkASHoldLegTurn(const InitArg& arg);
    ~ForkASHoldLegTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x710013ee00 (declared only): the body of calc_ is out of line in the original.
    void sub_710013EE00();
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeed_s{};
    // static_param at offset 0x28
    const float* mStopSpeedRatio_s{};
    // static_param at offset 0x30
    const float* mStopRotSpeedRatio_s{};
    // static_param at offset 0x38
    const float* mTargetPosNoUpdateArea_s{};
    // static_param at offset 0x40
    const bool* mIsFixBoneWithGround_s{};
    // static_param at offset 0x48
    sead::SafeString mRotBaseBoneName_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    ksys::act::Actor* _60 = mActor;
    s32 _68 = 0;
    bool _6c = false;
    u8 _6d[0x63];
    ksys::act::BoneHandle _d0;
    u8 _178[0x10];
};
KSYS_CHECK_SIZE_NX150(ForkASHoldLegTurn, 0x188);

}  // namespace uking::action
