#include "Game/AI/AI/aiHorseRideShootingEnemyBattle.h"
#include <random/seadGlobalRandom.h>

namespace uking::ai {

HorseRideShootingEnemyBattle::HorseRideShootingEnemyBattle(const InitArg& arg)
    : ShootingEnemyBattle(arg) {}

HorseRideShootingEnemyBattle::~HorseRideShootingEnemyBattle() = default;

bool HorseRideShootingEnemyBattle::init_(sead::Heap* heap) {
    return ShootingEnemyBattle::init_(heap);
}

void HorseRideShootingEnemyBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootingEnemyBattle::enter_(params);
    _e8 = ksys::Timer(0.0f, 0.0f, 1.0f);
    _f4 = 0;
    _f8 = 0;
    _fc = sead::GlobalRandom::instance()->getU32(*mTrackTimeRand_s);
    _100 = sead::GlobalRandom::instance()->getU32(*mSlowTimeRand_s);
}

void HorseRideShootingEnemyBattle::leave_() {
    ShootingEnemyBattle::leave_();
}

void HorseRideShootingEnemyBattle::loadParams_() {
    ShootingEnemyBattle::loadParams_();
    getStaticParam(&mTrackTime_s, "TrackTime");
    getStaticParam(&mTrackTimeRand_s, "TrackTimeRand");
    getStaticParam(&mSlowTime_s, "SlowTime");
    getStaticParam(&mSlowTimeRand_s, "SlowTimeRand");
}

}  // namespace uking::ai
