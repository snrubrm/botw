#pragma once

#include <prim/seadEnum.h>

namespace aal {

/// Whether a sound may be virtualized (stopped silently while it is inaudible). The enumerator names are guesses from
/// the behavior: 0 disables the virtualization (SoundSource::canVirtualize), 1 is the default, 2 restarts the sound when
/// it is unvirtualized (PlayingStateController::unvirtualize).
SEAD_ENUM(VirtualizeMode, Disable, Normal, Restart)

}  // namespace aal
