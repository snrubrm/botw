#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraClimbObj : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraClimbObj, CameraAction)
public:
    explicit CameraClimbObj(const InitArg& arg);
    ~CameraClimbObj() override;

protected:
    void m35() override;
    bool m32(sead::Heap* heap) override;

    // Members not recovered yet (class size from the factory).
    u8 _50[0x128 - 0x50];
};
KSYS_CHECK_SIZE_NX150(CameraClimbObj, 0x128);

}  // namespace uking::action
