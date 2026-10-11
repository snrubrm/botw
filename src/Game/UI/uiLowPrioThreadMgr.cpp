#include "Game/UI/uiUnkSingletons.h"
#include "KingSystem/Utils/Thread/TaskThread.h"
#include "KingSystem/Utils/Thread/TaskMgr.h"
#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(UiLowPrioThreadMgr)

UiLowPrioThreadMgr::~UiLowPrioThreadMgr() {
    _28->quitAndWaitDoneSingleThread(false);
    delete _28;
    _28 = nullptr;
    delete _30;
    _30 = nullptr;
    for (auto& handle : _38) {
        delete handle;
        handle = nullptr;
    }
}

// 0x7100a6d978
void UiLowPrioThreadMgr::pause() {
    if (_28)
        _28->pause();
}

// 0x7100a6d988
void UiLowPrioThreadMgr::resume() {
    if (_28)
        _28->resume();
}

// 0x7100a6d998
void UiLowPrioThreadMgr::clearQueue() {
    if (_28)
        _28->clearQueue();
}

}  // namespace uking::ui
