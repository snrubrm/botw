#pragma once

#include "KingSystem/System/Timer.h"
#include "Game/AI/Action/actionBlownOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossBlowOff : public BlownOff {
    SEAD_RTTI_OVERRIDE(SiteBossBlowOff, BlownOff)
public:
    explicit SiteBossBlowOff(const InitArg& arg);
    ~SiteBossBlowOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m36() override;
    s32 m40() override;

    ksys::Timer _160;
};

}  // namespace uking::action
