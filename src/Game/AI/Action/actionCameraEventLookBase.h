#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventLookBase : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventLookBase, CameraEvent)
public:
    explicit CameraEventLookBase(const InitArg& arg);
    ~CameraEventLookBase() override;

protected:
    void m46() override;

    virtual void m47();
    virtual void m48(sead::Matrix34f* mtx);

    act::Unk_71009214b8 _4c;
    f32 _84 = 0;
    f32 _88 = 0;
    f32 _8c = 0;
    f32 _90 = 0;
    f32 _94 = 0;
    f32 _98 = 0;
    f32 _9c = 0;
    f32 _a0 = 0;
    f32 _a4 = 0;
    // dynamic2_param at offset 0xa8
    float* mAngle_d{};
    // dynamic2_param at offset 0xb0
    float* mNear_d{};
    // dynamic2_param at offset 0xb8
    float* mMiddle_d{};
    // dynamic2_param at offset 0xc0
    float* mFar_d{};
    // dynamic2_param at offset 0xc8
    float* mLatMin_d{};
    // dynamic2_param at offset 0xd0
    float* mLatMax_d{};
    // dynamic2_param at offset 0xd8
    float* mFovyMin_d{};
    // dynamic2_param at offset 0xe0
    float* mFovyMax_d{};
    // dynamic2_param at offset 0xe8
    float* mCount_d{};
    // dynamic2_param at offset 0xf0
    int* mLatMode_d{};
    // dynamic2_param at offset 0xf8
    int* mReviseMode_d{};
    // dynamic2_param at offset 0x100
    bool* mBaseAngleCamera_d{};
    // dynamic2_param at offset 0x108
    bool* mBack_d{};
    // dynamic2_param at offset 0x110
    bool* mBgHitJump_d{};
    u8 _118 = 0;
    u8 _119 = 2;
    u8 _11a = 2;
};

}  // namespace uking::action
