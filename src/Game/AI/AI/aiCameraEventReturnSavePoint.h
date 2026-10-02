#pragma once

#include "Game/AI/AI/aiCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraEventReturnSavePoint : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventReturnSavePoint, CameraEvent)
public:
    explicit CameraEventReturnSavePoint(const InitArg& arg);
    void m41() override;
    void m43() override;
    void m40(ksys::act::ai::InlineParamPack* params) override;

protected:
    const int* _48{};
    int* _50{};
    f32* _58{};
    bool* _60{};
    s32 _68 = 0;
};

}  // namespace uking::ai
