#pragma once

#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventTalk : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventTalk, CameraEvent)
public:
    explicit CameraEventTalk(const InitArg& arg);
    ~CameraEventTalk() override;

protected:
    int m38() override { return 0; }
    u32 m37() override { return 1; }
};

}  // namespace uking::action
