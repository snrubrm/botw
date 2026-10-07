#include "KingSystem/Event/evtContext.h"
#include "KingSystem/Event/evtActorBase.h"

namespace ksys::evt {

// 0x7100db9e2c
void Context::setActorBeingDeleted() {
    mActorBeingDeleted = true;
}

// 0x7100db9df4
void Context::setFlag4() {
    getCurrentFlow()->setFlag4();
}

// 0x7100db9dbc
void Context::updateEventsStatus() {
    getCurrentFlow()->sub_7100DB6CFC();
}

// 0x7100db9e38
ActorBase* Context::getActorByPointer(act::BaseProc* proc) {
    auto* actors = getCurrentFlowUnchecked()->_110;
    if (!actors)
        return nullptr;
    return actors->sub_7100DA2E84(proc);
}

// 0x7100db9e64
ActorBase* Context::getActorByName(const sead::SafeString& name, const sead::SafeString& entry) {
    auto* actors = getCurrentFlowUnchecked()->_110;
    if (!actors)
        return nullptr;
    if (auto* actor = actors->getActorByName(name, entry))
        return actor;
    if (entry.isEmpty())
        return actors->getActorByName(name, sead::SafeString("0"));
    return nullptr;
}

// 0x7100dba274
void Context::sub_7100DBA274() {
    for (s32 i = 0; i < mFlows.size(); ++i)
        mFlows(i)->_340 |= 0x1000000000;
}

// 0x7100dba314
sead::SafeString Context::getEventName() const {
    return getCurrentFlow()->mEventName;
}

// 0x7100dba360
sead::SafeString Context::getEntryPointName() const {
    return getCurrentFlow()->mEntryPointName;
}

// 0x7100dba2ac
bool Context::sub_7100DBA2AC(act::BaseProc* proc) {
    return getCurrentFlow()->x_8(proc);
}

// 0x7100dba3ac
bool Context::sub_7100DBA3AC(bool a1) {
    bool result = true;
    for (s32 i = 0; i < mFlows.size(); ++i)
        result &= mFlows.at(i)->sub_7100DB8BB8(a1);
    return result;
}

// 0x7100dba2e4
void Context::setNoDeleteCurrentActor(bool no_delete) {
    if (auto* actors = getCurrentFlowUnchecked()->_110)
        actors->mNoDeleteCurrentActor = no_delete;
}

// 0x7100db9b40
void Context::x(bool set) {
    getCurrentFlow()->x(set);
    _1f4 = true;
}

}  // namespace ksys::evt
