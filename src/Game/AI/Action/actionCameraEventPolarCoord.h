#pragma once

#include <math/seadVector.h>
#include "Game/AI/Action/actionCameraEvent.h"
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

// Moves the camera to a polar coordinate (m51 elevation, m52 azimuth, m53 distance) around a
// look-at point (m55), interpolating from the current camera state with the progress m58.
class CameraEventPolarCoord : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventPolarCoord, CameraEvent)
public:
    explicit CameraEventPolarCoord(const InitArg& arg);

protected:
    void m43() override;
    void m44() override;

    virtual void m47();
    virtual bool m48();
    virtual void m49();
    virtual void m50();
    virtual float m51();
    virtual float m52();
    virtual float m53();
    virtual float m54();
    virtual void m55(sead::Vector3f* out);
    virtual void m56(act::Unk_7100922700* out);
    virtual bool m57();
    virtual float m58();
    virtual const ksys::act::BaseProcLink* m59();

    // Look-at point and its offset from the target.
    sead::Vector3f _4c = sead::Vector3f::zero;
    sead::Vector3f _58 = sead::Vector3f::zero;
    // Elevation / azimuth (degrees) and their offsets from the target.
    f32 _64 = angleStuff(0);
    f32 _68 = angleStuff(0);
    f32 _6c = angleStuff(0);
    f32 _70 = angleStuff(0);
    // Distance, fovy and roll (Unk_71009214b8::_28) and their offsets.
    f32 _74 = 0;
    f32 _78 = 0;
    f32 _7c = 0;
    f32 _80 = 0;
    f32 _84 = 0;
    f32 _88 = 0;
    s32 _8c = 0;
    bool _90 = false;
    bool _91 = true;
};

}  // namespace uking::action
