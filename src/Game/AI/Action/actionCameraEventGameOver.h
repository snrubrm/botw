#pragma once

#include "Game/Actor/actCamera.h"
#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventGameOver : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventGameOver, CameraEvent)
public:
    explicit CameraEventGameOver(const InitArg& arg);
    ~CameraEventGameOver() override;

protected:
    void m43() override;
    void m44() override;
    void m46() override;

    u8 _49[0x3];
    f32 _4c = 0.0f;
    f32 _50 = 0.0f;
    f32 _54 = 0.0f;
    f32 _58 = 0.0f;
    u8 _5c[0x4];
    uking::act::Unk_7102459dd8 _60;
    s32 _80 = 1;
    u8 _84[0x4];
    // static_param at offset 0x88
    const float* mLat_s{};
    // static_param at offset 0x90
    const float* mRadius_s{};
    // static_param at offset 0x98
    const float* mOffsetY_s{};
    // static_param at offset 0xa0
    const float* mFovy_s{};
    // static_param at offset 0xa8
    const float* mCount_s{};
};
KSYS_CHECK_SIZE_NX150(CameraEventGameOver, 0xb0);

}  // namespace uking::action
