#include "Game/AI/Action/actionDrowningDeath.h"

namespace uking::action {

DrowningDeath::DrowningDeath(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DrowningDeath::~DrowningDeath() = default;

bool DrowningDeath::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DrowningDeath::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DrowningDeath::leave_() {
    _30.resetMotionType(_30.sub_710072ACF8(mActor));
}

void DrowningDeath::loadParams_() {
    getStaticParam(&mPosBaseRagdollRbName_s, "PosBaseRagdollRbName");
}

void DrowningDeath::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
