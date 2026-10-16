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
