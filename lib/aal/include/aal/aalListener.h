#pragma once

#include <hostio/seadHostIONode.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadSafeString.h>
#include "aal/aalListenerDirectivity.h"
#include "aal/aalNamedObj.h"

namespace aal {

class ListenerPoser;

/// A listener of the sounds (the position and orientation sounds are heard from). TODO: incomplete.
class Listener : public FixedNamedObj<32>, public sead::hostio::Node {
public:
    Listener();
    ~Listener() override;

    void setObjName(const sead::SafeString& name) override;

    void setPoser(ListenerPoser* poser);

    /// The position of `position` relative to the listener.
    void calcLocalPosition(sead::Vector3f* out, const sead::Vector3f& position) const;
    /// The distance of `position` to the listener.
    f32 calcLocalDistance(const sead::Vector3f& position) const;
    /// Same as calcLocalPosition, with the other basis that is used for the angle calculation.
    void calcLocalPositionForAngle(sead::Vector3f* out, const sead::Vector3f& position) const;
    /// Purpose unknown (the byte at 0xf0 selects between the two bases of calcLocalPositionForAngle).
    bool isFlag0xf0() const { return _f0; }

private:
    u8 _58[0x68 - 0x58];
    ListenerDirectivity mDirectivity;
    /// Sounds are positioned on the horizontal plane only (the height is ignored).
    bool mIs2D;
    u8 _e9[0xf0 - 0xe9];
    bool _f0;
    u8 _f1[0xf8 - 0xf1];
    ListenerPoser* mPoser;
    /// The inverse of the listener matrix.
    sead::Matrix34f mLocalMatrix;
    sead::Matrix34f mMatrix;
    sead::Matrix34f mLocalMatrixForAngle;
    u8 _190[0x1b0 - 0x190];
};
static_assert(sizeof(Listener) == 0x1b0, "aal::Listener size mismatch");

}  // namespace aal
