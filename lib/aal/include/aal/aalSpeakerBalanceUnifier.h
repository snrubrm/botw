#pragma once

#include "aal/aalHandle.h"
#include "aal/aalSoundSource.h"

namespace aal {

class IUnifiable;
struct StartResult;

/// Plays one sound for several unifiable positions with a speaker balance that is calculated from all of them.
/// TODO: only the functions that SoundSourceUnifierTarget calls are declared.
class SpeakerBalanceUnifier {
public:
    /// 0x7100b926b0 (declared only)
    void addUnifiable(IUnifiable* unifiable);
    /// 0x7100b9273c (declared only)
    void removeUnifiable(IUnifiable* unifiable);
};

}  // namespace aal
