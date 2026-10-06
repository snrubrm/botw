#include "Game/AI/Behavior/behaviorBattleTensionUp.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

BattleTensionUp::BattleTensionUp(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void BattleTensionUp::m7() {}

void BattleTensionUp::m8() {
    if (!mActor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::Alive)) {
        if (auto* mgr = dmg::DamageInfoMgr::instance())
            mgr->get28().sub_710065CE14(mActor);
    }
}

void BattleTensionUp::m9() {
    if (auto* mgr = dmg::DamageInfoMgr::instance())
        mgr->get28().sub_710065CF08(mActor);
}

void BattleTensionUp::loadParams() {

}

}  // namespace uking::behavior
