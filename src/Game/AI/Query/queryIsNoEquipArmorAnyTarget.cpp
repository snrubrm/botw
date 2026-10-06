#include "Game/AI/Query/queryIsNoEquipArmorAnyTarget.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::query {

IsNoEquipArmorAnyTarget::IsNoEquipArmorAnyTarget(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsNoEquipArmorAnyTarget::~IsNoEquipArmorAnyTarget() = default;

int IsNoEquipArmorAnyTarget::doQuery() {
    bool result;
    {
        ksys::act::acc::PlayerBase accessor;
        accessor.getPlayerFromPlayerInfo();
        result = accessor.m280();
    }
    return result;
}

void IsNoEquipArmorAnyTarget::loadParams(const evfl::QueryArg& arg) {}

void IsNoEquipArmorAnyTarget::loadParams() {}

}  // namespace uking::query
