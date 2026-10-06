#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <time/seadTickTime.h>
#include "KingSystem/Utils/Types.h"

// Name from the CSV (DebugStatus::ctor 0x71010bcd5c, setStatus, clear, startTimer, stopTimer; the CSV
// name has no namespace). One line of the debug status list that GameSceneStatusMgr draws: a title, an
// optional timer (in milliseconds) and a status text.
// TODO: incomplete (_4 / _8: the draw code prints the title with the timer when _8 is zero).
class DebugStatus {
public:
    DebugStatus(const sead::SafeString& title, int id);

    // 0x71010bcef8: copies `status` into the status text.
    void setStatus(const sead::SafeString& status);
    // 0x71010bcfdc
    void clear() {
        mTimerMs = 0;
        mTimerRunning = false;
        _4 = 0;
        _8 = 0;
        mStatus.clear();
    }
    // 0x71010bd000 / 0x71010bd02c
    void startTimer();
    void stopTimer();

private:
    s32 mId;
    s32 _4 = 0;
    s32 _8 = 0;
    bool mTimerRunning = false;
    s64 mTimerMs = 0;
    sead::TickTime mTimerStart;
    sead::FixedSafeString<0x40> mTitle;
    sead::FixedSafeString<0x80> mStatus;
};
KSYS_CHECK_SIZE_NX150(DebugStatus, 0x110);
