#include "Game/AI/Query/queryIsIgnitionByArrowFire.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::query {

IsIgnitionByArrowFire::IsIgnitionByArrowFire(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsIgnitionByArrowFire::~IsIgnitionByArrowFire() = default;

int IsIgnitionByArrowFire::doQuery() {
    if (auto* chemical = mActor->getChemicalStuff()) {
        if (chemical->_c & 0x400000)
            return 1;
    }
    return 0;
}

void IsIgnitionByArrowFire::loadParams(const evfl::QueryArg& arg) {}

void IsIgnitionByArrowFire::loadParams() {}

}  // namespace uking::query
