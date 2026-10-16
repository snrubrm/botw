#include "Game/Actor/Behavior/behaviorDisableForbidJob.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

DisableForbidJob::DisableForbidJob(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

DisableForbidJob::~DisableForbidJob() = default;

bool DisableForbidJob::init_(sead::Heap* heap) {
    return true;
}

void DisableForbidJob::calc() {}

void DisableForbidJob::loadParams() {

}

void DisableForbidJob::enter() {
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2d, true);
}

void DisableForbidJob::leave() {
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2d, false);
}

}  // namespace uking::behavior
