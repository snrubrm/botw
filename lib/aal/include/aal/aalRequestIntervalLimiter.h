#pragma once

#include <basis/seadTypes.h>
#include "aal/aalStopWatch.h"

namespace aal {

class SoundSource;

/// Limits how often a sound can be requested in a group: after a sound was accepted, the following requests are
/// refused (the sound is stopped) until the interval has passed.
class RequestIntervalLimiter {
public:
    struct Settings {
        /// The interval (negative: not set).
        f32 mInterval;
    };

    RequestIntervalLimiter();
    virtual ~RequestIntervalLimiter() = default;

    void setup(const Settings& settings);
    void calc();
    bool limit(SoundSource* source);

private:
    StopWatch mStopWatch;
    f32 mInterval = 0.0f;
    bool mRunning = false;
};

}  // namespace aal
