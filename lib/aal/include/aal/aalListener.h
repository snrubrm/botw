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
    friend class Shape;

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
    /// The matrix `matrix` relative to the listener (with the basis of the angle calculation).
    void calcLocalMatrixForAngle(sead::Matrix34f* out, const sead::Matrix34f& matrix) const;
    /// Purpose unknown (the byte at 0xf0 selects between the two bases of calcLocalPositionForAngle).
    bool isFlag0xf0() const { return _f0; }

private:
    f32 _58;
    f32 _5c;
    void* _60;
    ListenerDirectivity mDirectivity;
    /// Sounds are positioned on the horizontal plane only (the height is ignored).
    bool mIs2D;
    u8 _e9[0xec - 0xe9];
    f32 _ec;
    bool _f0;
    u8 _f1[0xf8 - 0xf1];
    ListenerPoser* mPoser;
    /// The inverse of the listener matrix.
    sead::Matrix34f mLocalMatrix = sead::Matrix34f::ident;
    sead::Matrix34f mMatrix = sead::Matrix34f::ident;
    sead::Matrix34f mLocalMatrixForAngle = sead::Matrix34f::ident;
    /// The position that the angle calculation uses if the byte at 0xf0 is set.
    sead::Vector3f mPositionForAngle = sead::Vector3f::zero;
    sead::Vector3f _19c = sead::Vector3f::zero;
    bool _1a8;
    u8 _1a9[0x1ac - 0x1a9];
    u32 _1ac;
};
static_assert(sizeof(Listener) == 0x1b0, "aal::Listener size mismatch");

}  // namespace aal
