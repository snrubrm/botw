#include "KingSystem/Event/evtResidentEvent.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"

namespace ksys::evt {

ResidentEvent::ResidentEvent() = default;

ResidentEvent::~ResidentEvent() = default;

void ResidentEvent::initWithName(act::BaseProc* proc, const sead::SafeString& event_name,
                                 const sead::SafeString& entry_point) {
    unloadEvent();
    mLink.reset();
    Metadata metadata(event_name.cstr(), entry_point.cstr());
    mLink.initWithEvent(proc, &metadata);
    mProc = proc;
}

void ResidentEvent::unloadEvent() {
    if (!mEventFlow)
        return;
    auto* mgr = Manager::instance();
    if (!mgr)
        return;
    auto* flow_mgr = mgr->getEventFlowMgr();
    if (!flow_mgr)
        return;
    flow_mgr->unload(mEventFlow);
    mEventFlow = nullptr;
}

void ResidentEvent::initWithEvent_(act::BaseProc* proc, const Metadata* metadata) {
    unloadEvent();
    mLink.initWithEvent(proc, metadata);
    mProc = proc;
}

bool ResidentEvent::callEvent(bool a1) {
    auto* mgr = Manager::instance();
    if (!mgr)
        return false;
    CallArg arg;
    arg._31 = a1;
    arg._32 = mLink._178;
    arg._33 = mLink._179;
    arg.metadata = &mLink.mMetadata;
    arg.proc = mProc;
    return mgr->callEvent(arg);
}

bool ResidentEvent::sendMessageToEventMgrActor(act::Actor* actor) {
    if (!actor)
        return false;
    auto* mgr = Manager::instance();
    if (!mgr)
        return false;
    actor->sendMessage(*mgr->_48, MessageType(0x800002), this, true);
    return true;
}

bool ResidentEvent::loadEvent() {
    if (mEventFlow)
        return false;
    auto* mgr = Manager::instance();
    if (!mgr)
        return false;
    auto* flow_mgr = mgr->getEventFlowMgr();
    if (!flow_mgr)
        return false;
    mEventFlow = flow_mgr->loadSimple(mLink.mMetadata.getEventName().cstr(),
                                      mLink.mMetadata.getEntryPointName().cstr());
    return mEventFlow != nullptr;
}

}  // namespace ksys::evt
