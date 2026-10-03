#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ControllerRumble : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ControllerRumble, ksys::act::ai::Action)
public:
    explicit ControllerRumble(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x20
    const int* mPattern_s{};
    // dynamic2_param at offset 0x28
    int* mCount_d{};
    s32 _30 = 0;
    s32 _34 = 1;
};
KSYS_CHECK_SIZE_NX150(ControllerRumble, 0x38);

}  // namespace uking::action
