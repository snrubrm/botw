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

// 0x7100b85a38
bool InteriorSquare::hasCenter() const {
    return false;
}

// 0x7100b85a40
bool InteriorSquare::hasLFE() const {
    return false;
}

// 0x7100b85a48
bool InteriorSquare::hasRear() const {
    return true;
}

// 0x7100b85a54
bool InteriorWide::hasCenter() const {
    return false;
}

// 0x7100b85a5c
bool InteriorWide::hasLFE() const {
    return false;
}

// 0x7100b85a64
bool InteriorWide::hasRear() const {
    return true;
}

// 0x7100b85a70
bool Interior5point1ch::hasCenter() const {
    return true;
}

// 0x7100b85a78
bool Interior5point1ch::hasLFE() const {
    return true;
}

// 0x7100b85a80
bool Interior5point1ch::hasRear() const {
    return true;
}

// 0x7100b85a8c
bool Interior4point1ch::hasCenter() const {
    return false;
}

// 0x7100b85a94
bool Interior4point1ch::hasLFE() const {
    return true;
}

// 0x7100b85a9c
bool Interior4point1ch::hasRear() const {
    return true;
}

// 0x7100b85aac
bool InteriorStereo::hasCenter() const {
    return false;
}

// 0x7100b85ab4
bool InteriorStereo::hasLFE() const {
    return false;
}

// 0x7100b85abc
bool InteriorStereo::hasRear() const {
    return false;
}

}  // namespace aal
