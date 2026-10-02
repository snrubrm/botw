#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraRevolve : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraRevolve, CameraAction)
public:
    explicit CameraRevolve(const InitArg& arg);
    ~CameraRevolve() override;

protected:
    // 0x710077d4f8 / 0x710077d774 (not decompiled yet).
    void m33() override;
    void m34() override;
    void m35() override;
    void m36() override;

    f32 _4c = 0;
    f32 _50 = 0;
    f32 _54 = 0;
    f32 _58 = 0;
    f32 _5c = 0;
    f32 _60 = 0;
    f32 _64 = 0;
    f32 _68 = 0;
    // static_param at offset 0x70
    const float* mLatTarget_s{};
    // static_param at offset 0x78
    const float* mLatCus_s{};
    // static_param at offset 0x80
    const bool* mIsKeepLat_s{};
    // static_param at offset 0x88
    const float* mLngTarget_s{};
    // static_param at offset 0x90
    const float* mLngCus_s{};
    // static_param at offset 0x98
    const bool* mIsKeepLng_s{};
    // static_param at offset 0xa0
    const float* mRadiusMin_s{};
    // static_param at offset 0xa8
    const float* mRadiusMax_s{};
    // static_param at offset 0xb0
    const float* mRadiusCus_s{};
    // static_param at offset 0xb8
    const float* mSideOffset_s{};
    // static_param at offset 0xc0
    const float* mSideOffsetCus_s{};
    // static_param at offset 0xc8
    const sead::Vector3f* mWorldBaseOffset_s{};
    // static_param at offset 0xd0
    const sead::Vector3f* mPlayerBaseOffset_s{};
    // static_param at offset 0xd8
    const float* mAtHCus_s{};
    // static_param at offset 0xe0
    const float* mAtHCusSword_s{};
    // static_param at offset 0xe8
    const float* mAtVCus_s{};
    // static_param at offset 0xf0
    const float* mFovy_s{};
    // static_param at offset 0xf8
    const float* mFovyCus_s{};
    // static_param at offset 0x100
    const float* mStartCus_s{};
};

}  // namespace uking::action
