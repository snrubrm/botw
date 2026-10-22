#include "Game/Actor/Damage/dmgUnk_7100671794.h"
#include <prim/seadScopedLock.h>
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/System/Timer.h"

namespace uking::act {

// NON_MATCHING: the type-info / player position loads are scheduled differently and the compaction
// loop is strength-reduced to another index shape; the operations and order are the same.
void Unk_7100671794::sub_7100671794() {
    if (_c0 > 0.0f)
        ksys::Timer::update(&_c0, -1.0f);

    const sead::Vector3f player_pos = getPlayerPosition();
    for (s32 i = 0; i < 8; ++i) {
        auto& entry = mEntries[i];
        if (entry.mLink.hasProc()) {
            auto* proc = entry.mLink.getProc(nullptr, nullptr);
            auto* actor = sead::IsDerivedFrom<ksys::act::Actor>(proc)
                              ? static_cast<ksys::act::Actor*>(proc)
                              : nullptr;
            sead::Vector3f pos;
            actor->getMtx().getTranslation(pos);
            entry.mDistance = (pos - player_pos).length();
            entry._14 = ksys::sub_7100D8C4F8(pos);
        } else {
            for (s32 j = i + 1; j < 8; ++j)
                mEntries[j - 1] = mEntries[j];
            mEntries[7].mLink.reset();
        }
    }

    _c8 = 0;
    for (s32 i = 0; i < 8; ++i) {
        if (mEntries[i].mLink.hasProcInCalcState())
            ++_c8;
    }
}

bool Unk_7100671794::tryClaimSingleActorSlot(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::JobQueueLock> lock(&_d0);
    const u32 id = proc->getId();
    if (_c4 == -1) {
        _c4 = id;
        return true;
    }
    return _c4 == id;
}

bool Unk_7100671794::sub_7100671A40(ksys::act::BaseProc* proc, s32 frames) {
    if (_c0 > 0.0f)
        return false;
    _c0 = f32(frames);
    return true;
}

bool Unk_7100671794::sub_7100671A64(ksys::act::BaseProc* proc) const {
    return _c0 <= 0.0f;
}

// NON_MATCHING: our duplicate check branches through a shared return-value flag instead of `tbnz`
// straight to the return-true block (16 extra bytes), so the frame is 0xa0 instead of 0x90.
// 0x7100671a74: inserts the entry into the distance-sorted list of 8. Each occupied entry that is
// at least as near (with 10 m slack for entries already past that margin) uses up one of the
// allowed `count` slots; when they run out the entry is not inserted. Returns true otherwise.
bool Unk_7100671794::sub_7100671A74(Unk_7100671794_Entry* entry, s32 count) {
    sead::ScopedLock<sead::JobQueueLock> lock(&_cc);

    for (s32 i = 0; i < 8; ++i) {
        if (mEntries[i].mLink == entry->mLink)
            return true;
    }

    for (s32 i = 0; i < 8; ++i) {
        auto& e = mEntries[i];
        if (e.mLink.hasProc()) {
            const f32 slack = e._14 ? 10.0f : 0.0f;
            if (entry->mDistance < e.mDistance - slack) {
                for (s32 j = i + 1; j < 8; ++j)
                    mEntries[j - 1] = mEntries[j];
                mEntries[7].mLink.reset();
                break;
            }
            --count;
        }
        if (count < 1)
            return false;
    }

    for (s32 i = 0; i < 8; ++i) {
        auto& e = mEntries[i];
        if (!e.mLink.hasProc()) {
            mEntries[i] = *entry;
            return true;
        }
        if (entry->mDistance < e.mDistance) {
            for (s32 j = 6; j >= i; --j)
                mEntries[j + 1] = mEntries[j];
            mEntries[i] = *entry;
            return true;
        }
    }
    return true;
}

bool Unk_7100671794::sub_7100671ED8(ksys::act::BaseProc* proc) {
    return mEntries[0].mLink.hasProcById(proc) || mEntries[1].mLink.hasProcById(proc) ||
           mEntries[2].mLink.hasProcById(proc) || mEntries[3].mLink.hasProcById(proc) ||
           mEntries[4].mLink.hasProcById(proc) || mEntries[5].mLink.hasProcById(proc) ||
           mEntries[6].mLink.hasProcById(proc) || mEntries[7].mLink.hasProcById(proc);
}

bool Unk_7100671794::sub_7100671F78(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::JobQueueLock> lock(&_cc);
    bool found = false;
    for (int i = 0; i < 8; ++i) {
        found |= mEntries[i].mLink.hasProcById(proc);
        if (found) {
            if (i <= 6) {
                auto& next = mEntries[i + 1];
                mEntries[i].mLink = next.mLink;
                mEntries[i].mDistance = next.mDistance;
                mEntries[i]._14 = next._14;
            } else {
                mEntries[i].mLink.reset();
            }
        }
    }
    return found;
}

void Unk_7100671794::sub_71006720C8(ksys::act::BaseProc* proc) {
    sead::ScopedLock<sead::JobQueueLock> lock(&_d0);
    _c4 = -1;
}

}  // namespace uking::act
