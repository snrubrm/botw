#pragma once

#include "KingSystem/System/VFRValue.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FreeMoveByGuideBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FreeMoveByGuideBase, ksys::act::ai::Action)
public:
    explicit FreeMoveByGuideBase(const InitArg& arg);
    ~FreeMoveByGuideBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotateAngleMax_s{};
    // static_param at offset 0x28
    const float* mMaxAngleAcc_s{};
    // static_param at offset 0x30
    const float* mAngleAccRatio_s{};
    // static_param at offset 0x38
    const bool* mKeepPlacementRotation_s{};
    // static_param at offset 0x40
    const bool* mIsTraceRailPointRotation_s{};
    // static_param at offset 0x48
    sead::SafeString mKeepRotationBaseBoneName_s{};
    // static_param at offset 0x58
    sead::SafeString mASKeyName_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetFrontDir_d{};
    u8 _78[0x30];
    ksys::VFRValue _a8;
    u8 _b4[0x34];
};
KSYS_CHECK_SIZE_NX150(FreeMoveByGuideBase, 0xe8);

}  // namespace uking::action
