#include "Game/gameTipsMgr.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/Utils/HeapUtil.h"

TipsMgr* TipsMgr::sInstance;

bool TipsMgr::areResourcesReady() {
    for (s32 i = 0; i < _23d0.size(); ++i) {
        if (_23d0[i].requestedLoad() && !_23d0[i].isReadyOrNeedsParse())
            return false;
    }
    if (!_20a8.isReadyOrNeedsParse())
        return false;
    for (s32 i = 0; i < _20f8.size(); ++i) {
        if (_20f8[i].requestedLoad() && !_20f8[i].isReadyOrNeedsParse())
            return false;
    }
    if (ksys::util::getDebugHeap() && !_26a0.isReadyOrNeedsParse())
        return false;
    return true;
}

void TipsMgr::sub_7100920200() {
    if (_23c8)
        _23c8->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    _26fc = false;
}

void TipsMgr::initBeforeStageGen() {
    if (_23c8)
        _23c8->wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
    _26fc = true;
}
