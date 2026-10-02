#pragma once

#include "Game/AI/AI/aiCameraEventTalk.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraEventTalkAIRet : public CameraEventTalk {
    SEAD_RTTI_OVERRIDE(CameraEventTalkAIRet, CameraEventTalk)
public:
    explicit CameraEventTalkAIRet(const InitArg& arg);
    void m43() override;
    f32 m45() override;
    f32 m47() override;
    void m49() override;
    void m50() override;
    void m52(ksys::act::ai::InlineParamPack* params) override;

protected:
    const f32* _68{};
    s32* _70{};
    f32* _78{};
    s32 _80 = 0;
};

}  // namespace uking::ai
