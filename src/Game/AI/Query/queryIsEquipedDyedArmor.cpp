#include "Game/AI/Query/queryIsEquipedDyedArmor.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::query {

IsEquipedDyedArmor::IsEquipedDyedArmor(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsEquipedDyedArmor::~IsEquipedDyedArmor() = default;

int IsEquipedDyedArmor::doQuery() {
    bool result;
    {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        result = accessor.isEquipedDyedArmor();
    }
    return result;
}

void IsEquipedDyedArmor::loadParams(const evfl::QueryArg& arg) {}

void IsEquipedDyedArmor::loadParams() {}

}  // namespace uking::query
