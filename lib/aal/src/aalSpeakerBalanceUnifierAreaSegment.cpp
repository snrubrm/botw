#include "aal/aalSpeakerBalanceUnifierArea.h"
#include <cfloat>

namespace aal {

// 0x7100b93ec0
SpeakerBalanceUnifierAreaSegment::SpeakerBalanceUnifierAreaSegment()
    : mPosition(sead::Vector3f::zero), mNearestSquaredDistance(FLT_MAX),
      mSquaredDistance(FLT_MAX), mHasPosition(false) {}

// 0x7100b93ee8
void SpeakerBalanceUnifierAreaSegment::reset() {
    mPosition.x = sead::Vector3f::zero.x;
    mPosition.y = sead::Vector3f::zero.y;
    mPosition.z = sead::Vector3f::zero.z;
    mNearestSquaredDistance = FLT_MAX;
    mSquaredDistance = FLT_MAX;
    mHasPosition = false;
}

// 0x7100b93f18
bool SpeakerBalanceUnifierAreaSegment::setSquaredDistanceIfNear(f32 squared_distance) {
    if (mNearestSquaredDistance > squared_distance) {
        mNearestSquaredDistance = squared_distance;
        mHasPosition = true;
        return true;
    }
    return false;
}

}  // namespace aal
