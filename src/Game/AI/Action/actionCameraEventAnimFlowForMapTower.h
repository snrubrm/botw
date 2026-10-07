#pragma once

#include "Game/AI/Action/actionCameraEventAnimFlow.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventAnimFlowForMapTower : public CameraEventAnimFlow {
    SEAD_RTTI_OVERRIDE(CameraEventAnimFlowForMapTower, CameraEventAnimFlow)
public:
    explicit CameraEventAnimFlowForMapTower(const InitArg& arg);

protected:
    void m50(sead::BufferedSafeString* out) override;
};

}  // namespace uking::action
