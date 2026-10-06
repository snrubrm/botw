#include "aal/aalGroupLimiter.h"

namespace aal {

// 0x7100b80128
void GroupLimiter::finalize() {
    mInitialized = false;
}

// 0x7100b80134
void GroupLimiter::initialize(Group* group, sead::Heap* heap) {
    if (!mInitialized) {
        mGroup = group;
        mInitialized = true;
    }
}

// 0x7100b8014c
void GroupLimiter::calc() {
    if (mRequestIntervalLimiter)
        mRequestIntervalLimiter->calc();
}

// 0x7100b8015c
bool GroupLimiter::limitRequestInterval(SoundSource* source) {
    if (mRequestIntervalLimiterForLimit)
        return mRequestIntervalLimiterForLimit->limit(source);
    return true;
}

}  // namespace aal
