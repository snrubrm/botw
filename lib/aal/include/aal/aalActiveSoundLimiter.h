#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>

namespace aal {

class SoundSource;

/// Limits the number of sounds that are active at the same time.
/// TODO: partial (the subclasses and the limiting calculation are not modeled).
class ActiveSoundLimiter {
public:
    struct Settings {
        s32 mLimitNum;
        u8 mFlagA;
        u8 mFlagB;
    };

    ActiveSoundLimiter();
    virtual ~ActiveSoundLimiter() = default;

    void setup(const Settings& settings);
    /// 0x7100b83310 (declared only)
    void calcLimit(sead::OffsetList<SoundSource>* sound_sources);

private:
    s32 mLimitNum = -1;
    u8 mFlagA = 0;
    u8 mFlagB = 0;
    s32 _10 = 1;
    u16 _14 = 0;
    u8 _16 = 0;
};
static_assert(sizeof(ActiveSoundLimiter) == 0x18, "aal::ActiveSoundLimiter size mismatch");

namespace LimiterUtil {
/// The size of the biggest active sound limiter.
u32 getMaxActiveSoundLimiterSize();
}  // namespace LimiterUtil

}  // namespace aal
