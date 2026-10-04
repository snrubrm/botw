#include "Game/AI/Action/actionEventAppearRupeeAction.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::action {

EventAppearRupeeAction::EventAppearRupeeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void EventAppearRupeeAction::loadParams_() {
    getDynamicParam(&mIsVisible_d, "IsVisible");
}

bool EventAppearRupeeAction::oneShot_() {
    if (*mIsVisible_d)
        ksys::ui::sub_7100EDC334();
    else
        ksys::ui::sub_7100EDC2E4(false);
    return true;
}

}  // namespace uking::action
