#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

uking::dmg::DamageManager* sub_710072BA90(ksys::act::Actor* actor) {
    return sead::DynamicCast<uking::dmg::DamageManager>(actor->getDamageMgr());
}

void sub_710072BB28(ksys::act::Actor* actor) {
    ksys::act::disableAllAttClients(actor);
    sub_71007A397C(actor);
}
