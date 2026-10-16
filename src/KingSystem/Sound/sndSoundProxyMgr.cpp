#include "KingSystem/Sound/sndSound.h"
#include <prim/seadScopedLock.h>
#include "Game/Actor/actSoundProxy.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// The TU statics at 0x7102615170 (static initialiser 0x710105ab34; the array destructor is the empty
// 0x710105ab30). Names are guesses. 0x710105ba88 (emitter TU, not decompiled) reads sStr_RelicBeamBgm, so the
// original's is a global; it is TU-local here so that GlobalMerge keeps the original layout.
namespace {
util::InitTimeInfo sInitTimeInfo;
util::InitConstants sInitConstants;
sead::SafeString sStr_RelicBeamBgm = "RelicBeamBgm";
sead::SafeString sStr_Demo143[4] = {"Demo143_0", "Demo143_1", "Demo143_2", "Demo143_3"};
}  // namespace

Unk_710105a6f0::Unk_710105a6f0() = default;

Unk_710105a6f0::~Unk_710105a6f0() { _0 = false; }

void Unk_710105a6f0::sub_710105A718() {
    if (!_0) {
        mProxies.initOffset(offsetof(uking::act::SoundProxy, mManagerNode));
        _0 = true;
    }
}

void Unk_710105a6f0::sub_710105A734(uking::act::SoundProxy* proxy) {
    if (proxy && !mProxies.isNodeLinked(proxy)) {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        mProxies.pushBack(proxy);
    }
}

void Unk_710105a6f0::sub_710105A7B4(uking::act::SoundProxy* proxy) {
    if (proxy && mProxies.isNodeLinked(proxy)) {
        sead::ScopedLock<sead::CriticalSection> lock(&mCS);
        mProxies.erase(proxy);
    }
}

uking::act::SoundProxy* Unk_710105a6f0::sub_710105A830(map::Object* object) {
    if (!object)
        return nullptr;
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (auto& proxy : mProxies) {
        if (proxy.mSourceMapObject == object)
            return &proxy;
    }
    return nullptr;
}

}  // namespace ksys::snd
