#include "Game/AI/Action/actionLastBossRandomHighWarp.h"

namespace uking::action {

LastBossRandomHighWarp::LastBossRandomHighWarp(const InitArg& arg) : LastBossNormalWarp(arg) {}

LastBossRandomHighWarp::~LastBossRandomHighWarp() = default;

bool LastBossRandomHighWarp::init_(sead::Heap* heap) {
    if (!LastBossNormalWarp::init_(heap))
        return false;
    _11c = 0;
    return true;
}

void LastBossRandomHighWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossNormalWarp::enter_(params);
}

void LastBossRandomHighWarp::leave_() {
    LastBossNormalWarp::leave_();
}

void LastBossRandomHighWarp::loadParams_() {
    LastBossNormalWarp::loadParams_();
    getStaticParam(&mHighPosWarpRate_s, "HighPosWarpRate");
    getStaticParam(&mRandomRate_s, "RandomRate");
    getStaticParam(&mHighOffsetY_s, "HighOffsetY");
    getStaticParam(&mLifeCondition_s, "LifeCondition");
}

void LastBossRandomHighWarp::calc_() {
    LastBossNormalWarp::calc_();
}

bool LastBossRandomHighWarp::m32() {
    if (_118)
        return false;
    return *mIsWarpAtGround_s;
}

// NON_MATCHING: register choice of the two member addresses of the select (x9/x10 swapped)
float LastBossRandomHighWarp::m33() {
    return *(_118 == 0 ? mOffsetY_s : mHighOffsetY_s);
}

}  // namespace uking::action
