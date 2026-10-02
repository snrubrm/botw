#pragma once

#include "Game/AI/Action/actionCameraEventAnimFlowBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventAnimFlow : public CameraEventAnimFlowBase {
    SEAD_RTTI_OVERRIDE(CameraEventAnimFlow, CameraEventAnimFlowBase)
public:
    explicit CameraEventAnimFlow(const InitArg& arg);
    ~CameraEventAnimFlow() override = default;

protected:
    void m46() override;
    u8 m52() override;
    void m53() override;
    const sead::SafeString& m54() override;
    const sead::SafeString& m55() override;
    u8 m56() override;
    void m57() override;
    u8 m58() override;
    void m59() override;
    bool m60() override;

    // dynamic2_param at offset 0x180
    int* mTargetActor_d{};
    // dynamic2_param at offset 0x188
    int* mTargetActorPosReferenceMode_d{};
    // dynamic2_param at offset 0x190
    int* mTargetActorDirReferenceMode_d{};
    // dynamic2_param at offset 0x198
    bool* mAccept1FrameDelay_d{};
    // dynamic_param at offset 0x1a0
    sead::SafeString mActorName_d;
    // dynamic_param at offset 0x1b0
    sead::SafeString mUniqueName_d;
    u8 _1c0 = 4;
    u8 _1c1 = 4;
    u8 _1c2 = 4;
};

}  // namespace uking::action
