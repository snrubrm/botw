#pragma once

#include <prim/seadEnum.h>

namespace aal {

/// The speaker channels (the order of SpeakerChannelVolume::volume). The enumerator names are guesses from the
/// channel layout of nn::atk (the text table of the original has not been located); 4 is the value that
/// SoundSource::getChannelSpeakerType returns for a channel that does not exist.
SEAD_ENUM(SpeakerChannel, FrontLeft, FrontRight, RearLeft, RearRight, FrontCenter, Lfe)

}  // namespace aal
