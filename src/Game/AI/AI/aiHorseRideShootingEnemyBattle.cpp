#include "Game/AI/AI/aiHorseRideShootingEnemyBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
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

void HorseRideShootingEnemyBattle::sub_7100443A58() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild(_f8, &pack);
}

void HorseRideShootingEnemyBattle::changeToChaseCommand() {
    _f4 = 0;
    _f8 = mChildIdx;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("追跡指令", &pack);
}

void HorseRideShootingEnemyBattle::changeToDecelerateCommand() {
    _f8 = mChildIdx;
    _f4 = 1;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("減速指令", &pack);
}

}  // namespace uking::ai
