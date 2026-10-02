#pragma once

#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionCameraEventPolarCoordPlayer.h"
#include "Game/Actor/actCamera.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventPolarCoordPlayerRel : public CameraEventPolarCoordPlayer {
    SEAD_RTTI_OVERRIDE(CameraEventPolarCoordPlayerRel, CameraEventPolarCoordPlayer)
public:
    explicit CameraEventPolarCoordPlayerRel(const InitArg& arg);

protected:
    void m46() override;
    void m47() override;
    void m49() override;
    void m50() override;
    float m51() override;
    float m52() override;
    float m53() override;
    float m54() override;
    void m55(sead::Vector3f* out) override;
    bool m57() override;
    float m58() override;
    void m60(sead::Vector3f* out) override;
    void m61(sead::Vector3f* out) override;
    int m62(int idx) override;
    int m63() override;
    bool m64() override;

    // OtherActor (-1 if invalid or 1).
    s32 _1dc = -1;
    // AtCalcMode (3 if invalid).
    s32 _1e0 = 3;
    // FovyCalcMode != 0.
    s32 _1e4 = 1;
    // ReviseMode (1 if invalid).
    s32 _1e8 = 1;
    act::Unk_7102459dd8 _1f0;
    // dynamic2_param at offset 0x210
    int* mOtherActor_d{};
    // dynamic2_param at offset 0x218
    int* mAtCalcMode_d{};
    // dynamic2_param at offset 0x220
    int* mFovyCalcMode_d{};
    // dynamic2_param at offset 0x228
    int* mReviseMode_d{};
    // dynamic2_param at offset 0x230
    int* mActorIgnoringCollision_d{};
    // dynamic2_param at offset 0x238
    float* mLatOffset_d{};
    // dynamic2_param at offset 0x240
    float* mLngOffset_d{};
    // dynamic2_param at offset 0x248
    float* mRadiusOffset_d{};
    // dynamic2_param at offset 0x250
    float* mFovyParam_d{};
    // dynamic2_param at offset 0x258
    float* mTime_d{};
    // dynamic2_param at offset 0x260
    bool* mReverseOrder_d{};
    // dynamic_param at offset 0x268
    sead::SafeString mActorNameForOtherActor_d{};
    // dynamic_param at offset 0x278
    sead::SafeString mUniqueNameForOtherActor_d{};
    // dynamic2_param at offset 0x288
    sead::Vector3f* mAtParam_d{};
};
KSYS_CHECK_SIZE_NX150(CameraEventPolarCoordPlayerRel, 0x290);

}  // namespace uking::action
