#pragma once

#include <time/seadTickTime.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TimeSpecControllerRumble : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TimeSpecControllerRumble, ksys::act::ai::Action)
public:
    explicit TimeSpecControllerRumble(const InitArg& arg);
    ~TimeSpecControllerRumble() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mPattern_s{};
    // dynamic_param at offset 0x28
    int* mSeconds_d{};
    // dynamic_param at offset 0x30
    bool* mIsWait_d{};
    sead::TickTime _38;
};
KSYS_CHECK_SIZE_NX150(TimeSpecControllerRumble, 0x40);

}  // namespace uking::action
