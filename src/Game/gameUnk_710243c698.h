#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include "Game/Actor/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverTxOnly.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class BaseProc;
}

namespace uking {

// Sender at Unk_710243c698::_d0 (vtable 0x710243c6c0; message 0x800003c): the payload is the owner
// (set by Unk_710243c698::sub_710067E2B4). D1 is Unk_7102357d20's, D0 0x710067f0e8, m2 0x710067f0ec.
class Unk_710243c6c0 : public Unk_7102357d20 {
public:
    Unk_710243c6c0(ksys::MessageTransceiverBase* transceiver, u32 type)
        : Unk_7102357d20(transceiver, type) {}
    void* m2() override { return &_18; }

    void* _18 = nullptr;
};

// RuneMgr::_2a8 (CSV RuneMgr::StructX; ctor 0x710067e0a8, vtable 0x710243c698: D1 0x710067e16c,
// D0 0x710067e20c, handleAck 0x710067ef10). Tracks the three remote bombs (round, square and the
// second round bomb of the Lv2 rune?): each entry links the bomb actor and the actor that carries it.
// Placeholder name = vtable address. TU 0x710067e0a8-0x710067f0f0.
class Unk_710243c698 : public ksys::MessageTransceiverTxOnly::IHandler {
public:
    struct Entry {
        /* 0x00 */ ksys::act::BaseProcLink bomb;
        /* 0x10 */ ksys::act::BaseProcLink _10;  // set by sub_710067EDDC (with flag 0x10)
        /* 0x20 */ sead::BitFlag8 flags;  // 2: ack success (0x800003c), 4: detonating, 0x10: _10 set
    };
    KSYS_CHECK_SIZE_NX150(Entry, 0x28);

    Unk_710243c698();
    ~Unk_710243c698() override;
    void handleAck(const ksys::MessageAck& ack) override;

    // 0x710067e2b4: clears the bomb links and flags and points the _d0 payload at this.
    void sub_710067E2B4();
    // 0x710067e2f8: per-frame update of the three entries.
    void sub_710067E2F8();
    // 0x710067e4e0: whether entry `idx` has a bomb that is not fading out.
    bool sub_710067E4E0(s32 idx);
    // 0x710067e55c: detonates the bomb of entry `idx` (message 0x800000a).
    bool sub_710067E55C(s32 idx);
    // 0x710067e838: removes the bomb of entry `idx` (message 0x8000004, or deleteLater
    // when it is not calculating).
    void sub_710067E838(s32 idx);
    // 0x710067e968 (CSV doSpawnRemoteBomb): creates the remote bomb actor of entry `idx` (type 1: cube,
    // 2: boomerang when enabled, else round; "2" variants with the Lv2 rune) at `mtx` unless the entry
    // already has one; returns the new actor (null if none was created).
    ksys::act::Actor* doSpawnRemoteBomb(s32 idx, const sead::Matrix34f& mtx, s32 type, bool a4);
    // 0x710067eb24: distance from `pos` to the bomb of entry `idx` (FLT_MAX without one).
    f32 sub_710067EB24(s32 idx, const sead::Vector3f& pos);
    // 0x710067ec28: the direction (degrees, atan2 of x / z) from `pos` to the bomb of entry `idx`.
    f32 sub_710067EC28(s32 idx, const sead::Vector3f& pos);
    // 0x710067ed08: sets (`on`) or clears the flag bit `bit` of the entries whose bomb is `proc`
    // (RemoteBomb::leave_ clears bit 0).
    void sub_710067ED08(ksys::act::BaseProc* proc, s32 bit, bool on);
    // 0x710067eddc: links `link` to the entries whose bomb is `proc` and sets flag 0x10.
    void sub_710067EDDC(ksys::act::BaseProc* proc, const ksys::act::BaseProcLink& link);
    // 0x710067ee7c: resets the second link and clears flag 0x10 of the entries whose bomb is `proc`.
    void sub_710067EE7C(ksys::act::BaseProc* proc);

    // Inline-only in the original; names are guesses. Each one acquires the linked actor into a temporary
    // accessor that is destroyed before the result is used (repeated in sub_710067E2F8, sub_710067E4E0,
    // sub_710067E55C, sub_710067E838, doSpawnRemoteBomb, sub_710067EB24, sub_710067EC28 and handleAck).
    static bool isFadingOut(const ksys::act::BaseProcLink& link) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        return accessor.sub_7100D0F180();
    }
    static const ksys::MesTransceiverId* getTransceiverId(const ksys::act::BaseProcLink& link) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        return accessor.getMessageTransceiverId();
    }

    /* 0x008 */ sead::SafeArray<Entry, 3> mEntries;
    /* 0x080 */ ksys::MessageTransceiverTxOnly mTransceiver{this};
    /* 0x0d0 */ Unk_710243c6c0 _d0{&mTransceiver, 0x800003c};
    /* 0x0f0 */ Unk_7102381468 _f0{&mTransceiver, 0x8000042};
};
KSYS_CHECK_SIZE_NX150(Unk_710243c698, 0x120);

}  // namespace uking
