#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/System/Timer.h"

namespace uking::ui {

/// A ksys::Timer with a duration (in frames: seconds * 30) and a direction, shared by the UI screens.
/// Placeholder name and member names (recovered from the CSV rows 0x7100a82aec - 0x7100a82ce4).
struct UiTimer {
    /// 0x7100a82aec: restarts the timer: `seconds` is the duration; a zero duration is "ended" once.
    void init(f32 seconds);
    // 0x7100a82b14
    void reset();
    // 0x7100a82b24
    void setDuration(f32 seconds);
    // 0x7100a82b34
    void setToEnd();
    // 0x7100a82b48
    bool isDone() const;
    // 0x7100a82b84
    f32 getProgress() const;
    // 0x7100a82bc8
    void update();
    // 0x7100a82c68
    bool checkEnded();
    // 0x7100a82c94
    bool updateAndCheckEnded();

    ksys::Timer timer;
    /* 0xc */ f32 duration{};
    /* 0x10 */ f32 direction = 1.0f;
    /* 0x14 */ bool flag{};
};

}  // namespace uking::ui
