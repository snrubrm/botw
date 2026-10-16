#include "Game/Actor/Behavior/behaviorBattleTensionUp.h"
#include "Game/Actor/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

BattleTensionUp::BattleTensionUp(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void BattleTensionUp::calc() {}

void BattleTensionUp::enter() {
    if (!mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::Alive)) {
        if (auto* mgr = act::DamageInfoMgr::instance())
            mgr->get28().sub_710065CE14(mActor);
    }
}

void BattleTensionUp::leave() {
    if (auto* mgr = act::DamageInfoMgr::instance())
        mgr->get28().sub_710065CF08(mActor);
}

void BattleTensionUp::loadParams() {

}

}  // namespace uking::behavior
