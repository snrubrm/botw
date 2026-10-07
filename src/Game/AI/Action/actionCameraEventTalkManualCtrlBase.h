#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionCameraEvent.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class CameraEventTalkManualCtrlBase : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventTalkManualCtrlBase, CameraEvent)
public:
    explicit CameraEventTalkManualCtrlBase(const InitArg& arg);
    ~CameraEventTalkManualCtrlBase() override = default;

protected:
    u64 m37() override { return 1; }
    int m38() override { return 0; }
    void m43() override;
    void m46() override;

    // Elevation / azimuth of the current camera direction (elevation clamped to [_d8, _dc]).
    virtual void m47(f32* elevation);
    virtual void m48(f32* azimuth);
    virtual void m49() {}
    virtual bool m50() { return true; }
    virtual f32 m51();
    virtual f32 m52();
    virtual f32 m53();
    virtual f32 m54();
    virtual f32 m55();
    virtual f32 m56();
    virtual f32 m57();
    virtual f32 m58();
    virtual f32 m59();
    virtual f32 m60();
    virtual f32 m61();
    virtual f32 m62();
    virtual bool m63();

    ksys::act::BaseProcLink _50;
    sead::Vector3f _60 = sead::Vector3f::zero;
    f32 _6c = angleStuff(0.0f);
    f32 _70 = angleStuff(0.0f);
    f32 _74 = angleStuff(0.0f);
    f32 _78 = angleStuff(0.0f);
    sead::Vector3f _7c = sead::Vector3f::zero;
    sead::Vector3f _88 = sead::Vector3f::zero;
    f32 _94 = 0;
    f32 _98 = 0;
    f32 _9c = 0;
    f32 _a0 = 0;
    f32 _a4 = 0;
    f32 _a8 = 0;
    f32 _ac = 0;
    act::Unk_7102459dd8 _b0;
    // dynamic_param at offset 0xd0
    float* mHeightOffset_d{};
    f32 _d8 = 0;
    f32 _dc = 0;
    f32 _e0 = 0;
    f32 _e4 = 0;
    f32 _e8 = 0;
    f32 _ec = 0;
    f32 _f0 = 0;
    u8 _f4 = 0;
    u8 _f5 = 0;
};

}  // namespace uking::action
