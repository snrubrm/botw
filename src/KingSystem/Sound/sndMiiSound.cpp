#include "KingSystem/Sound/sndMiiSound.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Mii/miiUMii.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// Initialized by 0x71012ce620, followed by the four SafeString objects below.
// NON_MATCHING: the compiler places the initialization record after the strings in GlobalMerge.
static util::InitTimeInfoEx sMiiSoundInitTimeInfo;
static sead::SafeString sVoiceDirectory = "Voice/";
static sead::SafeString sCommonVoiceDirectory = "Voice/Common/";
static sead::SafeString sVoicePrefix = "NV_";
static sead::SafeString sCustomVoicePrefix = "Custom_";

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
    if (sub_71012CD880(mName, mIsCustomVoice)) {
        auto& requests = SoundMgr::instance()->_60->mMiiSoundRequests;
        requests.mQueue.push(this);
        _114 = requests.mCounter;
        if (mHandle.isSuccess())
            mState = 0;
    }
}

// NON_MATCHING: the static prefix string has a different GlobalMerge offset.
void Unk_710251b6f0::sub_71012CD4E8(sead::Heap*, mii::UMii* umii) {
    mName.clear();
    if (umii->getPersonal().voice_type.ref() == "None") {
        mState = 2;
    } else {
        mName.appendWithFormat("NV_%s", umii->getPersonal().voice_type.ref().cstr());
        mIsCustomVoice = umii->getPersonal().voice_type.ref().startsWith(sCustomVoicePrefix);
    }
}

// NON_MATCHING: the directory strings have different GlobalMerge offsets.
bool Unk_710251b6f0::sub_71012CD880(const sead::SafeString& name, bool is_custom_voice) {
    sead::FixedSafeString<128> path;
    if (is_custom_voice) {
        const char* directory = sVoiceDirectory.cstr();
        const char* locale = sub_710105E7B4(nullptr);
        path.format("%s%s/%s.bars", directory, locale, name.cstr());
    } else {
        path.format("%s%s.bars", sCommonVoiceDirectory.cstr(), name.cstr());
    }
    res::LoadRequest request;
    request.mLoadDataAlignment = 0x1000;
    request.mRequester = "Sound";
    request._22 = true;
    request.mLaneId = 2;
    request.mArena = SoundMgr::instance()->_60->mArena;
    return mHandle.requestLoad(path, &request);
}

// NON_MATCHING: the static prefix string has a different GlobalMerge offset.
bool Unk_710251b6f0::sub_71012CDA58(const sead::SafeString& name) const {
    if (mState == 2)
        return false;
    return name.startsWith(sVoicePrefix);
}

void Unk_710251b6f0::requestUnloadMaybe() {
    mHandle.requestUnload();
    mState = 0;
}

Unk_710251b710::Unk_710251b710() = default;

Unk_710251b710::~Unk_710251b710() {
    mQueue.freeBuffer();
}

}  // namespace ksys::snd
