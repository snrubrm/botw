#include "Game/gameWildHorseMgr.h"
#include <container/seadSafeArray.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadBitFlag.h>

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(WildHorseMgr)

// 0x7100e8c2c4: refreshes the slots of the wild horses that requested one this frame (or ages the slots that were
// not refreshed), then hands the free slots to the queued clients from the highest priority down.
// NON_MATCHING: the clear of mNumPending goes through a spilled address in ours (the original stores to the member);
// the expire chain's masks are materialised with csel instead of cset and the counts/buckets stack slots are 0x10
// apart.
void WildHorseMgr::postCalc(u32 flags) {
    if (!(flags & 1)) {
        s32 counts[3] = {};
        sead::SafeArray<sead::SafeArray<Client*, 32>, 3> buckets;
        u32 free_slots = 0xf;
        u32 priority0_slots = 0;
        const u32 num_pending = u32(sead::Mathf::clampMax(mNumPending, 32.0f));
        for (u32 i = 0; i < num_pending; ++i) {
            if (mPending[i]->slot >= 0 && mSlots[mPending[i]->slot].client == mPending[i]) {
                mSlots[mPending[i]->slot].timer = 30;
                mSlots[mPending[i]->slot].priority = mPending[i]->priority;
                free_slots &= ~(1u << mPending[i]->slot);
                if (mPending[i]->priority < 1)
                    priority0_slots |= 1u << mPending[i]->slot;
            } else {
                mPending[i]->slot = -1;
                buckets[mPending[i]->priority][counts[mPending[i]->priority]++] = mPending[i];
            }
        }

        for (s32 i = 0; i < 4; ++i) {
            if (!(free_slots & (1u << i)))
                continue;
            if (mSlots[i].timer == 0) {
                mSlots[i].client = nullptr;
                continue;
            }
            --mSlots[i].timer;
            free_slots &= ~(1u << i);
            if (mSlots[i].priority < 1)
                priority0_slots |= 1u << i;
        }

        for (s32 level = 2; level >= 0; --level) {
            if (counts[level] < 1)
                continue;
            if (level == 0) {
                for (s32 j = 0; j < counts[0]; ++j) {
                    const s32 slot = sead::BitFlagUtil::countContinuousOffBitFromRight(free_slots);
                    if (slot > 3) {
                        mNumPending = 0;
                        return;
                    }
                    free_slots &= ~(1u << slot);
                    Client* client = buckets[0][j];
                    mSlots[slot].timer = 30;
                    mSlots[slot].client = client;
                    client->slot = slot;
                }
            } else {
                for (s32 j = 0; j < counts[level]; ++j) {
                    s32 slot = sead::BitFlagUtil::countContinuousOffBitFromRight(free_slots);
                    if (slot > 3) {
                        slot = sead::BitFlagUtil::countContinuousOffBitFromRight(priority0_slots);
                        if (slot > 3) {
                            mNumPending = 0;
                            return;
                        }
                        priority0_slots &= ~(1u << slot);
                    } else {
                        free_slots &= ~(1u << slot);
                    }
                    Client* client = buckets[level][j];
                    mSlots[slot].client = client;
                    mSlots[slot].timer = 30;
                    client->slot = slot;
                }
            }
        }
    }
    mNumPending = 0;
}

}  // namespace uking
