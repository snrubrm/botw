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

private:
    u8 _58[0x68 - 0x58];
    ListenerDirectivity mDirectivity;
    u8 _e8[0xf8 - 0xe8];
    ListenerPoser* mPoser;
    u8 _100[0x1b0 - 0x100];
};
static_assert(sizeof(Listener) == 0x1b0, "aal::Listener size mismatch");

}  // namespace aal
