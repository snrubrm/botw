#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace uking {

// Placeholder declaration (name from the CSV: EventMgrMiniGame::createInstance 0x7100e493f0, ctor
// 0x7100e499c4, calc 0x7100e49490, startCountup 0x7100e49a9c, startCountdown 0x7100e49acc,
// getTimerMs 0x7100e49b24; instance pointer at GOT 0x257d1d8; namespace is a guess). The event
// mini game timer (size 0x40, polymorphic sead singleton with the disposer at +0x20). Only what the
// AI actions use is declared.
// TODO: incomplete.
class EventMgrMiniGame {
    u8 _8[0x1c - 0x8];
    // 0 = stopped / disabled (EventDisableMiniGameTime), 1 = counting down (startCountdown),
    // 2 = stopped by StopEventMiniGameTime
    s32 mMode;

    SEAD_SINGLETON_DISPOSER(EventMgrMiniGame)
    EventMgrMiniGame();
    virtual ~EventMgrMiniGame();

public:
    // 0x7100e49a9c: starts counting up from 0 (the argument is clamped to [0, 5999999] and is the
    // maximum time in milliseconds).
    void startCountup(s32 max_time_ms);
    // 0x7100e49acc: starts counting down from `start_time_ms` (clamped like startCountup).
    void startCountdown(s32 start_time_ms);
    // 0x7100e49b24: the elapsed (or remaining) time in milliseconds.
    s32 getTimerMs() const;

    s32 getMode() const { return mMode; }
    void setMode(s32 mode) { mMode = mode; }
};

}  // namespace uking
