#pragma once
#include "KingSystem/System/Timer.h"

#include "Game/AI/Action/actionTeleportBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TeleportForceApperPosition : public TeleportBase {
    SEAD_RTTI_OVERRIDE(TeleportForceApperPosition, TeleportBase)
public:
    explicit TeleportForceApperPosition(const InitArg& arg);
    ~TeleportForceApperPosition() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const int* mArriveAtTargetTimeOut_s{};
    // static_param at offset 0x80
    const float* mArriveAtTargetRange_s{};
    // static_param at offset 0x88
    const bool* mIsArriveAtTarget_s{};
    // static_param at offset 0x90
    sead::SafeString mHideEffectName_s{};
    // dynamic_param at offset 0xa0
    sead::Vector3f* mAppearPosition_d{};
    ksys::Timer _a8{0, 0};
    bool _b4 = false;
};

}  // namespace uking::action
