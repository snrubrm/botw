#include "Game/AI/AI/aiRemainsFireBattleStepSelector.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

RemainsFireBattleStepSelector::RemainsFireBattleStepSelector(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RemainsFireBattleStepSelector::~RemainsFireBattleStepSelector() = default;

bool RemainsFireBattleStepSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsFireBattleStepSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool attack1 = ksys::gdt::getFlag_Fire_Relic_Battle1stAttack();
    const bool attack2 = ksys::gdt::getFlag_Fire_Relic_Battle2ndAttack();
    const bool attack3 = ksys::gdt::getFlag_Fire_Relic_Battle3rdAttack();
    _3c = _38;
    int step = attack1;
    if (attack2)
        step = 2;
    if (attack3)
        step = 3;
    _38 = step;

    switch (step) {
    case 0:
        changeChild("1st");
        break;
    case 1:
        changeChild("2nd");
        break;
    case 2:
        changeChild("3rd");
        break;
    default:
        changeChild("Idle");
        break;
    }
}

bool RemainsFireBattleStepSelector::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::Ai::reenter_(other, true))
        return false;

    auto* other_selector = sead::DynamicCast<RemainsFireBattleStepSelector>(other);
    if (!other_selector)
        return false;

    _38 = other_selector->_38;
    _3c = other_selector->_3c;
    return true;
}

void RemainsFireBattleStepSelector::calc_() {
    const bool attack1 = ksys::gdt::getFlag_Fire_Relic_Battle1stAttack();
    const bool attack2 = ksys::gdt::getFlag_Fire_Relic_Battle2ndAttack();
    const bool attack3 = ksys::gdt::getFlag_Fire_Relic_Battle3rdAttack();
    const int prev_step = _38;
    int step = attack1;
    if (attack2)
        step = 2;
    if (attack3)
        step = 3;
    _3c = prev_step;
    _38 = step;
    if (prev_step == step)
        return;

    switch (step) {
    case 0:
        changeChild("1st");
        break;
    case 1:
        changeChild("2nd");
        break;
    case 2:
        changeChild("3rd");
        break;
    default:
        changeChild("Idle");
        break;
    }
}

void RemainsFireBattleStepSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsFireBattleStepSelector::loadParams_() {}

}  // namespace uking::ai
