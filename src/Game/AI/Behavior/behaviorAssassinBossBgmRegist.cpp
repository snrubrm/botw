#include "Game/AI/Behavior/behaviorAssassinBossBgmRegist.h"
#include "Game/AI/aiUnk_7100FFDFDC.h"

namespace uking::behavior {

AssassinBossBgmRegist::AssassinBossBgmRegist(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AssassinBossBgmRegist::~AssassinBossBgmRegist() = default;

bool AssassinBossBgmRegist::m6(sead::Heap* heap) {
    return true;
}

void AssassinBossBgmRegist::m7() {}

void AssassinBossBgmRegist::m8() {
    if (auto* bgm = sub_7100FFDFDC())
        bgm->sub_7100FF61BC();
}

void AssassinBossBgmRegist::m9() {}

void AssassinBossBgmRegist::loadParams() {

}

}  // namespace uking::behavior
