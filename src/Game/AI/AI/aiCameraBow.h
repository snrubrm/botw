#pragma once

#include "Game/AI/AI/aiCameraAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraBow : public CameraAI {
    SEAD_RTTI_OVERRIDE(CameraBow, CameraAI)
public:
    explicit CameraBow(const InitArg& arg);
    bool m34(sead::Heap* heap) override;

protected:
};

}  // namespace uking::ai
