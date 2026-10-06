#include "aal/aalStopWatch.h"
#include "aal/aalSettings.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100ba5b34
StopWatch::StopWatch() : mTime(-1.0f) {}

// 0x7100ba5b50
void StopWatch::start() {
    mTime = 0.0f;
}

// 0x7100ba5b58
void StopWatch::stop() {
    mTime = -1.0f;
}

// 0x7100ba5b64
void StopWatch::calc() {
    if (mTime >= 0.0f) {
        if (auto* settings = SystemAccessor::getSettings())
            mTime = settings->mCalcTimeStep + mTime;
    }
}

}  // namespace aal
