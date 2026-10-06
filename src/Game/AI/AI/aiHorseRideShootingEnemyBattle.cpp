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

// NON_MATCHING: load scheduling of the time limit sum (the original loads both parameter pointers first and the timer
// value after the int to float conversion)
void HorseRideShootingEnemyBattle::calc_() {
    auto* child = getCurrentChild();

    if (!sub_71005D90E0(mActor) && *mSlowTime_s > 0) {
        _e8.update();
        const s32 time = _fc + *mTrackTime_s + *mSlowTime_s + _100;
        if (_e8.value > time) {
            _e8.rate = 1.0f;
            _e8.value = _e8.previous_value = _e8.value - time;
        }
    }

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("追跡指令") || isCurrentChild("減速指令")) {
            sub_7100443A58();
            return;
        }
    } else if (child->isChangeable()) {
        if (sub_71005D90E0(mActor)) {
            if (_f4 != 0) {
                _e8.value = 0.0f;
                _e8.previous_value = 0.0f;
                _e8.rate = 1.0f;
                changeToChaseCommand();
                return;
            }
        } else if (*mSlowTime_s > 0) {
            if (_e8.value >= f32(_fc + *mTrackTime_s)) {
                if (_f4 != 1) {
                    changeToDecelerateCommand();
                    return;
                }
            } else if (_f4 != 0) {
                changeToChaseCommand();
                return;
            }
        }
    }

    ShootingEnemyBattle::calc_();
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
