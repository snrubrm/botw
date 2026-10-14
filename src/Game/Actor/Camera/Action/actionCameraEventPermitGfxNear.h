#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventPermitGfxNear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraEventPermitGfxNear, ksys::act::ai::Action)
public:
    explicit CameraEventPermitGfxNear(const InitArg& arg);

    bool oneShot_() override;

protected:
};

}  // namespace uking::action
