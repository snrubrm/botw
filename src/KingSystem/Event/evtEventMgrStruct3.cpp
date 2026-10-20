#include "KingSystem/Event/evtContext.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Event/evtEventMgrStruct3.h"
#include "KingSystem/Event/evtEventFlowMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actInfoData.h"

namespace ksys::evt {

// 0x7100dc12a4
// NON_MATCHING: FixedSafeString vptr lifetime and normal Vector2 copy initialization differ.
EventMgrStruct3B::EventMgrStruct3B() = default;

// 0x7100dc1340
void EventMgrStruct3B::sub_7100DC1340(s32 a1, s32 a2, const sead::SafeString& name) {
    _0 = name;
    _160 = 0;
    _164 = a1;
    _168 = a2;
}

// 0x7100dc1448
void EventMgrStruct3B::sub_7100DC1448(bool force) {
    for (s32 i = 0; i < _160; ++i) {
        if (force || !_60[i]->_120)
            _60[i]->unload(force);
    }
    _0.clear();
    _58 = 0;
    _160 = 0;
}

// 0x7100dc22e0
void EventMgrStruct3B::sub_7100DC22E0() {
    if (--_58 != 0)
        return;
    for (s32 i = 0; i < _160; ++i)
        _60[i]->unload(true);
    _0.clear();
    _58 = 0;
    _160 = 0;
}

// 0x71012793ec
// NON_MATCHING: accessor and native owner-pointer clearing scheduling differ.
void EventActorLink::releaseActor(act::Actor* actor, bool notify) {
    if (!actor)
        actor = sead::DynamicCast<act::Actor>(mLink.getProc(nullptr));
    if (actor) {
        act::ActorLinkConstDataAccess accessor;
        act::acquireActor(&mLink, &accessor);
        if (notify)
            Manager::instance()->sub_7100DB0FB0(*accessor.getMessageTransceiverId(), MessageType(0x80000f), nullptr);
        actor->_1a0 = nullptr;
        mLink.reset();
    }
    for (auto& owner : mOwners)
        owner.flow = nullptr;
    mActive = false;
}

// 0x710127950c
// NON_MATCHING: owner iteration and native release-path scheduling differ.
void EventActorLink::removeOwner(EventFlowBase* flow) {
    for (auto& owner : mOwners) {
        if (owner.flow == flow) {
            owner.flow = nullptr;
            if (!mOwners[0].flow && !mOwners[1].flow && !mOwners[2].flow && !mOwners[3].flow) {
                auto* actor = sead::DynamicCast<act::Actor>(mLink.getProc(nullptr));
                releaseActor(actor, true);
            }
        }
    }
}

// 0x71012799c4
EventMgrStruct3A::EventMgrStruct3A() = default;

// 0x71012799d0
EventMgrStruct3A::~EventMgrStruct3A() = default;

// 0x71012799d4
void EventMgrStruct3A::assignToActor(act::Actor* actor) {
    mAssigned = true;
    mActor = actor;
    mHasUniqueName = act::InfoData::instance()->hasTag(actor->getName().cstr(), 0xcab53f3d);
    if (mHasUniqueName && !mActor->getUniqueName())
        mHasUniqueName = false;
}

// inline-only in the original; name is a guess. Repeated in 127961C and 1279784.
// Retain a unique owner pair,
// acquire the actor on the first new pair, and publish this record on the actor.
inline void EventActorLink::bindActor(act::Actor* actor, EventFlowBase* flow, void* data) {
    bool found = false;
    for (const auto& owner : mOwners) {
        if (owner.flow == flow) {
            found = true;
            break;
        }
    }
    if (!found) {
        for (auto& owner : mOwners) {
            if (!owner.flow) {
                owner.flow = flow;
                owner.data = data;
                mLink.acquire(actor, false);
                actor->m118(false);
                mActive = true;
                break;
            }
        }
    }
    actor->_1a0 = this;
}

// NON_MATCHING: native owner traversal and inline binding scheduling differ.
// 0x710127961c
void EventActorLinkPool::bindActor(act::Actor* actor, EventFlowBase* flow, void* data) {
    if (!flow) {
        auto* context = Manager::instance()->_1d2b8;
        if (!context)
            return;
        flow = context->getCurrentFlow();
        if (!flow)
            return;
    }
    auto* link = static_cast<EventActorLink*>(actor->get1a0());
    if (!link) {
        for (auto& entry : mLinks) {
            if (!entry.mActive) {
                link = &entry;
                break;
            }
        }
        if (!link)
            return;
    }
    link->bindActor(actor, flow, data);
}

// NON_MATCHING: native owner traversal and inline binding scheduling differ.
// 0x7101279784
void EventActorLinkPool::copyOwners(act::Actor* actor, const EventActorLink* source) {
    auto* link = static_cast<EventActorLink*>(actor->get1a0());
    if (link && link->mActive)
        link->releaseActor(actor, !source || !source->mActive);
    if (source) {
        for (const auto& owner : source->mOwners) {
            if (owner.flow)
                bindActor(actor, owner.flow, owner.data);
        }
    }
}

// 0x710127995c
void EventActorLinkPool::releaseActor(act::Actor* actor) {
    auto* link = static_cast<EventActorLink*>(actor->get1a0());
    if (link && link->mActive)
        link->releaseActor(actor, true);
}

// NON_MATCHING: SafeArray traversal uses an index instead of a remaining count.
// 0x7101279978
void EventActorLinkPool::removeOwner(EventFlowBase* flow) {
    for (auto& link : mLinks) {
        if (link.mActive)
            link.removeOwner(flow);
    }
}

}  // namespace ksys::evt
