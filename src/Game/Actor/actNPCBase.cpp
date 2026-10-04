#include "Game/Actor/actNPCBase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::act {

// NON_MATCHING: the original destructor only resets the vtables and calls Actor::~Actor (no member
// destructors)
NPCBase::~NPCBase() { ; }  // see GameDataFlagSelector::~GameDataFlagSelector() in upstream (commit 96101229)

bool NPCBase::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

void NPCBase::onPreDeleteStart_(PrepareArg& arg) {}

void NPCBase::preDelete2_(const PreDeleteArg& arg) {}

void NPCBase::calcMaybe() {}

void NPCBase::updatePositionMaybe() {}

void NPCBase::m66() {}

void NPCBase::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    if (mActorFlags2.isOn(ActorFlag2::_200))
        ksys::act::sub_7100EE9B68(this, setter);
}

}  // namespace uking::act
