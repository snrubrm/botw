#include "Game/AI/Action/actionSiteBossLswordPostWarp.h"

namespace uking::action {

SiteBossLswordPostWarp::SiteBossLswordPostWarp(const InitArg& arg) : LastBossPostNormalWarp(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
SiteBossLswordPostWarp::~SiteBossLswordPostWarp() {
    ;
}

bool SiteBossLswordPostWarp::init_(sead::Heap* heap) {
    return LastBossPostNormalWarp::init_(heap);
}

void SiteBossLswordPostWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossPostNormalWarp::enter_(params);
}

void SiteBossLswordPostWarp::leave_() {
    LastBossPostNormalWarp::leave_();
}

void SiteBossLswordPostWarp::loadParams_() {
    LastBossPostNormalWarp::loadParams_();
    getStaticParam(&mCancelSleepPartsName_s, "CancelSleepPartsName");
}

void SiteBossLswordPostWarp::calc_() {
    LastBossPostNormalWarp::calc_();
}

}  // namespace uking::action
