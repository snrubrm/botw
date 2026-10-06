#include "Game/AI/Query/queryCheckEquipment.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actActorSystem.h"

namespace uking::query {

CheckEquipment::CheckEquipment(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckEquipment::~CheckEquipment() = default;

int CheckEquipment::doQuery() {
    auto* actor_system = ksys::act::ActorSystem::instance();
    if (!actor_system)
        return 0;
    auto* player = actor_system->getPlayerLink();
    if (!player)
        return 0;

    sead::FixedSafeString<64> name;
    name.clear();
    player->m379(&name);
    if (name == mEquipItemName)
        return 1;
    name.clear();
    player->m380(&name);
    if (name == mEquipItemName)
        return 1;
    name.clear();
    player->m381(&name);
    return name == mEquipItemName;
}

void CheckEquipment::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "EquipItemName");
}

void CheckEquipment::loadParams() {
    getDynamicParam(&mEquipItemName, "EquipItemName");
}

}  // namespace uking::query
