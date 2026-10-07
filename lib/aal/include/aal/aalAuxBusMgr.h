#pragma once

#include <basis/seadTypes.h>
#include "aal/aalDeviceType.h"
#include "aal/aalTimedFader.h"

namespace aal {

/// Manages the auxiliary buses (the environment effect send). TODO: incomplete: the singleton and everything
/// before offset 0x48 are not modeled.
class AuxBusMgr {
public:
    static AuxBusMgr* sInstance;

    /// The duration of one audio frame in seconds.
    f32 getAudioFrameTime() const;
    f32 getMinEnvFxSend() const;
    f32 getMaxEnvFxSend() const;
    BusType getEnvFxBus() const { return mEnvFxBus; }
    /// Moves the environment effect send range to [min_send, max_send] in `time` seconds (a negative maximum
    /// means the same as the minimum).
    void setEnvFxSend(f32 min_send, f32 max_send, f32 time);

private:
    u8 _0[0x40];
    /// The bus that the environment effect is sent to.
    BusType mEnvFxBus;
    u8 _44[0x48 - 0x44];
    SimpleTimedFader mMinEnvFxSendFader;
    SimpleTimedFader mMaxEnvFxSendFader;
    f32 mMinEnvFxSendTarget;
    f32 mMaxEnvFxSendTarget;
};

}  // namespace aal
