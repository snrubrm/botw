#include "Game/Actor/Behavior/behaviorAssassinBossBgmControl.h"
#include "Game/Actor/aiUnk_7100FFDFDC.h"

namespace uking::behavior {

AssassinBossBgmControl::AssassinBossBgmControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AssassinBossBgmControl::~AssassinBossBgmControl() = default;

bool AssassinBossBgmControl::init_(sead::Heap* heap) {
    return true;
}

void AssassinBossBgmControl::calc() {}

void AssassinBossBgmControl::enter() {
    if (auto* bgm = sub_7100FFDFDC()) {
        bgm->sub_7100FF61BC();
        bgm->sub_7100FF61C0();
    }
}

void AssassinBossBgmControl::leave() {}

void AssassinBossBgmControl::loadParams() {

}

}  // namespace uking::behavior
