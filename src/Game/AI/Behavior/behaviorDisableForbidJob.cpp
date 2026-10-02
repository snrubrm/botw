#include "Game/AI/Behavior/behaviorDisableForbidJob.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

DisableForbidJob::DisableForbidJob(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

DisableForbidJob::~DisableForbidJob() = default;

bool DisableForbidJob::m6(sead::Heap* heap) {
    return true;
}

void DisableForbidJob::m7() {}

void DisableForbidJob::loadParams() {

}

void DisableForbidJob::m8() {
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2d, true);
}

void DisableForbidJob::m9() {
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2d, false);
}

}  // namespace uking::behavior
