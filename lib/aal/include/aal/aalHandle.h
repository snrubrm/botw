#pragma once

#include <basis/seadTypes.h>

namespace aal {

class SoundSource;

/// A reference to a playing sound: the sound source and the id the source had when the handle
/// was set up (sound sources are reused; a handle whose id differs from the source's is stale).
class Handle {
public:
    Handle();

    /// Returns the sound source if the handle is still valid (the ids match), nullptr otherwise.
    SoundSource* getSoundSource();

private:
    SoundSource* mSoundSource = nullptr;
    u32 mId = 0;
};
static_assert(sizeof(Handle) == 0x10, "aal::Handle size mismatch");

}  // namespace aal
