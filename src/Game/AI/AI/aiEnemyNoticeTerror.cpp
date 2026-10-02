#include "Game/AI/AI/aiEnemyNoticeTerror.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/Actor/actUnk_71002dccbc.h"

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

void EnemyNoticeTerror::m36() {
    auto* unk = sub_71005D9D68(mActor);
    auto* link = sub_71005D9050(mActor);
    if ((link && *link == _60._0) || (unk && unk->sub_71002DC9E8(_60._0, 2, false))) {
        m35();
        return;
    }
    if (unk)
        unk->sub_71002DC628(_60._0, 2);
    sub_71003A7DD4();
}

bool EnemyNoticeTerror::m34(Unk* out) {
    out->_0.reset();
    out->_1c = 0;
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;
    auto* sensor = awareness->_260[2];
    if (!sensor || sensor->_8.size() < 1)
        return false;
    auto* entry = ksys::act::sub_7100D78E30(&sensor->_8, 0);
    if (!entry)
        return false;
    out->_0 = entry->_0.mLink;
    out->_10 = entry->_88;
    out->_1c |= 1;
    if (entry->_0.m5(3) || entry->_0.m5(4))
        out->_1c |= 2;
    return true;
}

}  // namespace uking::ai
