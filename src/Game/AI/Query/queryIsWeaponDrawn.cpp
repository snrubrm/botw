#include "Game/AI/Query/queryIsWeaponDrawn.h"
#include <evfl/Query.h>
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::query {

IsWeaponDrawn::IsWeaponDrawn(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsWeaponDrawn::~IsWeaponDrawn() = default;

int IsWeaponDrawn::doQuery() {
    if (auto* npc = sead::DynamicCast<act::NPC>(mActor))
        return !npc->getWeapons()->mWeapons[0]._10;
    return 0;
}

void IsWeaponDrawn::loadParams(const evfl::QueryArg& arg) {}

void IsWeaponDrawn::loadParams() {}

}  // namespace uking::query
