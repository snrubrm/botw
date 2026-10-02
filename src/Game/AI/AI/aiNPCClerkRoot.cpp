#include "Game/AI/AI/aiNPCClerkRoot.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

NPCClerkRoot::NPCClerkRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCClerkRoot::~NPCClerkRoot() = default;

bool NPCClerkRoot::init_(sead::Heap* heap) {
    if (!NPCRoot::init_(heap))
        return false;
    _240.initWithName(mActor, mActor->getName(), "ClerkAsk");
    return true;
}

void NPCClerkRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCRoot::enter_(params);
}

void NPCClerkRoot::leave_() {
    NPCRoot::leave_();
}

void NPCClerkRoot::onPreDelete() {
    NPCRoot::onPreDelete();
    if (_240.mEventFlow)
        _240.unloadEvent();
}

void NPCClerkRoot::loadParams_() {
    NPCRoot::loadParams_();
}

}  // namespace uking::ai
