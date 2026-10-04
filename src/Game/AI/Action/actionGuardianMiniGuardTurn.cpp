#include "Game/AI/Action/actionGuardianMiniGuardTurn.h"

namespace uking::action {

GuardianMiniGuardTurn::GuardianMiniGuardTurn(const InitArg& arg) : Turn(arg) {}

GuardianMiniGuardTurn::~GuardianMiniGuardTurn() = default;

void GuardianMiniGuardTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    Turn::enter_(params);
    sub_71001966C4();
}

void GuardianMiniGuardTurn::loadParams_() {
    TurnBase::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
