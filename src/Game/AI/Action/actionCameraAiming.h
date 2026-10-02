#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::act {
class ActorConstDataAccess;
}

namespace uking::action {

class CameraAiming : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraAiming, CameraAction)
public:
    explicit CameraAiming(const InitArg& arg);
    ~CameraAiming() override;

protected:
    void m33() override;
    void m34() override;
    void m35() override;
    void m36() override;

    void sub_710074C97C();
    void sub_710074D4A4(f32* out);
    void sub_710074D598(const act::Unk_7100922700& polar);
    void sub_710074D9EC();
    void sub_710074DAE8(sead::Matrix34f* mtx);
    void sub_710074DBD0(const sead::Matrix34f& mtx, sead::Vector3f* out);
    void sub_710074DD28(const act::Unk_7100922700& polar, sead::Vector3f* out);
    // Acquires the player (or what the player is riding / connected to) into `accessor`.
    void sub_710074E3EC(ksys::act::ActorConstDataAccess* accessor);

    f32 _4c = 0;
    f32 _50 = 0;
    sead::Vector3f _54 = sead::Vector3f::zero;
    sead::Vector3f _60 = sead::Vector3f::zero;
    f32 _6c = 0;
    f32 _70 = 0;
    act::Unk_71008a45f0 _74;
    f32 _150 = angleStuff(0);
    f32 _154 = angleStuff(0);
    f32 _158 = angleStuff(0);
    f32 _15c = angleStuff(0);
    s32 _160 = 0;
    f32 _164 = 0;
    f32 _168 = 0;
    f32 _16c = 0;
    sead::Vector3f _170 = sead::Vector3f::zero;
    sead::Vector3f _17c = sead::Vector3f::zero;
    f32 _188 = 0.6;
    f32 _18c = 0.9;
    f32 _190 = 0.4;
    f32 _194 = 0.9;
    f32 _198 = 0;
    f32 _19c = 0;
    f32 _1a0 = 0;
    f32 _1a4 = 0;
    act::Unk_7102459dd8 _1a8;
    f32 _1c8 = angleStuff(0);
    // static_param at offset 0x1d0
    const float* mLatMin_s{};
    // static_param at offset 0x1d8
    const float* mLatMax_s{};
    // static_param at offset 0x1e0
    const float* mLatOffset_s{};
    // static_param at offset 0x1e8
    const float* mLatStickScale_s{};
    // static_param at offset 0x1f0
    const float* mLngStickScale_s{};
    // static_param at offset 0x1f8
    const float* mLatGyroScale_s{};
    // static_param at offset 0x200
    const float* mLngGyroScale_s{};
    // static_param at offset 0x208
    const float* mRadiusMin_s{};
    // static_param at offset 0x210
    const float* mRadiusMax_s{};
    // static_param at offset 0x218
    const float* mRadiusMinLat_s{};
    // static_param at offset 0x220
    const float* mRadiusMaxLat_s{};
    // static_param at offset 0x228
    const float* mRadiusCus_s{};
    // static_param at offset 0x230
    const float* mSideOffset_s{};
    // static_param at offset 0x238
    const sead::Vector3f* mWorldBaseOffset_s{};
    // static_param at offset 0x240
    const float* mOffsetZ_s{};
    // static_param at offset 0x248
    const float* mOffsetZMin_s{};
    // static_param at offset 0x250
    const float* mOffsetZMax_s{};
    // static_param at offset 0x258
    const float* mAtCus_s{};
    // static_param at offset 0x260
    const float* mFovy_s{};
    // static_param at offset 0x268
    const int* mGyro_s{};
    // static_param at offset 0x270
    const int* mConnectType_s{};
    // static_param at offset 0x278
    const float* mConnect_s{};
    // Elevation range (sub_7100924CDC of latMin / latMax).
    f32 _280{};
    f32 _284{};
    u8 _288 = 0;
    u8 _289 = 0;
    u8 _28a = 2;
    u8 _28b = 2;
};
KSYS_CHECK_SIZE_NX150(CameraAiming, 0x290);

}  // namespace uking::action
