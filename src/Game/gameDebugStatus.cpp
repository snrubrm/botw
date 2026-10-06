#include "Game/gameDebugStatus.h"

DebugStatus::DebugStatus(const sead::SafeString& title, int id) : mId(id), mTitle(title) {}

void DebugStatus::setStatus(const sead::SafeString& status) {
    mStatus.copy(status);
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
