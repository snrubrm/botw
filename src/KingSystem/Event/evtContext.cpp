#include "KingSystem/Event/evtContext.h"
#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Event/evtEventFlowMgr.h"
#include "KingSystem/Event/evtManager.h"

namespace ksys::evt {

// NON_MATCHING: missing the last step: `if (_1f7)` the original clears bit 0 of ActorSystem::_13b (`and #0xfe`);
// _13b is a private bool in ActorSystem (lane4 header), so that flag write is left out.
Context::~Context() {
    constexpr u64 flags = 0x20000040000;
    for (int i = 0; i < mFlows.size(); ++i) {
        if ((mFlows(i)->_340 & flags) == flags) {
            Manager::instance()->_1d129 = true;
            break;
        }
    }
    for (int i = 0; i < mFlows.size(); ++i)
        delete mFlows.at(i);
    mFlows.freeBuffer();

    delete _200;

    if (mChildFlows.isBufferReady()) {
        for (int i = 0; i < mChildFlows.size(); ++i) {
            if (mChildFlows[i].flow)
                mChildFlows[i].flow->unload(true);
        }
        mChildFlows.freeBuffer();
    }

    Manager::instance()->sub_7100DB3750();
}

// 0x7100db93f4
void Context::loadChildrenEvents() {
    if (!mChildFlows.isBufferReady())
        return;
    for (s32 i = 0; i < mChildFlows.size(); ++i) {
        auto& child = mChildFlows[i];
        if (child.flow)
            continue;
        if (i + 1 == mFlowStack[mStackTop]) {
            child._8 = true;
        } else if (!child._8) {
            auto* flow = mFlows.at(i + 1);
            if (!flow->hasFlag(EventFlowBase::Flag::_80000000000))
                child.flow = Manager::instance()->getEventFlowMgr()->loadSimple(
                        flow->mEventName, flow->mEntryPointName);
        }
    }
}

// 0x7100db9b9c
s32 Context::x_3(const sead::SafeString& event_name, const sead::SafeString& entry_point) const {
    for (s32 i = 0; i < mFlows.size(); ++i) {
        if (mFlows.at(i)->mEventName == event_name &&
            mFlows.at(i)->mEntryPointName == entry_point)
            return i;
    }
    return -1;
}

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
