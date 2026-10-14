#pragma once

#include "Game/Actor/Camera/Action/actionCameraTrackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraLockOn : public CameraTrackBase {
    SEAD_RTTI_OVERRIDE(CameraLockOn, CameraTrackBase)
public:
    explicit CameraLockOn(const InitArg& arg);

protected:
    float m44() override;
    float m45() override;
    bool m51() override;
    void m57() override;
    bool m58() override;
    void m56(bool x) override;

    u8 _1bf = 0;
};

}  // namespace uking::action
