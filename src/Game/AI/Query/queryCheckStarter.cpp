#include "Game/AI/Query/queryCheckStarter.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::query {

CheckStarter::CheckStarter(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckStarter::~CheckStarter() = default;

int CheckStarter::doQuery() {
    auto* starter = ksys::evt::Manager::instance()->getStarterActor(nullptr);
    if (!starter)
        return 0;
    if (!(mActorName == starter->getName()))
        return 0;
    if (!mUniqueName.isEmpty()) {
        if (!starter->getUniqueName())
            return 0;
        return mUniqueName == sead::SafeString(starter->getUniqueName());
    }
    return 1;
}

void CheckStarter::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "ActorName");
    loadString(arg.param_accessor, "UniqueName");
}

void CheckStarter::loadParams() {
    getDynamicParam(&mActorName, "ActorName");
    getDynamicParam(&mUniqueName, "UniqueName");
}

}  // namespace uking::query
