#include "Game/AI/Action/actionSiteBossLswordTornadoEnd.h"

namespace uking::action {

SiteBossLswordTornadoEnd::SiteBossLswordTornadoEnd(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossLswordTornadoEnd::~SiteBossLswordTornadoEnd() = default;

bool SiteBossLswordTornadoEnd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordTornadoEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossLswordTornadoEnd::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossLswordTornadoEnd::loadParams_() {
    getStaticParam(&mIsUseTornadoAttack_s, "IsUseTornadoAttack");
    getDynamicParam(&mAttackActor_d, "AttackActor");
}

void SiteBossLswordTornadoEnd::calc_() {
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
