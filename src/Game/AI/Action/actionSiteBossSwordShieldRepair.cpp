#include "Game/AI/Action/actionSiteBossSwordShieldRepair.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::action {

SiteBossSwordShieldRepair::SiteBossSwordShieldRepair(const InitArg& arg) : OnetimeStopASPlay(arg) {}

SiteBossSwordShieldRepair::~SiteBossSwordShieldRepair() = default;

bool SiteBossSwordShieldRepair::init_(sead::Heap* heap) {
    _4c = 0;
    return true;
}

// NON_MATCHING: branch layout of the Wait path; flag test is a byte test instead of the original word or
void SiteBossSwordShieldRepair::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = false;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        bool repaired = false;
        if (checkHpRate(boss, 0.5f) && !boss->_1558.isOn(0x180000)) {
            boss->_1558.set(0x100000);
            repaired = true;
        }

        if (boss->_14c8._30.isOnAll(6) ||
            (checkHpRate(boss, 0.5f) && !boss->_1558.isOn(0x80000) && !repaired && _4c <= 1)) {
            if (!boss->_14c8._30.isOnAll(6))
                ++_4c;
            _48 = true;
            playAS("Wait", false, 0, 0, -1.0f);
            setFinished();
            return;
        }

        _4c = 0;
        boss->_14c8._30.reset(4);
        act::SiteBoss::x_2(boss, mActor);
    }

    OnetimeStopASPlay::enter_(params);
    playAS("Shield_Repair", false, 3, 0, -1.0f);
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
