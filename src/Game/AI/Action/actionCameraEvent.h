#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEvent : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraEvent, CameraAction)
public:
    explicit CameraEvent(const InitArg& arg);

protected:




    virtual bool m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
};

}  // namespace uking::action
