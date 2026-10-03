// 0x71008bb56c: event call helper (CSV callDemo007_1) of the TU after the Demo005_0 / Demo616_0 callers.
#include "Game/gameUnk_71008ba8d8.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"

namespace uking {

bool callDemo007_1(ksys::act::BaseProc* proc) {
    auto* manager = ksys::evt::Manager::instance();
    if (!manager)
        return false;

    ksys::evt::Metadata metadata("Demo007_1", "Demo007_1");
    metadata.setSkipIsStartableAirCheck(false);
    metadata.set13(false);
    ksys::evt::CallArg arg;
    arg._31 = true;
    arg.metadata = &metadata;
    arg.proc = proc;
    return manager->callEvent(arg);
}

}  // namespace uking
