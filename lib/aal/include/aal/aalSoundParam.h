#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// The set of mixing parameters of a sound (volume, pitch, filters, ...). 0x40 bytes: SoundSource holds two of
/// them at +0x38 (the default parameters) and +0x78.
/// TODO: only the setters are declared; the fields are not modeled.
class SoundParam {
public:
    void setVolume(f32 volume);
    void setPitch(f32 pitch);
    void setLfe(f32 lfe);
    void setLpf(f32 lpf);
    void setBiquadFilter(int index, f32 value);
    void setBiquadType(int type);
    void setBiquadValue(f32 value);
    void setSpread(f32 spread);

private:
    u8 _0[0x40];
};
static_assert(sizeof(SoundParam) == 0x40, "aal::SoundParam size mismatch");

}  // namespace aal
