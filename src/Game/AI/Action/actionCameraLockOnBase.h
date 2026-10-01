#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraLockOnBase : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraLockOnBase, CameraAction)
public:
    explicit CameraLockOnBase(const InitArg& arg);
    ~CameraLockOnBase() override;

protected:
    virtual bool m42();
    virtual void m43();
    virtual float m44();
    virtual float m45();
};

}  // namespace uking::action
