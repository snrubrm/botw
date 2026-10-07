#pragma once

#include <basis/seadTypes.h>
#include <nn/audio.h>
#include "aal/aalDeviceType.h"
#include "aal/aalOutputMode.h"

namespace aal {

/// The connection to the sound library (nn::atk) when it is not used through the sead audio manager. TODO: only
/// the output settings that aal::Settings changes are declared.
class SDKFoundation {
public:
    /// 0x7100ba0c6c (declared only)
    void setOutputMode(OutputMode mode, DeviceType device);
    /// 0x7100ba0ca8 / 0x7100ba0cd0 / 0x7100ba0cfc (declared only)
    void setTVOutputVolume(f32 volume);
    void setBuildInSpeakerOutputVolume(f32 volume);
    void setStereoJackOutputVolume(f32 volume);
};

}  // namespace aal
