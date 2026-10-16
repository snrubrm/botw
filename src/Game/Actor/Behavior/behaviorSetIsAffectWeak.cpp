#include "Game/Actor/Behavior/behaviorSetIsAffectWeak.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

SetIsAffectWeak::SetIsAffectWeak(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetIsAffectWeak::~SetIsAffectWeak() = default;

bool SetIsAffectWeak::init_(sead::Heap* heap) {
    return true;
}

void SetIsAffectWeak::calc() {}

void SetIsAffectWeak::loadParams() {
    getStaticParam(&mIsAffect_s, "IsAffect");
}

void SetIsAffectWeak::enter() {
    auto* dmg = sead::DynamicCast<uking::act::DamageManager>(mActor->getDamageMgr());
    if (!dmg)
        return;
    _30 = dmg->_216.isOn(8);
    dmg->_216.setDirect(*mIsAffect_s ? (dmg->_216.getDirect() | 8) :
                                         (dmg->_216.getDirect() & ~8));
}

void SetIsAffectWeak::leave() {
    if (auto* dmg = sead::DynamicCast<uking::act::DamageManager>(mActor->getDamageMgr()))
        dmg->_216.setDirect(_30 ? (dmg->_216.getDirect() | 8) :
                                  (dmg->_216.getDirect() & ~8));
}

}  // namespace uking::behavior
