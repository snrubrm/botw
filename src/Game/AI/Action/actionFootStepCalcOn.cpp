#include "Game/AI/Action/actionFootStepCalcOn.h"

namespace uking::action {

FootStepCalcOn::FootStepCalcOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FootStepCalcOn::~FootStepCalcOn() = default;

bool FootStepCalcOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FootStepCalcOn::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100DA1A0C(true);
}

void FootStepCalcOn::leave_() {
    sub_7100DA1A0C(false);
}

void FootStepCalcOn::loadParams_() {
    getDynamicParam(&mActor_d, "Actor");
    getDynamicParam(&mInstanceName_d, "InstanceName");
}

void FootStepCalcOn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
