#pragma once

#include <basis/seadTypes.h>

namespace gsys {

// Per-placement records. ParticleScene::initialize 0x7100c56210 allocates them with
// new[] at strides 0x58 / 0x2c / 0x7c; only their sizes are modelled.
struct EffectLightData {
    u8 _0[0x58];
};
struct EffectLensFlareData {
    u8 _0[0x2c];
};
struct EffectRadialBlurData {
    u8 _0[0x7c];
};

// The placement callback store. ParticleScene::initialize allocates 0x28 bytes, sets +0x24
// to the capacity, allocates 3 * capacity records and stores 3 / capacity at +0x8 / +0xc;
// clearPlacementData 0x7100c565a0 zeroes +0x18 / +0x20.
template <typename T>
class EffectPlaceMentCallbackMgr {
public:
    // 0x7100c565dc / 0x7100c566cc / 0x7100c56744 (D2)
    virtual ~EffectPlaceMentCallbackMgr() {
        if (mBuffer) {
            delete[] mBuffer;
            mBuffer = nullptr;
            mBufferNum = 0;
            mCapacity = 0;
        }
    }

protected:
    s32 mBufferNum = 0;
    s32 mCapacity = 0;
    T* mBuffer = nullptr;
    u64 _18 = 0;
    u32 _20 = 0;
    s32 _24 = 0;
};

// The vtables at 0x71024cf0c8 / 0x71024cf108 / 0x71024cf148 hold the base D2 and a D0
// that stores the base vtable: these subclasses add no members.
class EffectLightMgr : public EffectPlaceMentCallbackMgr<EffectLightData> {
public:
    ~EffectLightMgr() override;
};

class EffectLensFlareMgr : public EffectPlaceMentCallbackMgr<EffectLensFlareData> {
public:
    ~EffectLensFlareMgr() override;
};

}  // namespace gsys
