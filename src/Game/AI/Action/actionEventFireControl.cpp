#include "Game/AI/Action/actionEventFireControl.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EventFireControl::EventFireControl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventFireControl::~EventFireControl() = default;

bool EventFireControl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventFireControl::loadParams_() {
    getDynamicParam(&mReleaseFire_d, "ReleaseFire");
}

bool EventFireControl::oneShot_() {
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (*mReleaseFire_d)
            chemical->sub_7100D90B78();
        else
            chemical->sub_7100D90858(false, 2, false, true, false);
    }
    return true;
}

}  // namespace uking::action
