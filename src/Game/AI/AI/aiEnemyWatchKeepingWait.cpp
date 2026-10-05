#include "Game/AI/AI/aiEnemyWatchKeepingWait.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/System/Timer.h"

namespace uking::ai {

EnemyWatchKeepingWait::EnemyWatchKeepingWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyWatchKeepingWait::~EnemyWatchKeepingWait() = default;

bool EnemyWatchKeepingWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyWatchKeepingWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: The timer reload uses the member address instead of the retained pointer.
void EnemyWatchKeepingWait::calc_() {
    if (!_7e && isCurrentChild("待機")) {
        if (!_74 && _70 > 0) {
            ksys::Timer::update(&_68, -1.0f);
            if (_68 <= 0) {
                _74 = sead::GlobalRandom::instance()->getF32() * 100.0f < f32(_70);
                if (!_74)
                    _68 = f32(_70);
            }
        }
        if (_74) {
            _7e = true;
            _74 = false;
            _68 = f32(_6c);
        }
    }
    if (isCurrentChild("待機") && _78 > 0)
        ksys::Timer::update(&_78, -1.0f);
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("待機"))
            sub_71003C5F34();
        else
            changeToWait();
    } else if (child->isChangeable() && isCurrentChild("待機") && *mWaitTime_m > 0 &&
               sead::Mathf::abs(*mRotAngle_m) > 0) {
        ksys::Timer::update(&_38, -1.0f);
        if (_38 < 0) {
            sub_71003C5F34();
        } else if (_7e && _78 <= 0) {
            _7e = false;
            changeChild("サボり", nullptr);
        }
    }
}

void EnemyWatchKeepingWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyWatchKeepingWait::loadParams_() {
    getStaticParam(&mIdleCheckMin_s, "IdleCheckMin");
    getStaticParam(&mIdleCheckMax_s, "IdleCheckMax");
    getStaticParam(&mIdlePer_s, "IdlePer");
    getMapUnitParam(&mRotAngle_m, "RotAngle");
    getMapUnitParam(&mWaitTime_m, "WaitTime");
}

void EnemyWatchKeepingWait::changeToWait() {
    _38 = *mWaitTime_m;
    _78 = std::min(s32(*mWaitTime_m * 0.5f), 30);
    changeChild("待機", nullptr);
}

}  // namespace uking::ai
