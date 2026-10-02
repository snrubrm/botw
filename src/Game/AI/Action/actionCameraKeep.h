#pragma once

#include "Game/AI/Action/actionCameraAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraKeep : public CameraAction {
    SEAD_RTTI_OVERRIDE(CameraKeep, CameraAction)
public:
    explicit CameraKeep(const InitArg& arg);

    bool isFinished() const override;

protected:
    void m33() override;
    void m34() override;
    void m41() override;

    // 0x71007734cc: whether the camera moved more than 2 units away from _4c or there is input
    // (any button of _58 held or a stick moved).
    bool sub_71007734CC() const;

    sead::Vector3f _4c = sead::Vector3f::zero;
    u32 _58 = 0xf60ff;
};

}  // namespace uking::action
