#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraAiming2 : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraAiming2, CameraAction)
public:
    explicit CameraAiming2(const InitArg& arg);
    ~CameraAiming2() override;

protected:
    void m33() override;
    void m34() override;
    void m35() override;
    void m36() override;

    // Clamps / converts the parameters into _278-_2a4.
    void sub_710074EC10();
    void sub_710074ED54();
    void sub_710074FDF0(sead::Vector3f* out);
    // Height offset for the current elevation (_4c), from the OffsetY parameters and curves.
    void sub_7100750334(f32* out);

    f32 _4c = 0;
    f32 _50 = 0;
    f32 _54 = 0;
    f32 _58 = 0;
    sead::Vector3f _5c = sead::Vector3f::zero;
    sead::Vector3f _68 = sead::Vector3f::zero;
    f32 _74 = 0;
    f32 _78 = 0;
    act::Unk_71008a45f0 _7c;
    f32 _158 = angleStuff(0);
    f32 _15c = angleStuff(0);
    f32 _160 = 0.6;
    f32 _164 = 0.9;
    f32 _168 = 0.4;
    f32 _16c = 0.9;
    f32 _170 = 0;
    f32 _174 = 0;
    f32 _178 = 0;
    f32 _17c = 0;
    act::Unk_7102459dd8 _180;
    f32 _1a0 = angleStuff(0);
    // static_param at offset 0x1a8
    const float* mLatMin_s{};
    // static_param at offset 0x1b0
    const float* mLatMax_s{};
    // static_param at offset 0x1b8
    const float* mLatMinWidth_s{};
    // static_param at offset 0x1c0
    const float* mLatMaxWidth_s{};
    // static_param at offset 0x1c8
    const float* mLatMinWeight_s{};
    // static_param at offset 0x1d0
    const float* mLatMaxWeight_s{};
    // static_param at offset 0x1d8
    const float* mLatStickScale_s{};
    // static_param at offset 0x1e0
    const float* mLngStickScale_s{};
    // static_param at offset 0x1e8
    const float* mLatGyroScale_s{};
    // static_param at offset 0x1f0
    const float* mLngGyroScale_s{};
    // static_param at offset 0x1f8
    const float* mRadiusMin_s{};
    // static_param at offset 0x200
    const float* mRadiusMax_s{};
    // static_param at offset 0x208
    const float* mRadiusMinWidth_s{};
    // static_param at offset 0x210
    const float* mRadiusMaxWidth_s{};
    // static_param at offset 0x218
    const float* mRadiusMinWeight_s{};
    // static_param at offset 0x220
    const float* mRadiusMaxWeight_s{};
    // static_param at offset 0x228
    const float* mSideOffset_s{};
    // static_param at offset 0x230
    const float* mOffsetYMin_s{};
    // static_param at offset 0x238
    const float* mOffsetYMax_s{};
    // static_param at offset 0x240
    const float* mOffsetYMinWidth_s{};
    // static_param at offset 0x248
    const float* mOffsetYMaxWidth_s{};
    // static_param at offset 0x250
    const float* mOffsetYMinWeight_s{};
    // static_param at offset 0x258
    const float* mOffsetYMaxWeight_s{};
    // static_param at offset 0x260
    const float* mFovy_s{};
    // static_param at offset 0x268
    const int* mGyro_s{};
    // static_param at offset 0x270
    const float* mConnect_s{};
    // Elevation range (sub_7100924CDC of LatMin / LatMax).
    f32 _278{};
    f32 _27c{};
    f32 _280{};
    f32 _284{};
    f32 _288{};
    f32 _28c{};
    f32 _290{};
    f32 _294{};
    f32 _298{};
    f32 _29c{};
    f32 _2a0{};
    u32 _2a4{};
    u8 _2a8 = 2;
};
KSYS_CHECK_SIZE_NX150(CameraAiming2, 0x2b0);

}  // namespace uking::action
