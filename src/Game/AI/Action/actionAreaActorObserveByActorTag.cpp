#include "Game/AI/Action/actionAreaActorObserveByActorTag.h"
#include <codec/seadHashCRC32.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

AreaActorObserveByActorTag::AreaActorObserveByActorTag(const InitArg& arg)
    : AreaActorObserve(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
AreaActorObserveByActorTag::~AreaActorObserveByActorTag() {
    ;
}

bool AreaActorObserveByActorTag::init_(sead::Heap* heap) {
    _60 = sead::HashCRC32::calcStringHash(mActorTag_m.cstr() ? mActorTag_m.cstr() : "");
    return AreaActorObserve::init_(heap);
}

void AreaActorObserveByActorTag::m9() {
    _60 = sead::HashCRC32::calcStringHash(mActorTag_m.cstr() ? mActorTag_m.cstr() : "");
}

void AreaActorObserveByActorTag::m32() {
    getMapUnitParam(&mActorTag_m, "ActorTag");
}

bool AreaActorObserveByActorTag::m37(const ksys::act::ActorConstDataAccess& accessor) {
    return accessor.hasTag(_60);
}

}  // namespace uking::action
