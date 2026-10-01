#include "Game/AI/Action/actionGuard.h"

namespace uking::action {

Guard::Guard(const InitArg& arg) : TakeHitImpactForce(arg) {}

void Guard::enter_(ksys::act::ai::InlineParamPack* params) {
    TakeHitImpactForce::enter_(params);
}

void Guard::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mRotSubsAngRate_s, "RotSubsAngRate");
}

void Guard::calc_() {
    TakeHitImpactForce::calc_();
}

bool Guard::isChangeable() const {
    return true;
}

}  // namespace uking::action
