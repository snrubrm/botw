#pragma once

#include "Game/Actor/actCameraUtil.h"
#include "Game/Actor/actCamera.h"
#include "Game/AI/Action/actionCameraEvent.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventTurn : public CameraEvent {
    SEAD_RTTI_OVERRIDE(CameraEventTurn, CameraEvent)
public:
    explicit CameraEventTurn(const InitArg& arg);
    ~CameraEventTurn() override;

protected:
    u8 _49[0x3];
    uking::act::Unk_71009214b8 _4c;
    f32 _84 = 0.0f;
    uking::act::Unk_7102459dd8 _88;
    u64 _a8 = 0;
    u64 _b0 = 0;
    u64 _b8 = 0;
    u64 _c0 = 0;
    u64 _c8 = 0;
    u64 _d0 = 0;
    bool _d8 = true;
    u8 _d9[0x7];
};
KSYS_CHECK_SIZE_NX150(CameraEventTurn, 0xe0);

}  // namespace uking::action
