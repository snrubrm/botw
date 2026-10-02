#include "Game/AI/Behavior/behaviorDisableForbidJob.h"

namespace uking::behavior {

DisableForbidJob::DisableForbidJob(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

DisableForbidJob::~DisableForbidJob() = default;

bool DisableForbidJob::m6(sead::Heap* heap) {
    return true;
}

void DisableForbidJob::m7() {}

void DisableForbidJob::loadParams() {

}

}  // namespace uking::behavior
