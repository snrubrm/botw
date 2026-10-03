#pragma once

#include "Game/Actor/actCamera.h"
#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventGameOver : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventGameOver, CameraEvent)
public:
    explicit CameraEventGameOver(const InitArg& arg);
    ~CameraEventGameOver() override;

protected:
    u8 _49[0x3];
    f32 _4c[2]{};
    f32 _54[2]{};
    u8 _5c[0x4];
    uking::act::Unk_7102459dd8 _60;
    s32 _80 = 1;
    u8 _84[0x4];
    u64 _88 = 0;
    u64 _90 = 0;
    u64 _98 = 0;
    u64 _a0 = 0;
    u64 _a8 = 0;
};
KSYS_CHECK_SIZE_NX150(CameraEventGameOver, 0xb0);

}  // namespace uking::action
