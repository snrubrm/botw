#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraMotorcycle : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraMotorcycle, CameraAction)
public:
    explicit CameraMotorcycle(const InitArg& arg);
    ~CameraMotorcycle() override;

protected:

    // Members not recovered yet (class size from the factory).
    u8 _50[0x528 - 0x50];
};
KSYS_CHECK_SIZE_NX150(CameraMotorcycle, 0x528);

}  // namespace uking::action
