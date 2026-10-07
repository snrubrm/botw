#pragma once

namespace nn::atk {
class SoundArchivePlayer;
}

namespace aal {

/// Access to the nn::atk objects of the audio engine. TODO: only getSoundArchivePlayer is declared.
class ATKAccessor {
public:
    /// 0x7100b9ebc0 (declared only)
    static nn::atk::SoundArchivePlayer* getSoundArchivePlayer();
};

}  // namespace aal
