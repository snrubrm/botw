#include "KingSystem/Sound/sndMiiSound.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

Unk_710251b6f0::Unk_710251b6f0() {
    mPendingName.clear();
}

Unk_710251b6f0::~Unk_710251b6f0() {
    auto& requests = SoundMgr::instance()->_60->mMiiSoundRequests;
    auto lock = sead::makeScopedLock(requests.mCS);
    requests.mQueue.erase(this);
}

void Unk_710251b6f0::sub_71012CD7A4() {
    mTimer = 0.0f;
    _119 = false;
    _11a = false;
    mPendingName.clear();
    if (sub_71012CD880(mName, mIsMii)) {
        auto& requests = SoundMgr::instance()->_60->mMiiSoundRequests;
        requests.mQueue.push(this);
        _114 = requests.mCounter;
        if (mHandle.isSuccess())
            mState = 0;
    }
}

void Unk_710251b6f0::requestUnloadMaybe() {
    mHandle.requestUnload();
    mState = 0;
}

}  // namespace ksys::snd
