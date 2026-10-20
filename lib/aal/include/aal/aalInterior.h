#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMathCalcCommon.h>
#include "aal/aalInteriorType.h"
#include "aal/aalNamedObj.h"
#include "aal/aalSpeakerChannel.h"

namespace sead {
class Heap;
}

namespace aal {

/// The speaker layout of the room a listener is in (the subclasses are the speaker setups).
/// TODO: incomplete.
class Interior : public NamedObj, public sead::hostio::Node {
public:
    virtual bool hasCenter() const = 0;
    virtual bool hasLFE() const = 0;
    virtual bool hasRear() const = 0;

    /// Creates the interior of the speaker setup `type` (0x7100b856ec).
    static Interior* create(InteriorType type, sead::Heap* heap);

    /// Ignores sizes that are not positive.
    void setInteriorSize(f32 size);
    f32 getInteriorSizeAsInGameLength() const;
    f32 getFrontSpeakerAngle() const;
    f32 getRearSpeakerAngle() const;
    /// Ignores gains outside of [0, 1].
    void setRearSpeakerGain(f32 gain);
    /// The angle (a sead angle index) of the speaker; the left speakers are the negated angles of the right ones.
    s32 getSpeakerChannelAngleIdx(SpeakerChannel channel) const;

protected:
    Interior(const sead::SafeString& name, f32 front_angle, f32 rear_angle);

private:
    f32 mInteriorSize;
    f32 _24;
    f32 mRearSpeakerGain;
    /// The angles are in sead angle indices (see Mathf::idx2rad).
    u32 mFrontSpeakerAngle;
    u32 mRearSpeakerAngle;
    sead::SafeArray<u32, 5> mAngleBoundaries;
};

static_assert(sizeof(Interior) == 0x48);

/// The speaker setups. The names follow the vtables' class names (the CSV).
class InteriorSquare : public Interior {
public:
    InteriorSquare();
    bool hasCenter() const override;
    bool hasLFE() const override;
    bool hasRear() const override;
};

class InteriorWide : public Interior {
public:
    InteriorWide();
    bool hasCenter() const override;
    bool hasLFE() const override;
    bool hasRear() const override;
};

class Interior5point1ch : public Interior {
public:
    Interior5point1ch();
    bool hasCenter() const override;
    bool hasLFE() const override;
    bool hasRear() const override;
};

class Interior4point1ch : public Interior {
public:
    Interior4point1ch();
    bool hasCenter() const override;
    bool hasLFE() const override;
    bool hasRear() const override;
};

class InteriorStereo : public Interior {
public:
    InteriorStereo();
    bool hasCenter() const override;
    bool hasLFE() const override;
    bool hasRear() const override;
};

// Inline-only in the original; the five factory cases share this initialization.
inline Interior::Interior(const sead::SafeString& name, f32 front_angle, f32 rear_angle)
    : NamedObj(name), mInteriorSize(1.0f), _24(0.0f), mRearSpeakerGain(1.0f),
      mFrontSpeakerAngle(sead::Mathf::deg2idx(front_angle)),
      mRearSpeakerAngle(sead::Mathf::deg2idx(rear_angle)),
      mAngleBoundaries{{0, mRearSpeakerAngle - mFrontSpeakerAngle,
                        -mFrontSpeakerAngle - mRearSpeakerAngle,
                        -2 * mFrontSpeakerAngle, -mFrontSpeakerAngle}} {}

inline InteriorStereo::InteriorStereo() : Interior("Stereo", 90.0f, 90.0f) {}
inline Interior5point1ch::Interior5point1ch() : Interior("5.1ch", 30.0f, 110.0f) {}
inline Interior4point1ch::Interior4point1ch() : Interior("4.1ch", 30.0f, 110.0f) {}
inline InteriorSquare::InteriorSquare() : Interior("Square", 45.0f, 135.0f) {}
inline InteriorWide::InteriorWide() : Interior("Wide", 60.0f, 110.0f) {}

}  // namespace aal
