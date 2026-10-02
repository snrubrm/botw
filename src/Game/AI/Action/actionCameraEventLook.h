#pragma once

#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionCameraEventLookBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class CameraEventLook : public CameraEventLookBase {
    SEAD_RTTI_OVERRIDE(CameraEventLook, CameraEventLookBase)
public:
    explicit CameraEventLook(const InitArg& arg);
    ~CameraEventLook() override;

protected:
    void m46() override;

    ksys::act::BaseProcLink _120;
    // dynamic_param at offset 0x130
    sead::SafeString mTargetUniqueName_d;
    u32 _140 = 0;
};

}  // namespace uking::action
