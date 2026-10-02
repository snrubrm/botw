#pragma once

#include "Game/AI/Action/actionCameraEventAnimBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventAnimFlowBase : public CameraEventAnimBase {
    SEAD_RTTI_OVERRIDE(CameraEventAnimFlowBase, CameraEventAnimBase)
public:
    explicit CameraEventAnimFlowBase(const InitArg& arg);
    // Inline: first emitted in the CameraEventAnimFlowAbs translation unit in the original.
    ~CameraEventAnimFlowBase() override = default;

protected:
    void m47() override;
    void m48() override;
    float m49() override;

    f32 _17c = 0;
};

}  // namespace uking::action
