#include "Game/AI/Action/actionEventIncreaseRupeeAction.h"
#include "KingSystem/System/UIGlue.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

EventIncreaseRupeeAction::EventIncreaseRupeeAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

void EventIncreaseRupeeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* gdm = ksys::gdt::Manager::instance();
    ksys::ui::initRupeeCounter();
    gdm->incrementS32(*mValue_d, "CurrentRupee");
}

void EventIncreaseRupeeAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
}

void EventIncreaseRupeeAction::calc_() {
    if (ksys::ui::isRupeeCounterActive())
        return;
    setFinished();
}

}  // namespace uking::action
