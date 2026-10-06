#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include "aal/aalNamedObj.h"
#include "aal/aalSpeakerChannel.h"

namespace sead {
class Heap;
}

namespace aal {

enum class InteriorType : u32;

/// The speaker layout of the room a listener is in (the subclasses are the speaker setups).
/// TODO: incomplete.
class Interior : public NamedObj, public sead::hostio::Node {
public:
    virtual bool hasCenter() const = 0;
    virtual bool hasLFE() const = 0;
    virtual bool hasRear() const = 0;

    /// Creates the interior of the speaker setup `type` (0x7100b856ec, declared only).
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

private:
    f32 mInteriorSize;
    u8 _24[4];
    f32 mRearSpeakerGain;
    /// The angles are in sead angle indices (see Mathf::idx2rad).
    u32 mFrontSpeakerAngle;
    u32 mRearSpeakerAngle;
};


/// The speaker setups. The names follow the vtables' class names (the CSV).
class InteriorSquare : public Interior {
public:
    bool hasCenter() const override;
    bool hasLFE() const override;
    bool hasRear() const override;
};

class InteriorWide : public Interior {
public:
    bool hasCenter() const override;
    bool hasLFE() const override;
    bool hasRear() const override;
};

class Interior5point1ch : public Interior {
public:
    bool hasCenter() const override;
    bool hasLFE() const override;
    bool hasRear() const override;
};

class Interior4point1ch : public Interior {
public:
    bool hasCenter() const override;
    bool hasLFE() const override;
    bool hasRear() const override;
};

class InteriorStereo : public Interior {
public:
    bool hasCenter() const override;
    bool hasLFE() const override;
    bool hasRear() const override;
};

}  // namespace aal
