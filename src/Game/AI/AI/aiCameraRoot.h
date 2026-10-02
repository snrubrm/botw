#pragma once

#include "Game/AI/AI/aiCameraAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraRoot : public CameraAI {
    SEAD_RTTI_OVERRIDE(CameraRoot, CameraAI)
public:
    explicit CameraRoot(const InitArg& arg);
    ~CameraRoot() override;
    bool m34(sead::Heap* heap) override;

protected:
    // 0x48..0x54: not initialised and not used by the decompiled functions
    u32 _48;
    u32 _4c;
    u32 _50;
    f32 _54 = 0.0f;
    u8 _58 = 0x25;
    u8 _59 = 0x25;
    bool _5a = false;
    bool _5b = false;
};

}  // namespace uking::ai
