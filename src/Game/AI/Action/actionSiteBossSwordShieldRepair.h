#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossSwordShieldRepair : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(SiteBossSwordShieldRepair, OnetimeStopASPlay)
public:
    explicit SiteBossSwordShieldRepair(const InitArg& arg);
    ~SiteBossSwordShieldRepair() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool _48 = false;
    int _4c = 0;
};

}  // namespace uking::action
