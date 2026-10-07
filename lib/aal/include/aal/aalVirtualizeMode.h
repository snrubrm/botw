#pragma once

#include <prim/seadEnum.h>

namespace aal {

/// Whether a sound may be virtualized (stopped silently while it is inaudible). The enumerator names are guesses from
/// the behavior: 0 disables the virtualization (SoundSource::canVirtualize), 1 is the default (the sound is stopped),
/// 2 restarts the sound from the beginning when it is unvirtualized, 3 restarts it where it was virtualized and 4 does
/// the same but moves the position of the virtualized sound on (PlayingStateController::virtualize and
/// updateVirtualPlayingPos_).
SEAD_ENUM(VirtualizeMode, Disable, Normal, Restart, Resume, ResumeMoving)

}  // namespace aal
