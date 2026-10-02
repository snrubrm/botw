#pragma once

#include "Game/AI/Action/actionCameraEventMovePosBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventMovePos : public CameraEventMovePosBase {
    SEAD_RTTI_OVERRIDE(CameraEventMovePos, CameraEventMovePosBase)
public:
    explicit CameraEventMovePos(const InitArg& arg);

protected:
    void m46() override;
    float m47(const Pattern& pattern) override;
    bool m48() override;

    // static_param at offset 0x360
    const bool* mAccept1FrameDelay_s{};
};
KSYS_CHECK_SIZE_NX150(CameraEventMovePos, 0x368);

}  // namespace uking::action
