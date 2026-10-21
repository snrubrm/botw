#include "KingSystem/Quest/qstManager.h"
#include "KingSystem/Event/evtInfoData.h"
#include "KingSystem/Resource/Actor/resResourceAISchedule.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "Game/Actor/actNPCBase.h"
#include "KingSystem/ActorSystem/actActorParam.h"
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
void EventMgrStruct3B::sub_7100DC22E0(act::Actor* actor) {
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

// 0x7101279a54
void EventMgrStruct3A::formatActorName(sead::BufferedSafeString* name) const {
    name->copy(mActor->getParam()->getRes().mActorLink->getUserName(res::ActorLink::User::AISchedule));
    if (auto* npc = sead::DynamicCast<uking::act::NPCBase>(mActor)) {
        const sead::SafeString suffix(npc->_9d8);
        if (!suffix.isEmpty()) {
            name->append("-");
            name->append(suffix);
        }
    }
    if (mHasUniqueName) {
        name->append("-");
        name->append(mActor->getUniqueName());
    }
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

// 0x7101279ffc
void EventMgrStruct3A::sub_7101279FFC() {
    mAssigned = false;
    mFlowRecord = nullptr;
}

// 0x710127a008: the association is set and cleared by EventFlowMgr's schedule selection.
void EventMgrStruct3A::setFlowRecord(EventMgrStruct3B* record) {
    mFlowRecord = record;
}

// 0x7100dc14f0
// NON_MATCHING: native Byaml temporary lifetimes and timeline traversal scheduling differ.
void EventMgrStruct3B::loadBaischeduleStuff(EventMgrStruct3A* entry) {
    if (_58 == 0) {
        auto* actor = entry->mActor;
        const al::ByamlIter schedule(actor->getParam()->getRes().mAISchedule->getData());
        al::ByamlIter default_timeline;
        if (schedule.tryGetIterByKey(&default_timeline, "DefaultTimeline")) {
            loadAIScheduleTimelineInfo(default_timeline, actor,
                                      entry->mHasUniqueName ? actor->getUniqueName() : nullptr);
        } else {
            // Native DC14F0 constructs this diagnostic filename and discards its contents.
            sead::FormatFixedSafeString<128> filename("%s.baischedule",
                    actor->getParam()->getRes().mActorLink->getUserName(res::ActorLink::User::AISchedule));
        }
        al::ByamlIter conditional_timelines;
        if (schedule.tryGetIterByKey(&conditional_timelines, "ConditionalTimelines")) {
            for (s32 i = 0; i < conditional_timelines.getSize(); ++i) {
                al::ByamlIter timeline;
                if (conditional_timelines.tryGetIterByIndex(&timeline, i)) {
                    actor = entry->mActor;
                    loadAIScheduleTimelineInfo(timeline, actor,
                                      entry->mHasUniqueName ? actor->getUniqueName() : nullptr);
                }
            }
        }
    }
    ++_58;
}

// 0x7100dc1e64
void EventMgrStruct3B::sub_7100DC1E64() {
    if (_58 == 0) {
        const auto* quest = qst::Manager::instance()->sub_7100FD7610(_0);
        const al::ByamlIter data(*quest->mDataIter);
        al::ByamlIter steps;
        if (data.tryGetIterByKey(&steps, "Steps")) {
            for (s32 i = 0; i < steps.getSize(); ++i) {
                al::ByamlIter step;
                if (!steps.tryGetIterByIndex(&step, i))
                    continue;
                al::ByamlIter actors;
                if (!step.tryGetIterByKey(&actors, "Actors"))
                    continue;
                for (s32 j = 0; j < actors.getSize(); ++j) {
                    al::ByamlIter actor;
                    if (!actors.tryGetIterByIndex(&actor, j))
                        continue;
                    al::ByamlIter default_timeline;
                    if (actor.tryGetIterByKey(&default_timeline, "DefaultTimeline")) {
                        loadAIScheduleTimelineInfo(default_timeline, nullptr, nullptr);
                    } else {
                        // Native DC1E64 formats and discards this diagnostic filename.
                        sead::FormatFixedSafeString<128> filename("%s.quest", quest->mName.cstr());
                    }
                    al::ByamlIter conditional_timelines;
                    if (actor.tryGetIterByKey(&conditional_timelines, "ConditionalTimelines")) {
                        for (s32 k = 0; k < conditional_timelines.getSize(); ++k) {
                            al::ByamlIter timeline;
                            if (conditional_timelines.tryGetIterByIndex(&timeline, k))
                                loadAIScheduleTimelineInfo(timeline, nullptr, nullptr);
                        }
                    }
                }
            }
        }
    }
    ++_58;
}

// 0x7100dc2090
// NON_MATCHING: native Byaml and parameter-string temporary scheduling differ.
void EventMgrStruct3B::sub_7100DC2090(act::Actor* actor) {
    if (_58 == 0) {
        const char* flow_name;
        if (actor->getMapObjIter().tryGetParamStringByKey(&flow_name, "EventFlowName")) {
            const char* entry_name;
            if (!actor->getMapObjIter().tryGetParamStringByKey(&entry_name, "EventFlowEntryName"))
                entry_name = "";
            if (auto* flow = Manager::instance()->getEventFlowMgr()->load(
                        flow_name, entry_name, true, false, nullptr))
                _60[_160++] = flow;
            al::ByamlIter info;
            if (InfoData::instance()->getEntry(&info, flow_name, entry_name)) {
                al::ByamlIter children;
                if (info.tryGetIterByKey(&children, "child")) {
                    for (s32 i = 0; i < children.getSize(); ++i) {
                        al::ByamlIter child;
                        const char* child_file;
                        const char* child_entry;
                        if (!children.tryGetIterByIndex(&child, i) ||
                            !child.tryGetStringByKey(&child_file, "file") ||
                            !child.tryGetStringByKey(&child_entry, "entry"))
                            continue;
                        if (auto* flow = Manager::instance()->getEventFlowMgr()->load(
                                    child_file, child_entry, true, false, nullptr))
                            _60[_160++] = flow;
                    }
                }
            }
        }
    }
    _170 = actor;
    ++_58;
}

// 0x7100dc1680
// NON_MATCHING: native SafeString copy/append and Byaml temporary scheduling differ.
void EventMgrStruct3B::loadAIScheduleTimelineInfo(const al::ByamlIter& timeline,
                                                act::Actor* actor, const char* unique_name) {
    if (_160 >= 32)
        return;
    al::ByamlIter triggers;
    if (!timeline.tryGetIterByKey(&triggers, "TriggerEvents"))
        return;
    for (s32 i = 0; i < triggers.getSize(); ++i) {
        al::ByamlIter event;
        if (!triggers.tryGetIterByIndex(&event, i))
            continue;
        const char* trigger = nullptr;
        const char* entry_name = nullptr;
        bool pause_other_actors = false;
        // Native DC1680 discards these lookup results and uses the stored values.
        event.tryGetStringByKey(&trigger, "Trigger");
        event.tryGetStringByKey(&entry_name, "EvflEntry");
        event.tryGetBoolByKey(&pause_other_actors, "IsPauseOtherActors");
        if (!pause_other_actors)
            continue;
        sead::FixedSafeString<128> entry;
        entry.copy(entry_name);
        if (actor && sead::SafeString(trigger) == "Talk" &&
            sead::IsDerivedFrom<uking::act::NPCBase>(actor)) {
            const auto* npc = static_cast<uking::act::NPCBase*>(actor);
            const sead::SafeString suffix(npc->_9d8);
            if (!suffix.isEmpty())
                entry.copy(suffix);
        }
        if (unique_name) {
            entry.append("_");
            entry.append(unique_name);
        }
        sead::FixedSafeString<64> file;
        if (actor)
            file.copy(actor->getParam()->getRes().mActorLink->getUserName(res::ActorLink::User::AISchedule));
        else
            file.copy(_0);
        if (auto* flow = Manager::instance()->getEventFlowMgr()->load(
                    file, entry, true, false, nullptr))
            _60[_160++] = flow;
    }
}

}  // namespace ksys::evt
