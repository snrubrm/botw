#include "Game/gameSceneStatusMgr.h"
#include "Game/gameDebugStatus.h"

DebugStatus::DebugStatus(const sead::SafeString& title, int id) : mId(id), mTitle(title) {}

void DebugStatus::setStatus(const sead::SafeString& status) {
    mStatus.copy(status);
}

void DebugStatus::clear() {
    mTimerMs = 0;
    mTimerRunning = false;
    _4 = 0;
    _8 = 0;
    mStatus.clear();
}

void DebugStatus::startTimer() {
    mTimerRunning = true;
    mTimerStart.setNow();
}

void DebugStatus::stopTimer() {
    if (mTimerRunning)
        mTimerMs = sead::TickTime().diff(mTimerStart).toMilliSeconds();
    mTimerRunning = false;
}

SEAD_SINGLETON_DISPOSER_IMPL(GameSceneStatusMgr)

void GameSceneStatusMgr::unregisterStatus(DebugStatus* status) {
    if (status) {
        const s32 idx = mStatuses.indexOf(status);
        if (idx >= 0)
            mStatuses.erase(idx);
    }
}

void GameSceneStatusMgr::clearStatuses() {
    const auto end = mStatuses.end();
    for (auto it = mStatuses.begin(); end != it; ++it)
        (*it).clear();
    _21 = false;
}

void GameSceneStatusMgr::sub_71010BDCE4(bool value) {
    _20 = value;
}

void GameSceneStatusMgr::sub_71010BDCF0(bool value) {
    _22 = value;
}

void GameSceneStatusMgr::sub_71010BDCFC(bool value) {
    _23 = value;
}
