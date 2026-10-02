#include "Game/AI/Behavior/behaviorForceSealSilentKill.h"

namespace uking::behavior {

ForceSealSilentKill::ForceSealSilentKill(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ForceSealSilentKill::~ForceSealSilentKill() = default;

bool ForceSealSilentKill::m6(sead::Heap* heap) {
    return true;
}

void ForceSealSilentKill::m7() {}

void ForceSealSilentKill::loadParams() {
    getAITreeVariable(&mForceSealSilentKillCount_a, "ForceSealSilentKillCount");
}

void ForceSealSilentKill::m8() {
    ++*mForceSealSilentKillCount_a;
}

void ForceSealSilentKill::m9() {
    --*mForceSealSilentKillCount_a;
}

}  // namespace uking::behavior
