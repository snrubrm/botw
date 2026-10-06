#include "aal/aalActiveSoundLimiter.h"

namespace aal {

// 0x7100b832c8
ActiveSoundLimiter::ActiveSoundLimiter() = default;

// 0x7100b832fc
void ActiveSoundLimiter::setup(const Settings& settings) {
    mFlagA = settings.mFlagA;
    mFlagB = settings.mFlagB;
    mLimitNum = settings.mLimitNum;
}

// 0x7100b835e4
u32 LimiterUtil::getMaxActiveSoundLimiterSize() {
    return sizeof(ActiveSoundLimiter);
}

}  // namespace aal
