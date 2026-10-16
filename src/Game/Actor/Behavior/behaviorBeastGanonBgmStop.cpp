#include "Game/Actor/Behavior/behaviorBeastGanonBgmStop.h"
#include "Game/Actor/aiUnk_7100FFDFDC.h"

namespace uking::behavior {

BeastGanonBgmStop::BeastGanonBgmStop(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

BeastGanonBgmStop::~BeastGanonBgmStop() = default;

bool BeastGanonBgmStop::init_(sead::Heap* heap) {
    return true;
}

void BeastGanonBgmStop::calc() {}

void BeastGanonBgmStop::enter() {
    if (auto* bgm = sub_7100FFE468())
        bgm->sub_71010101EC(0.0f);
}

void BeastGanonBgmStop::leave() {}

void BeastGanonBgmStop::loadParams() {

}

}  // namespace uking::behavior
