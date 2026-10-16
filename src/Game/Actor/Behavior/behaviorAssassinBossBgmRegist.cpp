#include "Game/Actor/Behavior/behaviorAssassinBossBgmRegist.h"
#include "Game/Actor/aiUnk_7100FFDFDC.h"

namespace uking::behavior {

AssassinBossBgmRegist::AssassinBossBgmRegist(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AssassinBossBgmRegist::~AssassinBossBgmRegist() = default;

bool AssassinBossBgmRegist::init_(sead::Heap* heap) {
    return true;
}

void AssassinBossBgmRegist::calc() {}

void AssassinBossBgmRegist::enter() {
    if (auto* bgm = sub_7100FFDFDC())
        bgm->sub_7100FF61BC();
}

void AssassinBossBgmRegist::leave() {}

void AssassinBossBgmRegist::loadParams() {

}

}  // namespace uking::behavior
