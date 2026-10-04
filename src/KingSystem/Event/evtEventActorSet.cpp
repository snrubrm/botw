#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Event/evtEventFlow.h"

namespace ksys::evt {

// 0x7100da283c
void EventActorSet::callActorStuff() {
    for (s32 i = 0; i < mActors.size(); ++i)
        mActors(i)->m8();
}

// 0x7100da28e8
void EventActorSet::playActors() {
    for (s32 i = 0; i < mActors.size(); ++i)
        mActors(i)->play();
}

// 0x7100da2c18
ActorBase* EventActorSet::getActorByPointer(act::BaseProc* proc) const {
    for (s32 i = 0; i < mActors.size(); ++i) {
        auto* actor = mActors.at(i);
        if (actor->mLink.hasProcById(proc))
            return actor;
    }
    return nullptr;
}

}  // namespace ksys::evt
