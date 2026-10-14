#pragma once

#include "Game/Actor/Action/actionStopBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HoldArrow : public StopBase {
    SEAD_RTTI_OVERRIDE(HoldArrow, StopBase)
public:
    explicit HoldArrow(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
};

}  // namespace uking::action
