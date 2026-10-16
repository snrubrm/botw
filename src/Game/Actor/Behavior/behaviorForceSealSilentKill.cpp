#include "Game/Actor/Behavior/behaviorForceSealSilentKill.h"

namespace uking::behavior {

ForceSealSilentKill::ForceSealSilentKill(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

ForceSealSilentKill::~ForceSealSilentKill() = default;

bool ForceSealSilentKill::init_(sead::Heap* heap) {
    return true;
}

void ForceSealSilentKill::calc() {}

void ForceSealSilentKill::loadParams() {
    getAITreeVariable(&mForceSealSilentKillCount_a, "ForceSealSilentKillCount");
}

void ForceSealSilentKill::enter() {
    ++*mForceSealSilentKillCount_a;
}

void ForceSealSilentKill::leave() {
    --*mForceSealSilentKillCount_a;
}

}  // namespace uking::behavior
