#include "KingSystem/Event/evtEventMgrStruct3.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actInfoData.h"

namespace ksys::evt {

// 0x71012799c4
EventMgrStruct3A::EventMgrStruct3A() = default;

// 0x71012799d0
EventMgrStruct3A::~EventMgrStruct3A() = default;

// 0x71012799d4
void EventMgrStruct3A::assignToActor(act::Actor* actor) {
    mAssigned = true;
    mActor = actor;
    mHasUniqueName = act::InfoData::instance()->hasTag(actor->getName().cstr(), 0xcab53f3d);
    if (mHasUniqueName && !mActor->getUniqueName())
        mHasUniqueName = false;
}

}  // namespace ksys::evt
