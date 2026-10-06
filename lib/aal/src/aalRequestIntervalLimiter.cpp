#include "aal/aalRequestIntervalLimiter.h"
#include "aal/aalSoundSource.h"

namespace aal {

// 0x7100b835ec
RequestIntervalLimiter::RequestIntervalLimiter() {
    mStopWatch.stop();
    mRunning = false;
}

// 0x7100b83650
void RequestIntervalLimiter::calc() {
    mStopWatch.calc();
    if (mStopWatch.getTime() < 0.0f) {
        if (mRunning)
            mStopWatch.start();
    } else if (mStopWatch.getTime() >= mInterval) {
        mStopWatch.stop();
        mRunning = false;
    }
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
    if (mStopWatch.getTime() < 0.0f) {
        mRunning = true;
        return true;
    }
    source->stopForce();
    return false;
}

}  // namespace aal
