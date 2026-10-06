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
    void m35(ksys::act::ai::InlineParamPack* params) override;
    void m37() override;
    void m38() override;

    void sub_710078F434();
    // 0x710079016c (placeholder name): while the player rides a horse without an attention target, tracks (flag 8
    // of `_5a`) whether the stick is idle.
    void sub_710079016C();

protected:
    // 0x48..0x54: not initialised and not used by the decompiled functions
    u32 _48;
    u32 _4c;
    u32 _50;
    f32 _54 = 0.0f;
    u8 _58 = 0x25;
    u8 _59 = 0x25;
    u8 _5a = 0;  // flags (bit 3: the stick was idle, see sub_710079016C)
    bool _5b = false;
};

}  // namespace uking::ai
