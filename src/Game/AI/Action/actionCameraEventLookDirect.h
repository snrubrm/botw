#pragma once

#include "Game/AI/Action/actionCameraEventLookBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventLookDirect : public CameraEventLookBase {
    SEAD_RTTI_OVERRIDE(CameraEventLookDirect, CameraEventLookBase)
public:
    explicit CameraEventLookDirect(const InitArg& arg);

protected:
    void m46() override;
    void m48(sead::Matrix34f* mtx) override;

    // dynamic2_param at offset 0x120
    float* mPosX_d{};
    // dynamic2_param at offset 0x128
    float* mPosY_d{};
    // dynamic2_param at offset 0x130
    float* mPosZ_d{};
    // dynamic2_param at offset 0x138
    float* mDirX_d{};
    // dynamic2_param at offset 0x140
    float* mDirY_d{};
    // dynamic2_param at offset 0x148
    float* mDirZ_d{};
};

}  // namespace uking::action
