#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// Measures time in calculation steps: the time is negative while the watch is stopped.
class StopWatch {
public:
    StopWatch();
    virtual ~StopWatch() = default;

    void start();
    void stop();
    /// Advances a running watch by the time step of the system.
    void calc();
    f32 getTime() const { return mTime; }

private:
    f32 mTime;
};

}  // namespace aal
