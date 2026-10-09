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

void SetIsAffectWeak::m8() {
    auto* dmg = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr());
    if (!dmg)
        return;
    _30 = dmg->_216.isOn(8);
    dmg->_216.setDirect(*mIsAffect_s ? (dmg->_216.getDirect() | 8) :
                                         (dmg->_216.getDirect() & ~8));
}

void SetIsAffectWeak::m9() {
    if (auto* dmg = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr()))
        dmg->_216.setDirect(_30 ? (dmg->_216.getDirect() | 8) :
                                  (dmg->_216.getDirect() & ~8));
}

}  // namespace uking::behavior
