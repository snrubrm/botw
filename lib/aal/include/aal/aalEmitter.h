#pragma once

namespace aal {

class SoundSource;

/// Emits sounds (SoundSource) and keeps track of the ones that are playing. TODO: only removeSoundSource is
/// declared.
class Emitter {
public:
    /// 0x7100b9f264 (declared only)
    void removeSoundSource(SoundSource* sound_source);
};

}  // namespace aal
