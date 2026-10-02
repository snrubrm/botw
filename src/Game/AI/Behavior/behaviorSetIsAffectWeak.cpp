#include "Game/AI/Behavior/behaviorSetIsAffectWeak.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SetIsAffectWeak::SetIsAffectWeak(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetIsAffectWeak::~SetIsAffectWeak() = default;

bool SetIsAffectWeak::m6(sead::Heap* heap) {
    return true;
}

void SetIsAffectWeak::m7() {}

void SetIsAffectWeak::loadParams() {
    getStaticParam(&mIsAffect_s, "IsAffect");
}

// NON_MATCHING: the original selects between the set and reset values (ours branches)
void SetIsAffectWeak::m8() {
    auto* dmg = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr());
    if (!dmg)
        return;
    _30 = dmg->_216.isOn(8);
    dmg->_216.change(8, *mIsAffect_s);
}

// NON_MATCHING: the original selects between the set and reset values (ours branches)
void SetIsAffectWeak::m9() {
    if (auto* dmg = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr()))
        dmg->_216.change(8, _30);
}

}  // namespace uking::behavior
