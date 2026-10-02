#pragma once

#include "Game/AI/Action/actionWindCutter.h"
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerBeamMove : public WindCutter {
    SEAD_RTTI_OVERRIDE(PlayerBeamMove, WindCutter)
public:
    explicit PlayerBeamMove(const InitArg& arg);
    ~PlayerBeamMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool m33() override;

    xlink2::HandleSLink _c8;
};

}  // namespace uking::action
