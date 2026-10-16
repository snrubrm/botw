#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <thread/seadAtomic.h>

namespace uking {

// Name from the CSV (WildHorseMgr::createInstance 0x7100e8c1f4, postCalc 0x7100e8c2c4; instance pointer
// 0x7102603db8; the namespace is a guess). Size 0x168. A non-virtual singleton (the first member is
// the disposer) that hands out four "active" slots to wild horse AIs (HorseLoopTargetAndWaitAI,
// WildHorseDefWanderAI, HorseFollow): a client (a pair {priority, slot index} embedded in the AI) is
// registered in `mPending`, and postCalc assigns the free slots by priority; a slot is released
// 30 frames after its client stopped refreshing it. Only the layout is known; names are guesses.
class WildHorseMgr {
    SEAD_SINGLETON_DISPOSER(WildHorseMgr)
    WildHorseMgr() = default;

public:
    // The part of a wild horse AI that talks to the manager (at +0x54 of WildHorseDefWanderAI).
    struct Client {
        /* 0x0 */ s8 priority;  // 0 - 2
        /* 0x1 */ s8 slot;      // index into mSlots, -1 if it has none
    };

    struct Slot {
        /* 0x00 */ Client* client;
        /* 0x08 */ s8 priority;
        /* 0x09 */ u8 timer;  // set to 30 while the client keeps the slot
    };
    static_assert(sizeof(Slot) == 0x10);

    // inline-only in the original; name is a guess (WildHorseDefWanderAI::calc_ repeats it four times): queues
    // `client` for postCalc with priority 0; true if it already holds its slot (a stale slot index is cleared).
    bool requestSlot(Client* client) {
        client->priority = 0;
        const s32 idx = mNumPending.increment();
        if (u32(idx) >= 32)
            return false;
        mPending[idx] = client;
        if (client->slot < 0)
            return false;
        if (mSlots[client->slot].client == client)
            return true;
        client->slot = -1;
        return false;
    }

    // 0x7100e8c2c4 (not decompiled)
    void postCalc(u32 flags);

    /* 0x20 */ sead::Atomic<s32> mBusy = 0;  // atomically set by the AI that may use the horse loop target (HorseLoopTargetAndWaitAI)
    /* 0x24 */ sead::Atomic<s32> mNumPending = 0;  // incremented with ldxr / stxr (WildHorseDefWanderAI::calc_)
    /* 0x28 */ sead::SafeArray<Slot, 4> mSlots;  // indexed by Client::slot (the original clamps the index like SafeArray)
    /* 0x68 */ Client* mPending[32];
};
static_assert(sizeof(WildHorseMgr) == 0x168);

}  // namespace uking
