#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "Game/AI/Action/actionCameraAction.h"
#include "Game/Actor/actCamera.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraMotorcycleLockOnEmpty : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraMotorcycleLockOnEmpty, CameraAction)
public:
    explicit CameraMotorcycleLockOnEmpty(const InitArg& arg);
    ~CameraMotorcycleLockOnEmpty() override;

protected:
    // 0x710077b570 / 0x710077b8dc (not decompiled yet).
    void m33() override;
    void m34() override;
    void m35() override;
    void m36() override;

    void sub_710077B7DC();

    // static_param at offset 0x50
    const float* mSpeedMax_s{};
    // static_param at offset 0x58
    const float* mSpeedMin_s{};
    // static_param at offset 0x60
    const float* mLatitudeMin_s{};
    // static_param at offset 0x68
    const float* mLatitudeMax_s{};
    // static_param at offset 0x70
    const float* mAutoLatitudeSlow_s{};
    // static_param at offset 0x78
    const float* mAutoLatitudeFast_s{};
    // static_param at offset 0x80
    const float* mAutoLatitudeB2ICushion_s{};
    // static_param at offset 0x88
    const float* mAutoLngBaseCushion_s{};
    // static_param at offset 0x90
    const float* mAutoLngMaxRotSpeed_s{};
    // static_param at offset 0x98
    const float* mCameraRadiusSlow_s{};
    // static_param at offset 0xa0
    const float* mCameraRadiusFast_s{};
    // static_param at offset 0xa8
    const float* mCameraRadiusB2ICushion_s{};
    // static_param at offset 0xb0
    const float* mCameraFollowRotCushion_s{};
    // static_param at offset 0xb8
    const float* mCameraFollowPosCushionX_s{};
    // static_param at offset 0xc0
    const float* mCameraFollowPosCushionYUp_s{};
    // static_param at offset 0xc8
    const float* mCameraFollowPosCushionYDown_s{};
    // static_param at offset 0xd0
    const float* mCameraFollowPosCushionZ_s{};
    // static_param at offset 0xd8
    const float* mFovySlow_s{};
    // static_param at offset 0xe0
    const float* mFovyFast_s{};
    // static_param at offset 0xe8
    const float* mFovyBaseCushion_s{};
    // static_param at offset 0xf0
    const float* mSwitchingCushionRate_s{};
    // static_param at offset 0xf8
    const sead::Vector3f* mAtOffsetWorld_s{};
    // static_param at offset 0x100
    const sead::Vector3f* mAtOffsetLocal_s{};
    f32 _108 = 0;
    f32 _10c = angleStuff(0);
    f32 _110 = angleStuff(0);
    f32 _114 = 0;
    sead::Vector3f _118 = sead::Vector3f::zero;
    f32 _124 = 0;
    f32 _128 = angleStuff(0);
    f32 _12c = angleStuff(0);
    f32 _130 = 0;
    sead::Vector3f _134 = sead::Vector3f::zero;
    f32 _140 = 0;
    f32 _144 = angleStuff(0);
    f32 _148 = angleStuff(0);
    f32 _14c = 0;
    sead::Vector3f _150 = sead::Vector3f::zero;
    f32 _15c = 0;
    f32 _160 = 0;
    bool _164 = false;
    sead::Matrix34f _168 = sead::Matrix34f::ident;
    f32 _198 = 0;
};

}  // namespace uking::action
