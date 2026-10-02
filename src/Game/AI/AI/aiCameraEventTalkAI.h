#pragma once

#include "Game/AI/AI/aiCameraEventTalk.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraEventTalkAI : public CameraEventTalk {
    SEAD_RTTI_OVERRIDE(CameraEventTalkAI, CameraEventTalk)
public:
    explicit CameraEventTalkAI(const InitArg& arg);
    void m43() override;
    f32 m45() override;
    bool m46() override;
    bool m48() override;
    void m50() override;

protected:
    const f32* _68{};
    bool* _70{};
    bool* _78{};
};

}  // namespace uking::ai
