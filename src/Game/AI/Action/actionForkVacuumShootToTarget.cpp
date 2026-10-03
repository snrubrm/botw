#include "Game/AI/Action/actionForkVacuumShootToTarget.h"

namespace uking::action {

ForkVacuumShootToTarget::ForkVacuumShootToTarget(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkVacuumShootToTarget::~ForkVacuumShootToTarget() = default;

bool ForkVacuumShootToTarget::init_(sead::Heap* heap) {
    return _20.sub_710073ECC0();
}

void ForkVacuumShootToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    if (_20.sub_710073EF50(this))
        _20.mIsReuseBullet = *mIsReuseBullet_s;
    else
        setFailed();
}

void ForkVacuumShootToTarget::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkVacuumShootToTarget::loadParams_() {
    _20.sub_710073ED20(this);
    getStaticParam(&mIsReuseBullet_s, "IsReuseBullet");
}

void ForkVacuumShootToTarget::calc_() {
    if (!isFinished() && !isFailed()) {
        if (_20.sub_710073FA54())
            m32();
    }
}

void ForkVacuumShootToTarget::m32() {
    _20.sub_710073F040();
}

}  // namespace uking::action
