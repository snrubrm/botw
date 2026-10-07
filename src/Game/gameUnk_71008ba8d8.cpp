#include "Game/gameUnk_71008ba8d8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtEventSystem.h"
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

namespace {
const sead::SafeString sUnk_710246cdc0 = "CurrentActorName";
const sead::SafeString sUnk_710246cdd0 = "SharpWeaponAddValue";
const sead::SafeString sUnk_710246cde0 = "SharpWeaponAddType";
}  // namespace

const sead::SafeString& getStr_CurrentActorName() {
    return sUnk_710246cdc0;
}

const sead::SafeString& getStr_SharpWeaponAddValue() {
    return sUnk_710246cdd0;
}

const sead::SafeString& getStr_SharpWeaponAddType() {
    return sUnk_710246cde0;
}

bool isDemo000Or002(const ksys::evt::BaseProcLinkForEvent& link) {
    const sead::SafeString name = link.mMetadata.getEventName().cstr();
    return name == "Demo000_0" || name == "Demo002_0";
}

bool eventMgrHasActiveEvent() {
    return ksys::evt::Manager::instance()->hasActiveEvent();
}

bool sub_71008BA760() {
    if (auto* system = ksys::evt::EventSystem::instance())
        return system->sub_71008AC118();
    return false;
}

bool isActiveEventDemo000Or001Or002() {
    auto* manager = ksys::evt::Manager::instance();
    if (!manager)
        return false;
    return manager->isActiveEventNameEqualTo("Demo000_0", "") ||
           manager->isActiveEventNameEqualTo("Demo001_0", "") ||
           manager->isActiveEventNameEqualTo("Demo002_0", "");
}

bool sub_71008BB7D8() {
    if (auto* flow = ksys::evt::Manager::instance()->sub_7100DB222C())
        return flow->isPlaying();
    return false;
}

bool sub_71008BB804() {
    if (auto* flow = ksys::evt::Manager::instance()->sub_7100DB222C())
        return flow->byte3FlagIsSet();
    return false;
}

bool sub_71008BB830() {
    return ksys::evt::Manager::instance()->sub_7100DB20D0();
}

bool someEventMgrCheck() {
    if (auto* flow = ksys::evt::Manager::instance()->sub_7100DB222C())
        return flow->getEventFlowType() == 2;
    return false;
}

// NON_MATCHING: same logic; the original loads the empty-string GOT pointer separately in each branch (after the
// call), ours hoists it into a callee-saved register before hasActiveEvent()
// 0x71008bb878
const sead::SafeString& sub_71008BB878() {
    auto* manager = ksys::evt::Manager::instance();
    if (!manager->hasActiveEvent())
        return sead::SafeString::cEmptyString;
    auto* flow = manager->sub_7100DB222C();
    return flow ? flow->mEventName : sead::SafeString::cEmptyString;
}

namespace uking {

bool callPlayerGameOverDemo(ksys::act::Actor* player) {
    const sead::SafeString event = "Demo006_0";
    const sead::SafeString entry = "Demo006_0";
    if (!player)
        return false;
    return ksys::evt::callEvent(nullptr, event, entry, player->getMtx(), true, false);
}

}  // namespace uking
