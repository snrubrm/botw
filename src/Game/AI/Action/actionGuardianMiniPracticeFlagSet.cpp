#include "Game/AI/Action/actionGuardianMiniPracticeFlagSet.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

GuardianMiniPracticeFlagSet::GuardianMiniPracticeFlagSet(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GuardianMiniPracticeFlagSet::~GuardianMiniPracticeFlagSet() = default;

bool GuardianMiniPracticeFlagSet::init_(sead::Heap* heap) {
    *mGuardianMiniPracticeState_a = 4;
    return true;
}

void GuardianMiniPracticeFlagSet::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GuardianMiniPracticeFlagSet::leave_() {
    switch (*mGuardianMiniPracticeState_a) {
    case 0:
        ksys::gdt::setFlag_ClearTutorial_SpinAttack(true);
        break;
    case 1:
        ksys::gdt::setFlag_ClearTutorial_GuardJust(true);
        break;
    case 2:
        ksys::gdt::setFlag_ClearTutorial_BackStep(true);
        break;
    case 3:
        ksys::gdt::setFlag_ClearTutorial_SideStep(true);
        break;
    default:
        break;
    }
}

void GuardianMiniPracticeFlagSet::loadParams_() {
    getAITreeVariable(&mGuardianMiniPracticeState_a, "GuardianMiniPracticeState");
}

void GuardianMiniPracticeFlagSet::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
