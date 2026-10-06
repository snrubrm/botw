#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// The description of an audio asset. TODO: only the flags read by SoundSource::isLooped are modeled.
class AssetInfo {
public:
    u8 _0[0x11];
    /// Bit 0: the asset is looped; bit 2: the prefetched data is ignored (SoundController::setIgnorePrefetch).
    u8 mFlags;
};

}  // namespace aal
