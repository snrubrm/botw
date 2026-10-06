#include "aal/aalInterior.h"
#include <math/seadMathCalcCommon.h>
#include "aal/aalMeter.h"
#include "aal/aalSpeakerBalanceUnifierMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b85604
void Interior::setInteriorSize(f32 size) {
    if (size > 0.0f) {
        mInteriorSize = size;
        if (auto* mgr = SystemAccessor::getSpeakerBalanceUnifierMgr())
            mgr->setupInteriorSize();
    }
}

// 0x7100b8562c
f32 Interior::getInteriorSizeAsInGameLength() const {
    return Meter::toLength(mInteriorSize);
}

// 0x7100b856a0
f32 Interior::getFrontSpeakerAngle() const {
    return sead::Mathf::idx2rad(mFrontSpeakerAngle);
}

// 0x7100b856b8
f32 Interior::getRearSpeakerAngle() const {
    return sead::Mathf::idx2rad(mRearSpeakerAngle);
}

// 0x7100b856d0
void Interior::setRearSpeakerGain(f32 gain) {
    if (gain >= 0.0f && gain <= 1.0f)
        mRearSpeakerGain = gain;
}

}  // namespace aal
