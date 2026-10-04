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

// 0x7100da2e84
ActorBase* EventActorSet::sub_7100DA2E84(act::BaseProc* proc) {
    for (s32 i = 0; i < mActors.size(); ++i) {
        auto* actor = mActors.at(i);
        if (actor->mLink.hasProcById(proc))
            return actor;
    }
    return nullptr;
}

// 0x7100da288c
void EventActorSet::x_1() {
    for (s32 i = 0; i < mActors.size(); ++i)
        mActors.at(i)->sub_7100DAB548();
}

// 0x7100da2700
void EventActorSet::sub_7100DA2700(bool a1, bool a2) {
    for (s32 i = 0; i < mActors.size(); ++i)
        mActors(i)->m5(a1, a2);
    _18 = 2;
    _44 = 0;
}

// 0x7100da3878
void EventActorSet::x_0() {
    for (s32 i = 0; i < mActors.size(); ++i)
        mActors.at(i)->sub_7100DAC578();
}

// 0x7100da3624
bool EventActorSet::x_4() {
    for (s32 i = 0; i < mActors.size(); ++i) {
        if (!mActors.at(i)->x_0())
            return false;
    }
    return true;
}

}  // namespace ksys::evt
