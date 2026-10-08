#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace ksys::evt {

// 0x71008a9380
void Actor::m12() {
    ActorBase::m12();
    auto* actor = sead::DynamicCast<act::Actor>(mLink.getProc(nullptr));
    if (!actor)
        return;
    auto* ride = actor->getPlayerRideInfo();
    if (!ride)
        return;
    act::ActorConstDataAccess accessor;
    if (act::acquireActor(&ride->_18, &accessor))
        accessor.wakeUp(act::BaseProc::SleepWakeReason::_0);
}

// 0x71008a8b78
Actor::Actor(ActorBinding* binding, EventActorSet* set, sead::Heap* heap) : ActorBase(binding, set, heap) {}

// D1 0x71008a8bac, D0 0x71008a8e68
Actor::~Actor() {
    sub_71008A8BE0();
}

// 0x71008a8ea4
bool Actor::m4() {
    if (!ActorBase::m4())
        return false;
    if ((_1cc & 0x10) == 0 && mName.isEqual("GameROMPlayer")) {
        if ((_1cc & 8) == 0 && EventSystem::instance()->x_1(_108))
            _1cc |= 8;
        if (EventSystem::instance()->x_0(_108))
            return false;
        _1cc &= ~8;
    }
    _1cc |= 0x10;
    return true;
}

}  // namespace ksys::evt
