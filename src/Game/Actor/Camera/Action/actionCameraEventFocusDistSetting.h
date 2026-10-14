#pragma once

#include "Game/Actor/actCamera.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventFocusDistSetting : public ksys::act::ai::Action, public Unk_7102459708 {
    SEAD_RTTI_OVERRIDE(CameraEventFocusDistSetting, ksys::act::ai::Action)
public:
    explicit CameraEventFocusDistSetting(const InitArg& arg);
    ~CameraEventFocusDistSetting() override;

    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic2_param at offset 0x30
    int* mClipIndex_d{};
    // dynamic2_param at offset 0x38
    float* mFocusDistStart_d{};
    // dynamic2_param at offset 0x40
    float* mFocusDistEnd_d{};
};

}  // namespace uking::action
