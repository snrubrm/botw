#pragma once

#include "Game/AI/Action/actionCameraEventMovePosBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventMovePosFlow : public CameraEventMovePosBase {
    SEAD_RTTI_OVERRIDE(CameraEventMovePosFlow, CameraEventMovePosBase)
public:
    explicit CameraEventMovePosFlow(const InitArg& arg);

protected:
    void m46() override;
    float m47(const Pattern& pattern) override;
    bool m48() override;

    // dynamic2_param at offset 0x360
    bool* mAccept1FrameDelay_d{};
};
KSYS_CHECK_SIZE_NX150(CameraEventMovePosFlow, 0x368);

}  // namespace uking::action
