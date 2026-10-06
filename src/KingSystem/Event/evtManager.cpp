#include "KingSystem/Event/evtManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageDispatcher.h"
#include "KingSystem/Event/evtContext.h"
#include "KingSystem/Event/evtEventMgrStruct1.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Event/evtInfoData.h"

namespace ksys::evt {

// NON_MATCHING: same calls (this string's assureTermination once, the argument's twice) but the original loads the
// string pointer of the context's string between the first two virtual calls where ours loads it after them.
// 0x7100db05f4
bool Manager::isEventStartableAir(const BaseProcLinkForEvent& link) {
    const Metadata& metadata = link.mMetadata;
    if (metadata.getFlags().getDirect() == 0x1f4)
        return true;
    if (metadata.isSkipIsStartableAirCheck())
        return true;

    al::ByamlIter iter;
    if (!InfoData::instance()->getEntry(&iter, metadata.getEventName().cstr(),
                                        metadata.getEntryPointName().cstr())) {
        return true;
    }

    bool startable_air = false;
    iter.tryGetBoolByKey(&startable_air, "is_startable_air");
    if (startable_air)
        return true;
    if (_1d108 && !_1d108->m21())
        return false;
    return true;
}

// 0x7100db06ec
bool Manager::sub_7100DB06EC(const BaseProcLinkForEvent& link) {
    bool startable_air = false;
    const Metadata& metadata = link.mMetadata;
    if (metadata.getFlags().getDirect() != 0x1f4 && !metadata.isSkipIsStartableAirCheck()) {
        al::ByamlIter iter;
        if (InfoData::instance()->getEntry(&iter, metadata.getEventName().cstr(),
                                           metadata.getEntryPointName().cstr())) {
            iter.tryGetBoolByKey(&startable_air, "is_startable_air");
        }
    }
    return startable_air;
}

// 0x7100db2910
bool Manager::isActiveEventNameEqualTo(const sead::SafeString& event_name,
                                       const sead::SafeString& entry_point) const {
    if (auto* context = _1d2b8)
        return context->_60 == event_name && context->_b8 == entry_point;
    return false;
}

// 0x7100db0fb0
bool Manager::sub_7100DB0FB0(const MesTransceiverId& dest, MessageType type, void* user_data) {
    if (MessageDispatcher::instance()->isProcessingOnCurrentThread())
        return mTransceiver.sendMessageOnProcessingThread(dest, type, user_data, true);
    return mTransceiver.sendMessage(dest, type, user_data, true);
}

// 0x7100db0bac
bool Manager::callEvent(const Metadata& metadata, act::Actor* actor, void* x) {
    if (actor && actor->isDeletedOrDeleting())
        return false;

    CallArg arg;
    arg._40 = x;
    arg.proc = actor;
    arg.metadata = &metadata;
    return callEvent(arg);
}

// 0x7100db0c44
bool Manager::callEvent(const CallArg& arg) {
    s32 result = 0x1ff;
    if (!doCallEvent(arg, &result))
        return false;
    if (result != 500)
        _1d2f4 |= 0x100;
    return true;
}

// 0x7100db28c4
EventFlowBase* Manager::getActiveEvent() const {
    if (!_1d2b8)
        return nullptr;
    return _1d2b8->getCurrentFlow();
}

// 0x7100db222c
EventFlowBase* Manager::sub_7100DB222C() {
    if (!_1d2b8)
        return nullptr;
    return _1d2b8->getCurrentFlow();
}

// 0x7100db2440
bool Manager::checkEventCancel() const {
    if (!_1d2b8)
        return false;
    return (_1d2b8->getCurrentFlowUnchecked()->_340_bytes[1] >> 5) & 1;
}

// 0x7100db137c
void* Manager::sub_7100DB137C() const {
    if (!_1d2b8)
        return nullptr;
    auto* resource = _1d2b8->getCurrentFlowUnchecked()->_108;
    if (!resource)
        return nullptr;
    return resource->_1b8;
}

// 0x7100db2804
bool Manager::finishedLoadingResidentData() {
    const bool finished = _1d378->finishedLoading();
    mEventFlowMgr->calc(true);
    const bool ready = mEventFlowMgr->areAllEventFlowsReady();
    return finished & ready;
}

// NON_MATCHING: only the loop bound of the pair scan differs (`cmp x8, #0x20; b.lt` on the already incremented
// counter in the original, `cmp x8, #0x1f; b.le` here)
bool Manager::eventResidentMgrFinished() {
    bool done = true;
    for (auto* context : mContexts) {
        if (context)
            done &= context->sub_7100DBA3AC(false);
    }
    done &= mEventFlowMgr->loadEventResourceForAllEventFlows(false);
    if (!done)
        return false;
    for (s32 i = 0; i < 32; i += 2) {
        if (mContexts[i] || mContexts[i + 1])
            return false;
    }
    return mEventFlowMgr->sub_7100DBF50C();
}

bool Manager::sub_7100DB2804(bool a1) {
    bool result = true;
    for (auto* context : mContexts) {
        if (context)
            result &= context->sub_7100DBA3AC(a1);
    }
    result &= mEventFlowMgr->loadEventResourceForAllEventFlows(a1);
    return result;
}

// 0x7100db2884
void Manager::sub_7100DB2884() {
    for (auto* context : mContexts) {
        if (context)
            context->sub_7100DBA274();
    }
}

// 0x7100db2340
void Manager::setNoDeleteCurrentActor(bool no_delete) {
    if (_1d2b8)
        _1d2b8->setNoDeleteCurrentActor(no_delete);
}

SEAD_SINGLETON_DISPOSER_IMPL(Manager)

f32 Manager::sub_7100DB1138(int idx) const {
    if (idx == -99)
        return 0.0f;
    return _1d2d0->sub_7101273400(idx);
}

void Manager::sub_7100DB1158(int idx) {
    if (idx == -99)
        return;
    _1d2d0->sub_71012733D8(idx);
}

f32 Manager::sub_7100DB1174(int idx) const {
    return _1d2d0->sub_7101273448(idx);
}

bool Manager::sub_7100DB0CA0(const Metadata& metadata, act::Actor* actor) {
    return false;
}

bool Manager::hasActiveEvent() const {
    return _1d2b8 != nullptr;
}

// 0x7100db199c
void Manager::incrementAliveEventFlowCount() {
    mAliveEventFlowCount = sead::Mathi::min(mAliveEventFlowCount + 1, 0x100);
}

// 0x7100db19c0
void Manager::sub_7100DB19C0() {
    mAliveEventFlowCount = sead::Mathi::max(mAliveEventFlowCount - 1, 0);
}

// 0x7100db19dc
bool Manager::sub_7100DB19DC() const {
    if (_1d2c0)
        return true;
    return mAliveEventFlowCount < 1;
}

// 0x7100db101c
bool Manager::getActiveEventName(const char** event_name, const char** entry_point_name) const {
    if (!_1d2b8)
        return false;
    if (event_name)
        *event_name = _1d2b8->getEventName().cstr();
    if (entry_point_name)
        *entry_point_name = _1d2b8->getEntryPointName().cstr();
    return true;
}

// 0x7100db2278
act::BaseProcLink* Manager::getBaseProcLinkFromActiveEvent(const sead::SafeString& name,
                                                           const sead::SafeString& entry_point) const {
    if (!_1d2b8)
        return nullptr;
    auto* actor = _1d2b8->getActorByName(name, entry_point);
    if (!actor)
        return nullptr;
    return &actor->mLink;
}

// 0x7100db12d8
act::BaseProcLink* Manager::getBaseProcLinkForActorOrActiveLink(act::BaseProc* proc) const {
    if (proc) {
        for (s32 i = 0; i < 32; ++i) {
            if (mContexts[i] && mContexts[i]->getActorByPointer(proc))
                return &mContexts[i]->mLink;
        }
    }
    return _1d2b8 ? &_1d2b8->mLink : nullptr;
}

// 0x7100db0ea0
bool Manager::sub_7100DB0EA0(const Message* message) {
    if (message) {
        const u32 type = message->getType();
        if (type - 0x800001 <= 1 && message->getUserData()) {
            if (auto* link = static_cast<BaseProcLinkForEvent*>(message->getUserData())) {
                auto* actor = link->acquireActor();
                if (!actor || !actor->isDeletedOrDeleting()) {
                    CallArg arg;
                    arg._40 = nullptr;
                    arg.proc = actor;
                    arg.metadata = &link->mMetadata;
                    s32 result = 0x1ff;
                    if (doCallEvent(arg, &result)) {
                        if (result != 500)
                            _1d2f4 |= 0x100;
                        link->reset();
                    }
                }
            }
        }
    }
    return true;
}

// 0x7100db235c
bool Manager::getEventEntryPointName(sead::BufferedSafeString* out) const {
    if (!_1d2b8)
        return false;
    out->copy(sead::SafeString(_1d2b8->_b8.cstr()));
    return true;
}

// 0x7100db11d4
act::Actor* Manager::getStarterActor(act::BaseProc* proc) const {
    auto* link = getBaseProcLinkForActorOrActiveLink(proc);
    if (!link)
        return nullptr;
    return sead::DynamicCast<act::Actor>(link->getProc(nullptr, nullptr));
}

// 0x7100db10b0
bool Manager::sub_7100DB10B0(const void*, act::BaseProc* proc, void** out_1b8, void** out_1c0) const {
    for (s32 i = 0; i < 32; ++i) {
        if (!mContexts[i])
            continue;
        if (auto* actor = mContexts[i]->getActorByPointer(proc)) {
            if (out_1b8)
                *out_1b8 = actor->_1b8;
            if (out_1c0)
                *out_1c0 = actor->_1c0;
            return true;
        }
    }
    return false;
}

// 0x7100db22a8
act::BaseProcLink* Manager::sub_7100DB22A8() const {
    {
        const sead::SafeString name = "Argument";
        if (_1d2b8) {
            if (auto* actor = _1d2b8->getActorByName(name, sead::SafeString::cEmptyString))
                return &actor->mLink;
        }
    }
    const sead::SafeString name = "Current";
    if (_1d2b8) {
        auto* actor = _1d2b8->getActorByName(name, sead::SafeString::cEmptyString);
        if (!actor)
            return nullptr;
        return &actor->mLink;
    }
    return nullptr;
}

// 0x7100db272c
void Manager::setFlags1000() {
    _1d2f4 |= 0x1000;
}

// 0x7100db24c0
void Manager::initBeforeStageGen() {
    _1d2f8 = 999;
}

// 0x7100db04d8
void Manager::initBeforeStageGenB() {
    _1d1b0 &= ~2u;
}

}  // namespace ksys::evt
