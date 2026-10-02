#pragma once

#include "Game/AI/AI/aiCameraAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraTool : public CameraAI {
    SEAD_RTTI_OVERRIDE(CameraTool, CameraAI)
public:
    explicit CameraTool(const InitArg& arg);
    ~CameraTool() override;

    bool m34(sead::Heap* heap) override;
    void m35(ksys::act::ai::InlineParamPack* params) override;

protected:
    act::Unk_7100791b1c _48;
    u32 _b8 = 0;
};

}  // namespace uking::ai
