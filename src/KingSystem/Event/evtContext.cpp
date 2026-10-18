#include "KingSystem/Event/evtContext.h"
#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
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

// String buffer extents are proved by DB58B8 and DAF464 initialization.
static_assert(offsetof(EventFlowBase, _218) == 0x218);
static_assert(offsetof(Manager, _1d380) == 0x1d380);

// 0x7100db9500
// NON_MATCHING: baseline SafeString termination calls and alias-chain bounds checks differ.
bool Context::calc() {
    if (!act::ActorSystem::instance()->getPlayer() &&
        mProcLink.mMetadata.getEventName() != "Demo169_0") {
        // The original formats this filename even though its result is not consumed.
        sead::FixedSafeString<128> filename;
        filename.format("%s.bfevfl", mProcLink.mMetadata.getEventName().cstr());
        return true;
    }
    const bool finished = getCurrentFlow()->calc();
    _1f5 = 0;
    ++_238;
    if (!finished)
        return false;
    if (Manager::instance()->_1d380 == getCurrentFlow()->mEventName) {
        getCurrentFlow()->x(true);
        _1f4 = true;
    } else {
        sead::SafeString next_name = getCurrentFlow()->_218;
        bool has_next = !next_name.isEmpty();
        if (has_next) {
            s32 next_index;
            if (getCurrentFlowUnchecked()->_340 & 0x100000) {
                do {
                    next_index = x_3(next_name.cstr(), next_name.cstr());
                    auto* next = mFlows.at(next_index);
                    if (!(next->_340 & 0x100000))
                        break;
                    next_name = next->_218;
                    has_next = !next_name.isEmpty();
                } while (has_next);
            } else {
                next_index = x_3(next_name.cstr(), next_name.cstr());
            }
            if (has_next) {
                const u64 flags = getCurrentFlowUnchecked()->_340;
                if (!(flags & 0x60)) {
                    mFlowStack[mStackTop] = s8(next_index);
                    if (flags & 0x8000000000)
                        getCurrentFlowUnchecked()->_340 |= 0x8000000000;
                    else
                        getCurrentFlowUnchecked()->_340 &= ~u64(0x8000000000);
                    if (flags & 0x4000000000)
                        getCurrentFlowUnchecked()->_340 |= 0x4000000000;
                    else
                        getCurrentFlowUnchecked()->_340 &= ~u64(0x4000000000);
                    getCurrentFlow()->initEventAndReport(false);
                    _1f5 = 1;
                    return false;
                }
            }
        }
    }
    if (mStackTop == 0)
        return true;
    auto* finished_flow = getCurrentFlow();
    --mStackTop;
    if (finished_flow->_340 & 0x20)
        getCurrentFlow()->x(false);
    if (finished_flow->_340 & 0x40)
        getCurrentFlow()->exitEventMaybe();
    sUnk_7102601528 = getCurrentFlow();
    getCurrentFlow()->x_5(finished_flow);
    getCurrentFlowUnchecked()->_148.Invoke();
    sUnk_7102601528 = nullptr;
    _1f5 = 1;
    return false;
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
