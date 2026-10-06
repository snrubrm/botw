#include "Game/AI/Query/queryCheckPlayerWeaponFired.h"
#include <evfl/Query.h>
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::query {

CheckPlayerWeaponFired::CheckPlayerWeaponFired(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPlayerWeaponFired::~CheckPlayerWeaponFired() = default;

// NON_MATCHING: the original compares the three fire types one by one (2, 1, 0) instead of a range test for 0 / 1.
int CheckPlayerWeaponFired::doQuery() {
    auto* weapon = ksys::act::ActorSystem::instance()->getPlayerLink()->m273();
    if (!weapon)
        return 0;
    auto* chemical = weapon->getChemicalStuff();
    if (!chemical)
        return 0;
    switch (*mCheckFireType) {
    case 0:
    case 1:
        return chemical->_c0 == 2;
    case 2:
        if (chemical->_c0 == 2)
            return (chemical->_c >> 20) & 1;
        return 0;
    default:
        return 0;
    }
}

void CheckPlayerWeaponFired::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CheckFireType");
}

void CheckPlayerWeaponFired::loadParams() {
    getDynamicParam(&mCheckFireType, "CheckFireType");
}

}  // namespace uking::query
