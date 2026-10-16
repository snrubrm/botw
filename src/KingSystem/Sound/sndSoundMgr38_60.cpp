#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndSound.h"

namespace ksys::snd {

// TU around 0x71012c167c in the original (far from the other sub-managers).

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

}  // namespace ksys::snd
