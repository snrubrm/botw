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

    void setPoser(ListenerPoser* poser) { mPoser = poser; }

    /// The position of `position` relative to the listener (0x7100b846a4, declared only).
    void calcLocalPosition(sead::Vector3f* out, const sead::Vector3f& position) const;
    /// Same, with the other basis that is used for the angle calculation (0x7100b84804, declared only).
    void calcLocalPositionForAngle(sead::Vector3f* out, const sead::Vector3f& position) const;
    /// Purpose unknown (the byte at 0xf0 selects between the two bases of calcLocalPositionForAngle).
    bool isFlag0xf0() const { return _f0; }

private:
    u8 _58[0x68 - 0x58];
    ListenerDirectivity mDirectivity;
    u8 _e8[0xf0 - 0xe8];
    bool _f0;
    u8 _f1[0xf8 - 0xf1];
    ListenerPoser* mPoser;
    u8 _100[0x1b0 - 0x100];
};
static_assert(sizeof(Listener) == 0x1b0, "aal::Listener size mismatch");

}  // namespace aal
