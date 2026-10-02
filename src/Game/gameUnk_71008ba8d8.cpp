#include "Game/gameUnk_71008ba8d8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"

namespace ksys::evt {

bool callEvent(act::BaseProc* proc, const sead::SafeString& event, const sead::SafeString& entry,
               bool a4, bool a5) {
    auto* manager = Manager::instance();
    if (!manager)
        return false;

    Metadata metadata(event.cstr(), entry.cstr());
    metadata.setSkipIsStartableAirCheck(a5);
    metadata.set13(a5);
    CallArg arg;
    arg._31 = a4;
    arg.metadata = &metadata;
    arg.proc = proc;
    return manager->callEvent(arg);
}

bool callEvent(act::BaseProc* proc, const sead::SafeString& event, const sead::SafeString& entry,
               const sead::Matrix34f& mtx, bool a5, bool a6) {
    auto* manager = Manager::instance();
    if (!manager)
        return false;

    Metadata metadata;
    if (entry.isEmpty())
        metadata.init(event.cstr(), entry.cstr(), "Timeline");
    else
        metadata.init(event.cstr(), entry.cstr());
    metadata.setSkipIsStartableAirCheck(a6);
    metadata.set13(a6);
    CallArg arg;
    arg._30 = true;
    arg._0 = mtx;
    arg._31 = a5;
    arg.metadata = &metadata;
    arg.proc = proc;
    return manager->callEvent(arg);
}

}  // namespace ksys::evt

namespace uking {

bool callPlayerGameOverDemo(ksys::act::Actor* player) {
    const sead::SafeString event = "Demo006_0";
    const sead::SafeString entry = "Demo006_0";
    if (!player)
        return false;
    return ksys::evt::callEvent(nullptr, event, entry, player->getMtx(), true, false);
}

}  // namespace uking
