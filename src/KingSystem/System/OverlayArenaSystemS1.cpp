#include "KingSystem/System/OverlayArenaSystemS1.h"
#include <thread/seadThread.h>
#include <time/seadTickSpan.h>
#include <time/seadTickTime.h>
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys {

OverlayArenaSystemS1::OverlayArenaSystemS1() = default;

OverlayArenaSystemS1::~OverlayArenaSystemS1() = default;

void OverlayArenaSystemS1::init() {}

void OverlayArenaSystemS1::m3() {
    res::setCompactionStopped(false);
    while (res::isCompactionStopped()) {
        res::callResourceMgrTaskMethodOO();
        sead::Thread::sleep(sead::TickSpan::makeFromMilliSeconds(1));
    }
}

void OverlayArenaSystemS1::m5() {
    res::setCompactionStopped(false);
    evt::Manager::instance()->_1d2f4 |= 0x10000;
    while (res::isCompactionStopped()) {
        res::callResourceMgrTaskMethodOO();
        sead::Thread::sleep(sead::TickSpan::makeFromMilliSeconds(1));
    }
}

void OverlayArenaSystemS1::m10() {}

void OverlayArenaSystemS1::m13() {
    sead::TickTime start;
    res::stubbedLogFunction();
    while (!res::ResourceMgrTask::instance()->returnTrue1())
        sead::Thread::yield();
    res::stubbedLogFunction();
    res::setCompactionStopped(true);
    res::texHandleMgrSetSomeFlags(true);
}

void OverlayArenaSystemS1::m14() {}

}  // namespace ksys
