#pragma once

#include "Game/Actor/actCamera.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventOverwriteFar : public ksys::act::ai::Action, public Unk_7102459708 {
    SEAD_RTTI_OVERRIDE(CameraEventOverwriteFar, ksys::act::ai::Action)
public:
    explicit CameraEventOverwriteFar(const InitArg& arg);
    ~CameraEventOverwriteFar() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic2_param at offset 0x30
    float* mFar_d{};
};

}  // namespace uking::action
