#pragma once

#include <prim/seadEnum.h>

namespace aal {

/// How the sound is mixed to the speakers. The enumerator names are guesses from nn::atk::OutputMode (the
/// text table of the original has not been located).
SEAD_ENUM(OutputMode, Mono, Stereo, Surround)

}  // namespace aal
