#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class BaseProc;
}

namespace uking {

// CSV placeholder "RuneMgr::StructX" (ctor 0x710067e0a8, vtable at GOT 0x710258eb48; the TU 0x710067e0a8 -
// 0x710067f0ec also has doSpawnRemoteBomb). Three remote bomb slots, a MessageTransceiverTxOnly at 0x80 and a
// link at 0x108; only the slots are modelled. RemoteBomb::_198 points to it. Placeholder name = ctor address.
class Unk_710067e0a8 {
public:
    struct Slot {
        /* 0x00 */ ksys::act::BaseProcLink bomb;
        /* 0x10 */ ksys::act::BaseProcLink target;  // set with flag 0x10 by sub_710067EDDC
        /* 0x20 */ sead::BitFlag8 flags;
    };
    static_assert(sizeof(Slot) == 0x28);

    virtual ~Unk_710067e0a8();

    // 0x710067ed08: sets (`on`) or clears bit `bit` of the flags of every slot whose bomb is `bomb`.
    void sub_710067ED08(ksys::act::BaseProc* bomb, s32 bit, bool on);
    // 0x710067eddc: stores `target` in every slot whose bomb is `bomb` (flag 0x10).
    void sub_710067EDDC(ksys::act::BaseProc* bomb, const ksys::act::BaseProcLink& target);
    // 0x710067ee7c: clears the target (and flag 0x10) of every slot whose bomb is `bomb`.
    void sub_710067EE7C(ksys::act::BaseProc* bomb);

    /* 0x08 */ Slot mSlots[3];
};

}  // namespace uking
