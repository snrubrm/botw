#include "Game/Actor/actNPCBase.h"

namespace uking::act {

// NON_MATCHING: the original destructor only resets the vtables and calls Actor::~Actor (no member
// destructors)
NPCBase::~NPCBase() = default;

bool NPCBase::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

void NPCBase::onPreDeleteStart_(PrepareArg& arg) {}

void NPCBase::preDelete2_(const PreDeleteArg& arg) {}

void NPCBase::calcMaybe() {}

void NPCBase::updatePositionMaybe() {}

void NPCBase::m66() {}

}  // namespace uking::act
