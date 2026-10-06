#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "aal/aalDeviceType.h"

namespace aal {

struct SpeakerChannelVolume;

/// Supplies the speaker balance (and the related reductions) of a sound instead of the usual spatial
/// calculation; see SoundSource::setSpeakerBalanceSupplier.
class ISpeakerBalanceSupplier {
    SEAD_RTTI_BASE(ISpeakerBalanceSupplier)
public:
    virtual ~ISpeakerBalanceSupplier() = default;

    virtual void calcSpeakerBalance(SpeakerChannelVolume* volume, DeviceType device, s32 index,
                                    f32 spread) = 0;
    /// The default ignores the first index and uses the other overload.
    virtual void calcSpeakerBalance(SpeakerChannelVolume* volume, DeviceType device, s32 index_a,
                                    s32 index_b, f32 spread);
    virtual f32 getEnvFxReduction() const { return -1.0f; }
    virtual f32 getFilterReduction() const { return 0.0f; }
    virtual f32 getPriorityReduction() const { return 1.0f; }
    virtual f32 getLpf() const { return 0.0f; }
    virtual f32 getReductionVolumeMax(s32 index) const { return 1.0f; }
};

}  // namespace aal
