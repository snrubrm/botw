#include "Game/AI/Action/actionTumble.h"
#include "Game/Damage/dmgDamageCallback.h"

namespace uking::action {

Tumble::Tumble(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Tumble::~Tumble() = default;

void Tumble::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Tumble::leave_() {
    sub_71005DA114(mActor, &_68);
}

void Tumble::loadParams_() {}

bool Tumble::handleMessage_(const ksys::Message* message) {
    return true;
}

void Tumble::calc_() {
    ksys::act::ai::Action::calc_();
}

bool Tumble::isChangeable() const {
    return false;
}

}  // namespace uking::action
