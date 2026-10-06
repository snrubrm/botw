#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <thread/seadCriticalSection.h>

namespace aal {

class SoundSource;

namespace LimiterUtil {
/// 0x7100b835e4 (declared only)
u32 getMaxActiveSoundLimiterSize();
}  // namespace LimiterUtil

/// Limits the number of active sounds. TODO: only calcLimit is declared.
class ActiveSoundLimiter {
public:
    /// 0x7100b83310 (declared only)
    void calcLimit(sead::OffsetList<SoundSource>* sound_sources);
};

/// Emits sounds (SoundSource) and keeps track of the ones that are playing.
/// TODO: incomplete (the SoundParam at +0x10 and the SpatialSetting at +0xa8 are not modeled; the constructor and
/// destructor are not decompiled).
class Emitter {
public:
    static u32 getRequiredMemSize();

    void calc();
    /// Whether any of the sound sources of the emitter is still playing.
    bool isActive() const;
    /// 0x7100b9f264 (declared only)
    void removeSoundSource(SoundSource* sound_source);
    void setDebugSolo(bool solo);
    void setDebugMute(bool mute);
    bool isDebugMuted() const;

private:
    u8 _0[0x50];
    sead::OffsetList<SoundSource>* mSoundSources;
    sead::CriticalSection mCS;
    u8 _98[8];
    ActiveSoundLimiter* mLimiter;
    u8 _a8[0x13c - 0xa8];
    /// Bit 0: solo, bit 1: muted (a solo emitter is not muted).
    u8 mDebugFlags;
};

}  // namespace aal
