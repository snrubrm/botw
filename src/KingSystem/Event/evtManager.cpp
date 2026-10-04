#include "KingSystem/Event/evtManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Event/evtContext.h"
#include "KingSystem/Event/evtEventMgrStruct1.h"
#include "KingSystem/Event/evtEventResource.h"

namespace ksys::evt {

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
EventFlow* Manager::getActiveEvent() const {
    if (!_1d2b8)
        return nullptr;
    return _1d2b8->getCurrentFlow();
}

// 0x7100db222c
EventFlow* Manager::sub_7100DB222C() {
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
