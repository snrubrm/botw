#pragma once

#include <basis/seadTypes.h>
#include "aal/aalHandle.h"

namespace aal {

/// The part of a unified (merged) group of sounds that belongs to one SoundSource.
/// TODO: only the members SoundSource uses are declared.
class SoundSourceUnifierSource {
public:
    /// 0x7100b8ef88 (declared only)
    void pause(bool pause, f32 fade_time);
    /// 0x7100b8ef58 (declared only): the handle of the sound that plays the unified sources.
    Handle getTargetHandle() const;
};

/// TODO: only freeSource is declared.
class SoundSourceUnifier {
public:
    /// 0x7100b8ea64 (declared only): a negative fade time stops the target immediately.
    void freeSource(SoundSourceUnifierSource* source, f32 fade_time);
};

}  // namespace aal
