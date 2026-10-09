#include "Game/gameTipsMgr.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"

// 920CFC is the native sead enum text parser; text_(s32) returns const char*.
const char* getTipString(s32 index);

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

void TipsMgr::loadTipFiles() {
    ksys::res::LoadRequest request;
    request.mRequester = "TipsMgr";
    request._22 = true;
    sead::FixedSafeString<128> path;
    for (s32 i = 0; i < _23d0.size(); ++i) {
        path.format("Tips/%s.byml", getTipString(i));
        if (ksys::res::ResourceMgrTask::instance()->getResourceSize(path, nullptr))
            _23d0[i].requestLoad(path, &request, nullptr);
    }
    _20a8.requestLoad("EventFlow/TipsCommon.bfevfl", &request, nullptr);
    for (s32 i = 0; i < _20f8.size(); ++i) {
        path.format("EventFlow/%s.bfevfl", getTipString(i));
        if (ksys::res::ResourceMgrTask::instance()->getResourceSize(path, nullptr))
            _20f8[i].requestLoad(path, &request, nullptr);
    }
    if (ksys::util::getDebugHeap())
        _26a0.requestLoad("Tips/EventFlowEntry.byml", &request, nullptr);
}
