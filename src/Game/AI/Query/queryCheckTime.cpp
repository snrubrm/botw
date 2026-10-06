#include "Game/AI/Query/queryCheckTime.h"
#include <evfl/Query.h>
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldTimeMgr.h"

namespace uking::query {

CheckTime::CheckTime(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckTime::~CheckTime() = default;

int CheckTime::doQuery() {
    auto* manager = ksys::world::Manager::instance();
    if (!manager)
        return 0;

    const int hour = *mHour;
    const int minute = *mMinute;
    if (mConditionType == "ge") {
        if (hour < manager->getTimeMgr()->getHour())
            return 1;
        if (hour != manager->getTimeMgr()->getHour())
            return 0;
        return minute <= manager->getTimeMgr()->getMinute();
    }
    if (mConditionType == "le") {
        if (manager->getTimeMgr()->getHour() < hour)
            return 1;
        if (manager->getTimeMgr()->getHour() != hour)
            return 0;
        return manager->getTimeMgr()->getMinute() <= minute;
    }
    return 0;
}

void CheckTime::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Hour");
    loadInt(arg.param_accessor, "Minute");
    loadString(arg.param_accessor, "ConditionType");
}

void CheckTime::loadParams() {
    getDynamicParam(&mHour, "Hour");
    getDynamicParam(&mMinute, "Minute");
    getDynamicParam(&mConditionType, "ConditionType");
}

}  // namespace uking::query
