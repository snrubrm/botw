#include "Game/AI/Behavior/behaviorAssassinBossBgmControl.h"
#include "Game/AI/aiUnk_7100FFDFDC.h"

namespace uking::behavior {

AssassinBossBgmControl::AssassinBossBgmControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AssassinBossBgmControl::~AssassinBossBgmControl() = default;

bool AssassinBossBgmControl::m6(sead::Heap* heap) {
    return true;
}

void AssassinBossBgmControl::m7() {}

void AssassinBossBgmControl::m8() {
    if (auto* bgm = sub_7100FFDFDC()) {
        bgm->sub_7100FF61BC();
        bgm->sub_7100FF61C0();
    }
}

void AssassinBossBgmControl::m9() {}

void AssassinBossBgmControl::loadParams() {

}

}  // namespace uking::behavior
