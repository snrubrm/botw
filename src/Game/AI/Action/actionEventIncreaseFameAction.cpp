#include "Game/AI/Action/actionEventIncreaseFameAction.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

EventIncreaseFameAction::EventIncreaseFameAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool EventIncreaseFameAction::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    s32 value = 0;
    if (!gdm->getParamBypassPerm().get().getS32(&value, "FamouseValue"))
        return false;
    value += *mValue_d;
    return gdm->setS32(value, "FamouseValue");
}

void EventIncreaseFameAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
}

}  // namespace uking::action
