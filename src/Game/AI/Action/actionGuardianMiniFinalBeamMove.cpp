#include "Game/AI/Action/actionGuardianMiniFinalBeamMove.h"

namespace uking::action {

GuardianMiniFinalBeamMove::GuardianMiniFinalBeamMove(const InitArg& arg) : GuardianBeamFire(arg) {}

GuardianMiniFinalBeamMove::~GuardianMiniFinalBeamMove() = default;

void GuardianMiniFinalBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianBeamFire::enter_(params);
    _80 = false;
}

void GuardianMiniFinalBeamMove::leave_() {
    sub_7100194A58();
    GuardianBeamFire::leave_();
}

void GuardianMiniFinalBeamMove::loadParams_() {
    GuardianBeamFire::loadParams_();
}

void GuardianMiniFinalBeamMove::calc_() {
    GuardianBeamFire::calc_();
    sub_7100194A58();
}

bool GuardianMiniFinalBeamMove::isFinished() const {
    return ActionBase::isFinished();
}

}  // namespace uking::action
