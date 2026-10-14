#pragma once

#include "Game/Actor/actCamera.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventReserveConnectTime : public ksys::act::ai::Action, public Unk_7102459708 {
    SEAD_RTTI_OVERRIDE(CameraEventReserveConnectTime, ksys::act::ai::Action)
public:
    explicit CameraEventReserveConnectTime(const InitArg& arg);
    ~CameraEventReserveConnectTime() override;

    bool oneShot_() override;
    void loadParams_() override;

protected:
    // dynamic2_param at offset 0x30
    float* mInterpolateTime_d{};
};

}  // namespace uking::action
