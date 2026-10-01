#include "Game/AI/Action/actionLastBossJustGuard.h"

namespace uking::action {

LastBossJustGuard::LastBossJustGuard(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossJustGuard::~LastBossJustGuard() = default;

bool LastBossJustGuard::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossJustGuard::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("GuardJust", false, 0, 0, -1.0f);
}

void LastBossJustGuard::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossJustGuard::loadParams_() {}

void LastBossJustGuard::calc_() {
    ksys::act::ai::Action::calc_();
}

bool LastBossJustGuard::isChangeable() const {
    return true;
}

}  // namespace uking::action
