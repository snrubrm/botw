#include "Game/AI/AI/aiEnemyNoticeTerror.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

namespace uking::ai {

EnemyNoticeTerror::EnemyNoticeTerror(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyNoticeTerror::~EnemyNoticeTerror() = default;

bool EnemyNoticeTerror::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original also copy-constructs a temporary Unk from _80 (BaseProcLink() + operator=, flags
// default-initialized first) and destroys it right after the assignment; its source is unknown.
void EnemyNoticeTerror::enter_(ksys::act::ai::InlineParamPack* params) {
    m34(&_60);
    _80 = _60;

    const int wait_time = *mWaitTime_s;
    const int wait_time_max = wait_time * 1.1f;
    _a4 = sead::Mathi::min(wait_time, wait_time_max);
    _a8 = sead::Mathi::max(wait_time, wait_time_max);
    int time = _a4;
    if (_a8 != _a4)
        time = sead::GlobalRandom::instance()->getS32Range(_a4, _a8);
    _a0 = time;
    m36();
}

void EnemyNoticeTerror::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyNoticeTerror::loadParams_() {
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mNoWarnDist_s, "NoWarnDist");
    getStaticParam(&mNoWarnHeightMin_s, "NoWarnHeightMin");
    getStaticParam(&mNoWarnHeightMax_s, "NoWarnHeightMax");
    getStaticParam(&mNoTerrorDist_s, "NoTerrorDist");
}

}  // namespace uking::ai
