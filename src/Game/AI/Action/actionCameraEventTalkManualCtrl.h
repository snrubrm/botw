#pragma once

#include "Game/AI/Action/actionCameraEventTalkManualCtrlBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventTalkManualCtrl : public CameraEventTalkManualCtrlBase {
    SEAD_RTTI_OVERRIDE(CameraEventTalkManualCtrl, CameraEventTalkManualCtrlBase)
public:
    explicit CameraEventTalkManualCtrl(const InitArg& arg);

protected:
    void m46() override;
    f32 m51() override;
    f32 m52() override;
    f32 m53() override;
    f32 m54() override;
    f32 m55() override;
    f32 m56() override;
    f32 m57() override;
    f32 m58() override;
    f32 m59() override;
    f32 m60() override;
    f32 m62() override;
    bool m63() override;

    // static_param at offset 0xf8
    const float* mLatMin_s{};
    // static_param at offset 0x100
    const float* mLatMax_s{};
    // static_param at offset 0x108
    const float* mLatStickScale_s{};
    // static_param at offset 0x110
    const float* mLngStickScale_s{};
    // static_param at offset 0x118
    const float* mDistanceMin_s{};
    // static_param at offset 0x120
    const float* mDistanceMax_s{};
    // static_param at offset 0x128
    const float* mRadiusNear_s{};
    // static_param at offset 0x130
    const float* mRadiusFar_s{};
    // static_param at offset 0x138
    const float* mFovyNear_s{};
    // static_param at offset 0x140
    const float* mFovyFar_s{};
    // static_param at offset 0x148
    const float* mConnect_s{};
    // dynamic2_param at offset 0x150
    bool* mNoConnect_d{};
};

}  // namespace uking::action
