#pragma once

#include "Game/AI/Action/actionCameraEventAnimBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventAnim : public CameraEventAnimBase {
    SEAD_RTTI_OVERRIDE(CameraEventAnim, CameraEventAnimBase)
public:
    explicit CameraEventAnim(const InitArg& arg);
    ~CameraEventAnim() override;

protected:
    void m46() override;
    float m49() override;
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
    int* mClipIndex_d{};
    // dynamic2_param at offset 0x188
    int* mTargetActor_d{};
    // dynamic2_param at offset 0x190
    int* mTargetActorPosReferenceMode_d{};
    // dynamic2_param at offset 0x198
    int* mTargetActorDirReferenceMode_d{};
    // dynamic2_param at offset 0x1a0
    bool* mAccept1FrameDelay_d{};
    // dynamic_param at offset 0x1a8
    sead::SafeString mActorName_d;
    // dynamic_param at offset 0x1b8
    sead::SafeString mUniqueName_d;
    u8 _1c8 = 4;
    u8 _1c9 = 4;
    u8 _1ca = 4;
};

}  // namespace uking::action
