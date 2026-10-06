#pragma once

#include <basis/seadTypes.h>
#include "aal/aalDeviceType.h"

namespace aal {

/// The set of mixing parameters of a sound (volume, pitch, filters, ...). 0x40 bytes: SoundSource holds two of
/// them at +0x38 (the default parameters) and +0x78.
class SoundParam {
public:
    SoundParam();
    SoundParam(const SoundParam& other);
    virtual ~SoundParam() = default;

    void reset();
    static void copy(SoundParam* dst, const SoundParam& src);
    /// Whether the parameters are the initial parameters (0x7100b76758, declared only).
    static bool isInitial(const SoundParam& param);
    /// Aggregates `src` into `dst` (0x7100b764ec, declared only).
    static void aggregate(SoundParam* dst, const SoundParam& src);
    /// Aggregates `src1` and `src2` into `dst` (0x7100b7660c, declared only).
    static void aggregate(SoundParam* dst, const SoundParam& src1, const SoundParam& src2);

    void setVolume(f32 volume);
    f32 getVolume() const { return mVolume; }
    f32 getSpread() const { return mSpread; }
    void setPitch(f32 pitch);
    void setLfe(f32 lfe);
    void setLpf(f32 lpf);
    void setBiquadFilter(int type, f32 value);
    void setBiquadType(int type);
    void setBiquadValue(f32 value);
    void setAngleIdx(u32 index);
    void setSpread(f32 spread);
    void setAngle(f32 angle);
    void clampMinBusVolume();
    void clampExceptVolume();
    void setDeviceVolume(DeviceType device, f32 volume);
    void setBusVolume(BusType bus, f32 volume);

private:
    f32 mVolume;
    /// Per-device and per-bus volume overrides (-1: none); the index space is from the DeviceType / BusType
    /// enums (the setters add the index to +0xc / +0x10).
    f32 mDeviceVolume[1];
    f32 mBusVolume[4];
    f32 mPitch;
    f32 mLfe;
    f32 mLpf;
    int mBiquadType;
    f32 mBiquadValue;
    u32 mAngleIdx;
    f32 mSpread;
    u32 _3c;
};
static_assert(sizeof(SoundParam) == 0x40, "aal::SoundParam size mismatch");

}  // namespace aal
