#pragma once

#include "aal/aalHandle.h"
#include "aal/aalSoundSource.h"

namespace aal {

class Attenuator;
class IUnifiable;
struct StartResult;

/// Plays one sound for several unifiable positions with a speaker balance that is calculated from all of them.
/// TODO: only the functions that SoundSourceUnifierTarget calls are declared.
class SpeakerBalanceUnifier {
public:
    /// 0x7100b92ac4 (declared only)
    void setAttenuator(Attenuator* attenuator);
    /// 0x7100b92b34 (declared only)
    void setInteriorNum(s32 num);
    /// 0x7100b92c18 (declared only)
    void setListenerDirectivityEnabled(bool enabled);
    /// 0x7100b926b0 (declared only)
    void addUnifiable(IUnifiable* unifiable);
    /// 0x7100b9273c (declared only)
    void removeUnifiable(IUnifiable* unifiable);

    u8 _0[0x118];
    /// Which interiors the sounds are heard from (copied from the spatial calculator setting).
    u16 mInteriorMask;
};

}  // namespace aal
