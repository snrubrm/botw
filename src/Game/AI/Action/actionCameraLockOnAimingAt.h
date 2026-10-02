#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class CameraLockOnAimingAt : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraLockOnAimingAt, CameraAction)
public:
    explicit CameraLockOnAimingAt(const InitArg& arg);
    ~CameraLockOnAimingAt() override;

protected:
    void m33() override;
    // 0x710077408c (not decompiled yet).
    void m34() override;
    void m36() override;

    act::Unk_71008a45f0 _4c;
    ksys::act::BaseProcLink _128;
    sead::Vector3f _138 = sead::Vector3f::zero;
    sead::Vector3f _144 = sead::Vector3f::zero;
    sead::Vector3f _150 = sead::Vector3f::zero;
    f32 _15c = 0;
    f32 _160 = 0;
    f32 _164 = 0;
    f32 _168 = 0;
    sead::Vector3f _16c = sead::Vector3f::zero;
    f32 _178 = 0;
    f32 _17c = 0;
    f32 _180 = 0;
    f32 _184 = 0;
    f32 _188 = 0;
    f32 _18c = 0;
    f32 _190 = 0;
    f32 _194 = 0;
    f32 _198 = 0;
    f32 _19c = 0;
    sead::Vector3f _1a0 = sead::Vector3f::zero;
    sead::Vector3f _1ac = sead::Vector3f::zero;
    f32 _1b8 = 0;
    f32 _1bc = 0;
    act::Unk_7102459dd8 _1c0;
    // static_param at offset 0x1e0
    const float* mLatMin_s{};
    // static_param at offset 0x1e8
    const float* mLatMax_s{};
    // static_param at offset 0x1f0
    const float* mInputRangeNearDist_s{};
    // static_param at offset 0x1f8
    const float* mLatInputRange_s{};
    // static_param at offset 0x200
    const float* mLngInputRange_s{};
    // static_param at offset 0x208
    const float* mInputRangeFarDist_s{};
    // static_param at offset 0x210
    const float* mLatInputRangeFar_s{};
    // static_param at offset 0x218
    const float* mLngInputRangeFar_s{};
    // static_param at offset 0x220
    const float* mRadius_s{};
    // static_param at offset 0x228
    const float* mOffsetX_s{};
    // static_param at offset 0x230
    const float* mOffsetY_s{};
    // static_param at offset 0x238
    const float* mFovy_s{};
    // static_param at offset 0x240
    const int* mGyro_s{};
};

}  // namespace uking::action
