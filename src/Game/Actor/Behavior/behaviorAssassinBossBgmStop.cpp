#include "Game/Actor/Behavior/behaviorAssassinBossBgmStop.h"
#include "Game/Actor/aiUnk_7100FFDFDC.h"

namespace uking::behavior {

AssassinBossBgmStop::AssassinBossBgmStop(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AssassinBossBgmStop::~AssassinBossBgmStop() = default;

bool AssassinBossBgmStop::init_(sead::Heap* heap) {
    return true;
}

void AssassinBossBgmStop::calc() {}

void AssassinBossBgmStop::enter() {
    if (auto* bgm = sub_7100FFDFDC())
        bgm->sub_7100FF6220();
}

void AssassinBossBgmStop::leave() {}

void AssassinBossBgmStop::loadParams() {

}

}  // namespace uking::behavior
