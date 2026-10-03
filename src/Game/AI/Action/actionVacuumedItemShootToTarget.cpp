#include "Game/AI/Action/actionVacuumedItemShootToTarget.h"

namespace uking::action {

VacuumedItemShootToTarget::VacuumedItemShootToTarget(const InitArg& arg) : OnetimeStopASPlay(arg) {}

VacuumedItemShootToTarget::~VacuumedItemShootToTarget() = default;

bool VacuumedItemShootToTarget::init_(sead::Heap* heap) {
    return _48.sub_710073ECC0();
}

void VacuumedItemShootToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
    if (_48.sub_710073EF50(this))
        _48.mIsReuseBullet = *mIsReuseBullet_s;
    else
        setFailed();
}

void VacuumedItemShootToTarget::leave_() {
    OnetimeStopASPlay::leave_();
}

void VacuumedItemShootToTarget::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    _48.sub_710073ED20(this);
    getStaticParam(&mIsReuseBullet_s, "IsReuseBullet");
}

void VacuumedItemShootToTarget::calc_() {
    if (!isFinished() && !isFailed()) {
        OnetimeStopASPlay::calc_();
        if (_48.sub_710073FA54())
            m32();
    }
}

void VacuumedItemShootToTarget::m32() {
    _48.sub_710073F040();
}

}  // namespace uking::action
