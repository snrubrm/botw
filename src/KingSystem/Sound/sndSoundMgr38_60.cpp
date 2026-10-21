#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndSound.h"
#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// The TU's static initialiser is 0x71012c1f6c.
namespace {
util::InitConstants sInitConstants;
util::InitTimeInfo sInitTimeInfo;
}  // namespace

// TU around 0x71012c167c in the original (far from the other sub-managers).

Unk_SoundMgr38_60::Unk_SoundMgr38_60() = default;

Unk_SoundMgr38_60::~Unk_SoundMgr38_60() = default;

Unk_SoundMgr38_60::Entry::~Entry() = default;

void Unk_SoundMgr38_60::Entry::m4(xlink2::UserInstanceSLink* user_instance) {}

void Unk_SoundMgr38_60::Entry::m5(xlink2::UserInstanceSLink* user_instance,
                                  xlink2::HandleSLink* handle) {
    if (handle)
        handle->setPosition(mPos);
}

void Unk_SoundMgr38_60::sub_71012C167C() {
    for (auto& entry : mEntries) {
        // called through a pointer in the original (not devirtualised)
        (&entry)->sub_710104A0D4();
    }
    if (mInstances) {
        mInstances->sub_710104993C();
        delete mInstances;
        mInstances = nullptr;
    }
}

// Empty in the release build.
void Unk_SoundMgr38_60::sub_71012C17B4() {}

void Unk_SoundMgr38_60::sub_71012C171C() {
    auto lock = sead::makeScopedLock(mCS);
    if (mInstances)
        mInstances->sub_7101049C60();
    for (auto& entry : mEntries) {
        // called through a pointer in the original (not devirtualised)
        (&entry)->sub_710104A1B8();
    }
}

// NON_MATCHING: the original keeps a candidate pointer across the free / not-busy passes (the select chains over
// the six entries start at entry 0, not null) and reuses it in the looping pass; our early returns give a shorter
// body (1104 B vs 1228 B).
Unk_SoundMgr38_60::Entry* Unk_SoundMgr38_60::sub_71012C1860(const sead::SafeString& name) {
    // An entry already bound to `name` that is ready and not busy.
    for (s32 i = 0; i < 6; ++i) {
        auto* user_instance = mEntries[i].getUserInstance();
        if (!user_instance)
            continue;
        const char* user_name = user_instance->getUserName();
        if (!user_name)
            continue;
        if (name == sead::SafeString(user_name) && mEntries[i].sub_710104A2E8() &&
            !mEntries[i].sub_710104A858()) {
            return &mEntries[i];
        }
    }

    Entry* result = nullptr;
    for (s32 i = 0; i < 6; ++i) {
        if (mEntries[i].sub_710104A8AC()) {
            result = &mEntries[i];
            break;
        }
    }
    if (!result) {
        for (s32 i = 0; i < 6; ++i) {
            if (!mEntries[i].sub_710104A858()) {
                result = &mEntries[i];
                break;
            }
        }
    }
    if (result)
        return result;

    // Every entry is busy: an entry bound to `name` that plays a looping event, else any looping entry.
    for (s32 i = 0; i < 6; ++i) {
        auto* user_instance = mEntries[i].getUserInstance();
        if (!user_instance)
            continue;
        const char* user_name = user_instance->getUserName();
        if (!user_name)
            continue;
        if (name == sead::SafeString(user_name) && mEntries[i].sub_710104A2E8() &&
            mEntries[i].mHandle.isActive() &&
            mEntries[i].mHandle.getEvent()->getBitFlag().isOnBit(4)) {
            return &mEntries[i];
        }
    }

    for (s32 i = 0; i < 6; ++i) {
        if (mEntries[i].mHandle.isActive() &&
            mEntries[i].mHandle.getEvent()->getBitFlag().isOnBit(4)) {
            result = &mEntries[i];
            break;
        }
    }
    return result;
}

s32 Unk_SoundMgr38_60::sub_71012C17B8(const sead::SafeString& name, const sead::Vector3f& pos,
                                      s32 value) {
    auto lock = sead::makeScopedLock(mCS);
    Entry* entry = sub_71012C1860(name);
    if (!entry)
        return -1;
    entry->mPos = pos;
    entry->sub_710104A308(name);
    const s32 id = mNextId;
    entry->mId = id;
    ++mNextId;
    entry->_b0 = value;
    return id;
}

void Unk_SoundMgr38_60::sub_71012C1D2C(s32 id, s32 frame) {
    if (id < 0)
        return;
    auto lock = sead::makeScopedLock(mCS);
    for (auto& entry : mEntries) {
        if (entry.mId == id) {
            entry.sub_710104A76C(frame);
            entry.mId = -1;
        }
    }
}

// NON_MATCHING: ours tail-calls sub_710104A858; the original masks its result with a found flag.
bool Unk_SoundMgr38_60::sub_71012C1E3C(s32 id) const {
    if (id < 0)
        return false;
    s32 index = -1;
    for (s32 i = 0; i < 6; ++i) {
        if (mEntries[i].mId == id) {
            index = i;
            break;
        }
    }
    return index >= 0 && mEntries[index].sub_710104A858();
}

}  // namespace ksys::snd
