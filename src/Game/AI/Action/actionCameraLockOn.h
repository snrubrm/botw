#pragma once

#include "Game/AI/Action/actionCameraLockOnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraLockOn : public CameraLockOnBase {
    SEAD_RTTI_OVERRIDE(CameraLockOn, CameraLockOnBase)
public:
    explicit CameraLockOn(const InitArg& arg);

protected:
    float m44() override;
    float m45() override;

    u8 _1bf = 0;
};

}  // namespace uking::action
