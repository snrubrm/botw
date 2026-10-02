#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraWaterfallClimb : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraWaterfallClimb, CameraAction)
public:
    explicit CameraWaterfallClimb(const InitArg& arg);
    ~CameraWaterfallClimb() override;

protected:
    void m33() override;
    // 0x710078ad0c (not decompiled yet).
    void m34() override;
    void m36() override;

    s32 _4c = 3;
    sead::Vector3f _50 = sead::Vector3f::zero;
    sead::Vector3f _5c = sead::Vector3f::zero;
    f32 _68 = angleStuff(0);
    f32 _6c = angleStuff(0);
    f32 _70 = 0;
    f32 _74 = 0;
    f32 _78 = 0;
    f32 _7c = 0;
    f32 _80 = 0;
    f32 _84 = 0;
    f32 _88 = 0;
    f32 _8c = 0;
    f32 _90 = 0;
    f32 _94 = 0;
    act::Unk_7102459dd8 _98;
    // static_param at offset 0xb8
    const float* mLat_s{};
    // static_param at offset 0xc0
    const float* mLng_s{};
    // static_param at offset 0xc8
    const float* mRadius_s{};
    // static_param at offset 0xd0
    const float* mHeightAllowance_s{};
    // static_param at offset 0xd8
    const float* mManualHeightMin_s{};
    // static_param at offset 0xe0
    const float* mManualHeightMax_s{};
    // static_param at offset 0xe8
    const float* mOffsetY_s{};
    // static_param at offset 0xf0
    const float* mFovy_s{};
    f32 _f8 = 0;
    f32 _fc = 0;
    f32 _100 = 0;
    f32 _104 = 0;
    f32 _108 = 0;
    bool _10c = false;
};

}  // namespace uking::action
