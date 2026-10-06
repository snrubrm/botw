#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace sead {
class Heap;
}

namespace aal {

class Attenuator;

/// One angular segment of a SpeakerBalanceUnifierArea: the nearest registered position.
class SpeakerBalanceUnifierAreaSegment {
public:
    SpeakerBalanceUnifierAreaSegment();

    void reset();
    /// Remembers the squared distance (and returns true) if it is smaller than the current one.
    bool setSquaredDistanceIfNear(f32 squared_distance);

    sead::Vector3f mPosition;
    f32 mNearestSquaredDistance;
    f32 mSquaredDistance;
    bool mHasPosition;
};

/// TODO: incomplete. calcSpeakerBalance and calcAttenuationExceptVolume_ are not declared.
class SpeakerBalanceUnifierArea {
public:
    static constexpr s32 cSegmentNum = 64;

    SpeakerBalanceUnifierArea();
    ~SpeakerBalanceUnifierArea();

    void initialize(sead::Heap* heap);
    void reset();
    void finalize();
    void initParams();
    /// Registers `position` in the segment that `direction` points to. Returns whether it was registered.
    bool registerPosition(const sead::Vector3f& position, const sead::Vector3f& direction);

    void setAttenuator(Attenuator* attenuator);
    void setRegisterCullingDistance(f32 distance);
    void setInteriorNum(s32 num);
    void setSpread(f32 spread);
    void setListenerDirectivityEnabled(bool enabled) { _214 = enabled; }

private:
    SpeakerBalanceUnifierAreaSegment* mSegments[cSegmentNum];
    Attenuator* mAttenuator;
    f32 mRegisterCullingDistanceSquared;
    s32 mInteriorNum;
    f32 mSpread;
    bool _214;
};

}  // namespace aal
