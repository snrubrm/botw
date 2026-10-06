#include "aal/aalRequestIntervalLimiter.h"
#include "aal/aalSoundSource.h"

namespace aal {

// 0x7100b835ec
RequestIntervalLimiter::RequestIntervalLimiter() {
    mStopWatch.stop();
    mRunning = false;
}

// The body keeps the vtable pointer store of the destructor (a destructor with an empty body does not store it).
// 0x7100b83638 / 0x7100b8364c
RequestIntervalLimiter::~RequestIntervalLimiter() { ; }

// 0x7100b83650
void RequestIntervalLimiter::calc() {
    mStopWatch.calc();
    const f32 time = mStopWatch.getTime();
    if (time >= 0.0f) {
        if (time >= mInterval)
            mStopWatch.stop();
    } else if (mRunning) {
        mStopWatch.start();
    }
    mRunning = false;
}

// 0x7100b836b0
void RequestIntervalLimiter::setup(const Settings& settings) {
    if (settings.mInterval >= 0.0f)
        mInterval = settings.mInterval;
}

// 0x7100b836c4
bool RequestIntervalLimiter::limit(SoundSource* source) {
    if (!source)
        return false;
    if (source->isLooped())
        return true;
    if (mStopWatch.getTime() >= 0.0f) {
        source->stopForce();
        return false;
    }
    mRunning = true;
    return true;
}

}  // namespace aal
