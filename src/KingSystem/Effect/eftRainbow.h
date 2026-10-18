#pragma once

#include <math/seadVector.h>
#include <xlink2/xlink2HandleELink.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::eft {

// Effect constructs this 0x70-byte weather effect at +0x19370. The update emits
// Rainbow and Rainbow_Mirror; the parameter names are inferred from their uses.
class Rainbow {
public:
    void start();
    void stop();
    void calc();

    u8 mFlags = 0;
    u8 _1[3];
    f32 mDelay = 0.0f;
    f32 mDelayDuration = 5.0f;
    f32 mTimeLeft = 0.0f;
    f32 mDuration = 60.0f;
    f32 mFadeTime = 10.0f;
    f32 mAlpha = 1.0f;
    f32 mRandomFactor = 1.0f;
    f32 mDistance = 2000.0f;
    f32 mScaleMin = 5500.0f;
    f32 mScaleMax = 7000.0f;
    f32 mPowerMin = 0.4f;
    f32 mPowerMax = 0.8f;
    f32 mMirrorScale = 1.45f;
    f32 mMirrorPower = 0.5f;
    bool mEnabled = false;
    u8 _3d[3];
    sead::Vector3f mDirection;
    u8 _4c[4];
    xlink2::HandleELink mRainbow;
    xlink2::HandleELink mMirror;
};
KSYS_CHECK_SIZE_NX150(Rainbow, 0x70);
static_assert(offsetof(Rainbow, mDirection) == 0x40);
static_assert(offsetof(Rainbow, mRainbow) == 0x50);

}  // namespace ksys::eft
