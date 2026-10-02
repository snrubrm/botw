#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventSavePoint : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraEventSavePoint, CameraAction)
public:
    explicit CameraEventSavePoint(const InitArg& arg);

    bool oneShot_() override;

protected:
    void m36() override;

    // static_param at offset 0x50
    const int* mSavePoint_s{};
    u8 _58 = 0;
};

}  // namespace uking::action
