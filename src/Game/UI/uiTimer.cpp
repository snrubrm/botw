#include "Game/UI/uiTimer.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/System/VFR.h"

namespace uking::ui {

// 0x7100a82aec
void UiTimer::init(f32 seconds) {
    timer = ksys::Timer(0.0f, 0.0f, 1.0f);
    duration = seconds * 30.0f;
    flag = seconds == 0.0f;
}

// 0x7100a82b14
void UiTimer::reset() {
    timer = ksys::Timer(0.0f, 0.0f, 1.0f);
}

// 0x7100a82b24
void UiTimer::setDuration(f32 seconds) {
    duration = seconds * 30.0f;
}

// 0x7100a82b34
void UiTimer::setToEnd() {
    timer = ksys::Timer(duration, duration, 1.0f);
}

// 0x7100a82b48
bool UiTimer::isDone() const {
    if (direction > 0.0f)
        return duration <= timer.value;
    if (!(direction < 0.0f))
        return true;
    return timer.value < 0.0f;
}

// 0x7100a82b84
f32 UiTimer::getProgress() const {
    if (duration == 0.0f)
        return 1.0f;
    return sead::Mathf::clamp(timer.value / duration, 0.0f, 1.0f);
}

// 0x7100a82bc4
void UiTimer::update() {
    updateImpl();
}

// 0x7100a82bc8
void UiTimer::updateImpl() {
    if (!timer.hasEnded(duration)) {
        if (direction > 0.0f) {
            if (duration <= timer.value)
                return;
        } else if (!(direction < 0.0f) || timer.value < 0.0f) {
            return;
        }
    }
    if (ksys::VFR::instance()) {
        ksys::VFR::ScopedDeltaSetter setter(0, 1);
        timer.update();
    } else {
        timer.rate = 1.0f;
        timer.update();
    }
}

// 0x7100a82c68
bool UiTimer::checkEnded() {
    if (duration == 0.0f) {
        if (!flag)
            return false;
        flag = false;
        return true;
    }
    return timer.hasEnded(duration);
}

// 0x7100a82c94
bool UiTimer::updateAndCheckEnded() {
    if (duration == 0.0f) {
        if (!flag)
            return false;
        flag = false;
        return true;
    }
    updateImpl();
    return timer.hasEnded(duration);
}

}  // namespace uking::ui
