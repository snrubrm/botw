#include "KingSystem/Event/evtManager.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Event/evtContext.h"
#include "KingSystem/Event/evtEventMgrStruct1.h"

namespace ksys::evt {

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
