#pragma once

#include "Game/AI/Action/actionCameraLockOnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraMagneCatch : public CameraLockOnBase {
    SEAD_RTTI_OVERRIDE(CameraMagneCatch, CameraLockOnBase)
public:
    explicit CameraMagneCatch(const InitArg& arg);
    ~CameraMagneCatch() override;

protected:
    bool m60(int idx) override { return u32(idx) < 3; }
};

}  // namespace uking::action
