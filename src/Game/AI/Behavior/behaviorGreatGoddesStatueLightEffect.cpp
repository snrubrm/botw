#include "Game/AI/Behavior/behaviorGreatGoddesStatueLightEffect.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::behavior {

GreatGoddesStatueLightEffect::GreatGoddesStatueLightEffect(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
GreatGoddesStatueLightEffect::~GreatGoddesStatueLightEffect() {
    ;
}

bool GreatGoddesStatueLightEffect::m6(sead::Heap* heap) {
    return true;
}

void GreatGoddesStatueLightEffect::m8() {}

void GreatGoddesStatueLightEffect::m9() {}

void GreatGoddesStatueLightEffect::loadParams() {
    getStaticParam(&mFlagName_s, "FlagName");
}

void GreatGoddesStatueLightEffect::m7() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm)
        return;
    bool value = false;
    if (gdm->getParamBypassPerm().get().getBool(&value, mFlagName_s) && value)
        xlinkEventOn(mActor, 25, 1, false);
}

}  // namespace uking::behavior
