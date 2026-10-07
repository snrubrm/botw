#include "Game/AI/Behavior/behaviorBeastGanonBgmStop.h"
#include "Game/AI/aiUnk_7100FFDFDC.h"

namespace uking::behavior {

BeastGanonBgmStop::BeastGanonBgmStop(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

BeastGanonBgmStop::~BeastGanonBgmStop() = default;

bool BeastGanonBgmStop::m6(sead::Heap* heap) {
    return true;
}

void BeastGanonBgmStop::m7() {}

void BeastGanonBgmStop::m8() {
    if (auto* bgm = sub_7100FFE468())
        bgm->sub_71010101EC(0.0f);
}

void BeastGanonBgmStop::m9() {}

void BeastGanonBgmStop::loadParams() {

}

}  // namespace uking::behavior
