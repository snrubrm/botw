#include "Game/AI/Action/actionBeeDamaged.h"

namespace uking::action {

BeeDamaged::BeeDamaged(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeeDamaged::~BeeDamaged() = default;

bool BeeDamaged::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BeeDamaged::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BeeDamaged::leave_() {
    ksys::act::ai::Action::leave_();
}

void BeeDamaged::loadParams_() {
    getStaticParam(&mParams.mTime_s, "Time");
    getStaticParam(&mParams.mSubActorSpeed_s, "SubActorSpeed");
    getStaticParam(&mParams.mAddYSpeed_s, "AddYSpeed");
}

void BeeDamaged::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
