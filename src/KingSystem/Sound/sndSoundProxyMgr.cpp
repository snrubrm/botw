#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Sound/sndBgmMgr.h"
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

// NON_MATCHING: the original re-masks the mask to 64 bits for the callee; ours reuses the byte test.
void Unk_710105abc0::sub_710105B0C8(const sead::SafeString& name, res::Handle* pack, u8 mask) {
    if ((mask & 0xff) != 0)
        sub_710105B0F0(name, mask);
    else
        SoundMgr::instance()->_60->_828.sub_710105C3D0(name, pack);
}

// NON_MATCHING: the original unrolled loop keeps its induction variable on the stack; ours folds
// the bit tests into tbz.
void Unk_710105abc0::sub_710105B0F0(const sead::SafeString& name, u8 mask) {
    SoundMgr::instance()->_30->_78->sub_710100754C(sStr_RelicBeamBgm);
    auto* list = &SoundMgr::instance()->_60->_828;
    for (s32 i = 0; i < 4; ++i) {
        if (mask & (1 << i))
            list->sub_710105C3D0(sStr_Demo143[i], nullptr);
    }
    _39 = mask;
}

// NON_MATCHING: the unrolled resource loop keeps its induction variable on the stack in the
// original; ours folds the bit tests into tbz and tail-calls the last load.
bool Unk_710105abc0::sub_710105B224(const sead::SafeString& name) {
    if (!_39)
        return SoundMgr::instance()->_60->_828.sub_710105C70C(name);

    bool finished = SoundMgr::instance()->_30->_78->isFinished(sStr_RelicBeamBgm);
    auto* list = &SoundMgr::instance()->_60->_828;
    for (s32 i = 0; i < 4; ++i) {
        if (_39 & (1 << i))
            finished = finished && list->sub_710105C70C(sStr_Demo143[i]);
    }
    return finished;
}

// NON_MATCHING: the original unrolled loop keeps its induction variable on the stack; ours folds
// the bit tests into tbz.
void Unk_710105abc0::sub_710105B7D0() {
    SoundMgr::instance()->_30->_78->release(sStr_RelicBeamBgm);
    auto* list = &SoundMgr::instance()->_60->_828;
    s32 i;
    for (i = 0; i < 4; ++i) {
        if (_39 & (1 << i))
            list->sub_710105C96C(sStr_Demo143[i]);
    }
}

void Unk_710105abc0::sub_710105BA88() {
    if (_39)
        return;
    SoundMgr::instance()->_30->_78->sub_7101007904(0.0f, sStr_RelicBeamBgm);
}

}  // namespace ksys::snd
