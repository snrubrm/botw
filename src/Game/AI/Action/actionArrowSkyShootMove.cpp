#include "Game/AI/Action/actionArrowSkyShootMove.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ArrowSkyShootMove::ArrowSkyShootMove(const InitArg& arg) : ArrowShootMove(arg) {}

ArrowSkyShootMove::~ArrowSkyShootMove() = default;

void ArrowSkyShootMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowShootMove::enter_(params);
    _170 = 0;
}

void ArrowSkyShootMove::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    ArrowShootMove::leave_();
}

void ArrowSkyShootMove::loadParams_() {
    ArrowShootMove::loadParams_();
    getStaticParam(&mInterval_s, "Interval");
    getStaticParam(&mSkyShootDist_s, "SkyShootDist");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getDynamicParam(&mPosOffset_d, "PosOffset");
}

void ArrowSkyShootMove::calc_() {
    ArrowShootMove::calc_();
}

bool ArrowSkyShootMove::m34(sead::Vector3f* pos, bool* a, bool* b, sead::Vector3f* vel) {
    if (_170 == 3)
        return ArrowShootMove::m34(pos, a, b, vel);
    return false;
}

bool ArrowSkyShootMove::m40() {
    if (_170 != 3)
        return false;
    sead::Vector3f diff = _180;
    diff -= mActor->getMtx().getTranslation();
    return diff.length() >= *mAtRange_d * 2;
}

}  // namespace uking::action
