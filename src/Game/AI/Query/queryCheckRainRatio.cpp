#include "Game/AI/Query/queryCheckRainRatio.h"
#include <evfl/Query.h>
#include "KingSystem/World/worldManager.h"

namespace uking::query {

CheckRainRatio::CheckRainRatio(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckRainRatio::~CheckRainRatio() = default;

int CheckRainRatio::doQuery() {
    if (auto* manager = ksys::world::Manager::instance()) {
        if (auto* weather = manager->getWeatherMgr())
            return weather->_2dc >= *mRainRatio;
    }
    return 0;
}

void CheckRainRatio::loadParams(const evfl::QueryArg& arg) {
    loadFloat(arg.param_accessor, "RainRatio");
}

void CheckRainRatio::loadParams() {
    getDynamicParam(&mRainRatio, "RainRatio");
}

}  // namespace uking::query
