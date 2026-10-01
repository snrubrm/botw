#include "Game/AI/Action/actionSiteBossSwordShieldRepair.h"

namespace uking::action {

SiteBossSwordShieldRepair::SiteBossSwordShieldRepair(const InitArg& arg) : OnetimeStopASPlay(arg) {}

SiteBossSwordShieldRepair::~SiteBossSwordShieldRepair() = default;

bool SiteBossSwordShieldRepair::init_(sead::Heap* heap) {
    _4c = 0;
    return true;
}

void SiteBossSwordShieldRepair::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void SiteBossSwordShieldRepair::leave_() {
    OnetimeStopASPlay::leave_();
}

void SiteBossSwordShieldRepair::loadParams_() {
    OnetimeStopASPlay::loadParams_();
}

void SiteBossSwordShieldRepair::calc_() {
    if (_48) {
        setFinished();
        return;
    }
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
