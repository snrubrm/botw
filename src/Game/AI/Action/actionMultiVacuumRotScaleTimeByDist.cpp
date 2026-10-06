#include "Game/AI/Action/actionMultiVacuumRotScaleTimeByDist.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

MultiVacuumRotScaleTimeByDist::MultiVacuumRotScaleTimeByDist(const InitArg& arg)
    : MultiVacuumRotScaleTimeByDistWithTgt(arg) {}

MultiVacuumRotScaleTimeByDist::~MultiVacuumRotScaleTimeByDist() = default;

bool MultiVacuumRotScaleTimeByDist::init_(sead::Heap* heap) {
    return MultiVacuumRotScaleTimeByDistWithTgt::init_(heap);
}

void MultiVacuumRotScaleTimeByDist::enter_(ksys::act::ai::InlineParamPack* params) {
    MultiVacuumRotScaleTimeByDistWithTgt::enter_(params);
    const float dist = (mActor->getMtx().getTranslation() - *mTargetPos_d).length();
    if (dist < *mMaxTimeDist_s)
        _1b8 = dist * _1b8 / *mMaxTimeDist_s;
}

void MultiVacuumRotScaleTimeByDist::leave_() {
    MultiVacuumRotScaleTimeByDistWithTgt::leave_();
}

void MultiVacuumRotScaleTimeByDist::loadParams_() {
    MultiVacuumRotScaleTimeByDistWithTgt::loadParams_();
    getStaticParam(&mMaxTimeDist_s, "MaxTimeDist");
}

void MultiVacuumRotScaleTimeByDist::calc_() {
    MultiVacuumRotScaleTimeByDistWithTgt::calc_();
}

}  // namespace uking::action
