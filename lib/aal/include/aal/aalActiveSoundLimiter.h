#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <prim/seadEnum.h>
#include "aal/aalDebuggerResult.h"

namespace aal {

class SoundSource;

/// Limits the number of sounds that are active at the same time.
/// TODO: partial (the subclasses and the limiting calculation are not modeled).
class ActiveSoundLimiter {
public:
    /// Two flags that are copied together (the names are not known).
    struct Flags {
        u8 mA = 0;
        u8 mB = 0;
    };

    struct Settings {
        s32 mLimitNum;
        Flags mFlags;
    };

    ActiveSoundLimiter();
    virtual ~ActiveSoundLimiter() = default;

    void setup(const Settings& settings);
    /// Virtualizes (or stops) the sounds that are over the limit; the sound sources are sorted first (the sounds that
    /// come first are kept).
    void calcLimit(sead::OffsetList<SoundSource>* sound_sources);

protected:
    friend class GroupLimiter;

    /// The debugger result of the sounds that are over the limit.
    virtual DebuggerResult getDebuggerResultWhenLimit_() const = 0;
    virtual void sortSoundSourceList_(sead::OffsetList<SoundSource>* sound_sources) const = 0;
    virtual void sortSoundSourceArray_(sead::PtrArray<SoundSource>* sound_sources) const = 0;

    s32 mLimitNum = -1;
    Flags mFlags;
    /// The cause that the limited sounds are virtualized by (SoundSource::VirtualizedBy).
    s32 mVirtualizedBy = 1;
    bool _14 = false;
    bool _15 = false;
    u8 _16 = 0;
};
static_assert(sizeof(ActiveSoundLimiter) == 0x18, "aal::ActiveSoundLimiter size mismatch");

/// The sound sources that were started earlier are kept. The names of the limiters are the names of the classes of
/// the CSV; the sort of Earlier / Later is by the time the sound started.
class ActiveSoundLimiterEarlier : public ActiveSoundLimiter {
protected:
    DebuggerResult getDebuggerResultWhenLimit_() const override;
    void sortSoundSourceList_(sead::OffsetList<SoundSource>* sound_sources) const override;
    void sortSoundSourceArray_(sead::PtrArray<SoundSource>* sound_sources) const override;
};

class ActiveSoundLimiterLater : public ActiveSoundLimiter {
protected:
    DebuggerResult getDebuggerResultWhenLimit_() const override;
    void sortSoundSourceList_(sead::OffsetList<SoundSource>* sound_sources) const override;
    void sortSoundSourceArray_(sead::PtrArray<SoundSource>* sound_sources) const override;
};

class ActiveSoundLimiterPriorityEarlier : public ActiveSoundLimiter {
protected:
    DebuggerResult getDebuggerResultWhenLimit_() const override;
    void sortSoundSourceList_(sead::OffsetList<SoundSource>* sound_sources) const override;
    void sortSoundSourceArray_(sead::PtrArray<SoundSource>* sound_sources) const override;
};

class ActiveSoundLimiterPriorityLater : public ActiveSoundLimiter {
protected:
    DebuggerResult getDebuggerResultWhenLimit_() const override;
    void sortSoundSourceList_(sead::OffsetList<SoundSource>* sound_sources) const override;
    void sortSoundSourceArray_(sead::PtrArray<SoundSource>* sound_sources) const override;
};

/// The limiter classes (the names of the values are guesses from the classes that are created).
SEAD_ENUM(ActiveSoundLimiterType, None, PriorityEarlier, PriorityLater, Earlier, Later)

namespace LimiterUtil {
/// The size of the biggest active sound limiter.
u32 getMaxActiveSoundLimiterSize();
/// nullptr for None.
ActiveSoundLimiter* createActiveSoundLimiter(ActiveSoundLimiterType type, sead::Heap* heap);
}  // namespace LimiterUtil

}  // namespace aal
