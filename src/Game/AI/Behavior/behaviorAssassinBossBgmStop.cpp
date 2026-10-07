#include "Game/AI/Behavior/behaviorAssassinBossBgmStop.h"
#include "Game/AI/aiUnk_7100FFDFDC.h"

namespace uking::behavior {

AssassinBossBgmStop::AssassinBossBgmStop(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AssassinBossBgmStop::~AssassinBossBgmStop() = default;

bool AssassinBossBgmStop::m6(sead::Heap* heap) {
    return true;
}

void AssassinBossBgmStop::m7() {}

void AssassinBossBgmStop::m8() {
    if (auto* bgm = sub_7100FFDFDC())
        bgm->sub_7100FF6220();
}

void AssassinBossBgmStop::m9() {}

void AssassinBossBgmStop::loadParams() {

}

}  // namespace uking::behavior
