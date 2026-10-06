#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// The volume of each channel of an output device (the Switch only has the TV).
/// TODO: the channel order is not known (ListenerSpeakerBalance::setSpeakerBalance only reads the first five values).
struct SpeakerChannelVolume {
    f32 volume[6];
};
static_assert(sizeof(SpeakerChannelVolume) == 0x18, "aal::SpeakerChannelVolume size mismatch");

}  // namespace aal
