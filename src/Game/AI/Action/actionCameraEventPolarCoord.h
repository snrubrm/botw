#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventPolarCoord : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventPolarCoord, CameraEvent)
public:
    explicit CameraEventPolarCoord(const InitArg& arg);

protected:
    virtual void m47();
    virtual bool m48();
    virtual void m49();
    virtual void m50();
    virtual float m51();
    virtual float m52();
    virtual float m53();
    virtual float m54();
};

}  // namespace uking::action
