#pragma once

#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraWaterRemainsHowling : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraWaterRemainsHowling, CameraAction)
public:
    explicit CameraWaterRemainsHowling(const InitArg& arg);
    ~CameraWaterRemainsHowling() override;

protected:
    // 0x710078c42c (not decompiled yet).
    void m34() override;
    void m33() override;

    void sub_710078BF18();
    void sub_710078C1F0();
    void m36() override;

    f32 _4c = angleStuff(0);
    f32 _50 = angleStuff(0);
    f32 _54 = 1.0;
    sead::Vector3f _58 = sead::Vector3f::zero;
    sead::Vector3f _64 = sead::Vector3f::zero;
    f32 _70 = angleStuff(0);
    f32 _74 = angleStuff(0);
    f32 _78 = 0;
    sead::Vector3f _7c = sead::Vector3f::zero;
    sead::Vector3f _88 = sead::Vector3f::zero;
    f32 _94 = 0;
    f32 _98 = 0;
    act::Unk_7102459dd8 _a0;
    // static_param at offset 0xc0
    const float* mRadius_s{};
    // static_param at offset 0xc8
    const float* mRadiusFromPlayer_s{};
    // static_param at offset 0xd0
    const float* mAtY_s{};
    // static_param at offset 0xd8
    const float* mAtOffsetZ_s{};
    // static_param at offset 0xe0
    const float* mWaterAvoid4At_s{};
    // static_param at offset 0xe8
    const float* mWaterAvoid4CameraPos_s{};
    // static_param at offset 0xf0
    const float* mFovy_s{};
    // static_param at offset 0xf8
    const float* mConnect_s{};
    f32 _100 = 0;
    f32 _104 = 0;
    f32 _108 = 0;
    f32 _10c = 0;
    bool _110 = false;
};

}  // namespace uking::action
