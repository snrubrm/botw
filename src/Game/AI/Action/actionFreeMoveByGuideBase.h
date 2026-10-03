#pragma once

#include <math/seadMatrix.h>
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
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;
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
    sead::Vector3f _78;
    sead::Vector3f _84;
    sead::Vector3f _90;
    sead::Vector3f _9c;
    ksys::VFRValue _a8;
    sead::Matrix34f _b4;
    u32 _e4;
};
KSYS_CHECK_SIZE_NX150(FreeMoveByGuideBase, 0xe8);

}  // namespace uking::action
