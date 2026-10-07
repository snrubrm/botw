#include "KingSystem/Event/evtEventFlowBinder.h"
#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Event/evtActorManager.h"
#include "KingSystem/Event/evtEventFlow.h"

namespace ksys::evt {

void EventActorBinder::bind(evfl::ActorBinding* binding, const evfl::ResActor* actor) {
    binding->SetUserData(mActors->sub_7100DA2A28(actor->name.Get()->data(),
                                              actor->secondary_name.Get()->data()));
    binding->SetInitialized(true);
}

void EventActionBinder::bind(evfl::ActorBinding::Action* binding, const evfl::ResAction* action,
                             const evfl::ResActor*, ActorBase* instance) {
    binding->user_data = instance->getActionByName(action);
    binding->handler = ActorManager::actionHandler;
}

void EventQueryBinder::bind(evfl::ActorBinding::Query* binding, const evfl::ResQuery* query,
                            const evfl::ResActor*, ActorBase* instance) {
    binding->user_data = instance->getQueryByRes(query);
    binding->handler = ActorManager::queryHandler;
}

}  // namespace ksys::evt
