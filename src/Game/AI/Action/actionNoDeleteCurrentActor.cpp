#include "Game/AI/Action/actionNoDeleteCurrentActor.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

NoDeleteCurrentActor::NoDeleteCurrentActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NoDeleteCurrentActor::~NoDeleteCurrentActor() = default;

bool NoDeleteCurrentActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool NoDeleteCurrentActor::oneShot_() {
    if (auto* event_mgr = ksys::evt::Manager::instance())
        event_mgr->setNoDeleteCurrentActor(true);
    return true;
}

void NoDeleteCurrentActor::loadParams_() {}

}  // namespace uking::action
