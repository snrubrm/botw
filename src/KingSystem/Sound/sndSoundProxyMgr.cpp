#include "KingSystem/Sound/sndMgr.h"
#include <prim/seadScopedLock.h>
#include "Game/Actor/actSoundProxy.h"

namespace ksys::snd {

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
