#pragma once

#include "Game/Actor/Player/Action/actionPlayerParashawlGlideBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerParashawlGlide : public PlayerParashawlGlideBase {
    SEAD_RTTI_OVERRIDE(PlayerParashawlGlide, PlayerParashawlGlideBase)
public:
    explicit PlayerParashawlGlide(const InitArg& arg);
    bool isFinished() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    const float* mEnergyGlide_s{};
    // static_param at offset 0x90
    const float* mNoEnergyTime_s{};
    int _98 = 0;
    int _9c = 0;
    bool _a0 = false;
};

}  // namespace uking::action
