#pragma once

#include "Game/Actor/actCameraUtil.h"
#include "Game/Actor/actCamera.h"
#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventTurn : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventTurn, CameraEvent)
public:
    explicit CameraEventTurn(const InitArg& arg);
    ~CameraEventTurn() override;

protected:
    void m43() override;
    void m44() override;
    void m46() override;

    u8 _49[0x3];
    uking::act::Unk_71009214b8 _4c;
    f32 _84 = 0.0f;
    uking::act::Unk_7102459dd8 _88;
    // dynamic_param at offset 0xa8
    int* mReviseModeRunning_d{};
    // dynamic_param at offset 0xb0
    float* mPosX_d{};
    // dynamic_param at offset 0xb8
    float* mPosY_d{};
    // dynamic_param at offset 0xc0
    float* mPosZ_d{};
    // dynamic_param at offset 0xc8
    float* mCount_d{};
    // dynamic_param at offset 0xd0
    float* mCushion_d{};
    u8 _d8 = 1;
    u8 _d9[0x7];
};
KSYS_CHECK_SIZE_NX150(CameraEventTurn, 0xe0);

}  // namespace uking::action
