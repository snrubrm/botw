#include "Game/AI/Query/queryCheckPlayerEquip.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::query {

CheckPlayerEquip::CheckPlayerEquip(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerEquip::~CheckPlayerEquip() = default;

int CheckPlayerEquip::doQuery() {
    if (auto* player = ksys::act::PlayerInfo::instance()->getPlayer()) {
        switch (*mPlayerEquipType) {
        case 0:
            return player->m268();
        case 1:
            return player->m269();
        case 2:
            return player->m270();
        }
    }
    return 0;
}

void CheckPlayerEquip::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "PlayerEquipType");
}

void CheckPlayerEquip::loadParams() {
    getDynamicParam(&mPlayerEquipType, "PlayerEquipType");
}

}  // namespace uking::query
