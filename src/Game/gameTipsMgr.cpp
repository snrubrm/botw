#include "Game/gameTipsMgr.h"
#include <evfl/Action.h>
#include <evfl/Query.h>
#include <heap/seadExpHeap.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actAiQuery.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"

// 920CFC is the native sead enum text parser; text_(s32) returns const char*.
const char* getTipString(s32 index);

SEAD_SINGLETON_DISPOSER_IMPL(TipsMgr)

// 92026C binds the Tips heap as both EventFlow allocator user data pointers.
void* sub_7100921090(size_t size, size_t alignment, void* user_data) {
    return static_cast<sead::Heap*>(user_data)->alloc(size, alignment);
}

void sub_71009210B0(void* ptr, void* user_data) {
    static_cast<sead::Heap*>(user_data)->free(ptr);
}

void handler_TipsDisplayOK(const evfl::ActionArg& arg, evfl::ActionDoneHandler done) {
    // 92026C binds the address of its bool result as actor user data.
    if (auto* result = static_cast<bool*>(arg.actor_user_data))
        *result = true;
    done.Invoke();
}

void handler_TipsDisplayNG(const evfl::ActionArg& arg, evfl::ActionDoneHandler done) {
    if (auto* result = static_cast<bool*>(arg.actor_user_data))
        *result = false;
    done.Invoke();
}

void handler_FlagOn(const evfl::ActionArg& arg, evfl::ActionDoneHandler done) {
    ore::StringView flag;
    arg.param_accessor.FindString(&flag, "FlagName");
    if (auto* manager = ksys::gdt::Manager::instance())
        manager->setBoolNoCheck(true, flag.data());
    done.Invoke();
}

void handler_UnknownTipsAction(const evfl::ActionArg& arg, evfl::ActionDoneHandler done) {
    done.Invoke();
}

int sub_71009212D0(const evfl::QueryArg& arg) {
    // 92026C binds the Query found by name as each matching query's user data.
    if (auto* query = static_cast<ksys::act::ai::Query*>(arg.query_user_data)) {
        query->loadParams(arg);
        return query->doQuery();
    }
    return 0;
}

int sub_7100921324(const evfl::QueryArg& arg) {
    return 0;
}

TipsMgr::~TipsMgr() = default;

void TipsMgr::init(sead::Heap* heap) {
    _20 = sead::ExpHeap::create(0x100000, "Tips", heap, 8, sead::Heap::cHeapDirection_Forward, true);
    _26fc = false;
}

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
