#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

uking::dmg::DamageManager* sub_710072BA90(ksys::act::Actor* actor) {
    return sead::DynamicCast<uking::dmg::DamageManager>(actor->getDamageMgr());
}
