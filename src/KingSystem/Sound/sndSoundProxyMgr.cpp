#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include <prim/seadScopedLock.h>
#include <aal/aalEmitter.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include <aal/aalSoundSource.h>
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

namespace ksys::snd {

// NON_MATCHING: asset/setup temporaries and the volume state have different stack placement.
void Unk_710105abc0::sub_710105B5D4(const sead::SafeString& name, bool use_barefoot, bool) {
    if (!_38.isOn(8)) {
        auto* list = &SoundMgr::instance()->_60->_828;
        aal::AssetInfo info;
        if (list->sub_710105CA84(&info, name, use_barefoot)) {
            aal::SoundSource::SetupInfo setup{};
            setup.prepare_flags = 3;
            if (auto* groups = aal::SystemAccessor::getGroupMgr())
                setup.sound_group = groups->findSoundGroupOrDefault("DemoMixed");
            _10 = _8->emit(info, &setup, nullptr);
            if (_10.isActive()) {
                _10.getSoundSource()->setInteriorNum(1);
                list->sub_710105CD4C(name, _10);
                _20.setValueImmediate(1.0f);
                if (auto* mgr = SoundMgr::instance()) {
                    f32 volume = _20.getValue();
                    if (mgr->_ec != 2)
                        volume *= _3c;
                    _10.setVolume(volume);
                    _10.setTrackVolume(4, mgr->sub_71011FC31C());
                }
            }
        }
    }
    if (_39) {
        if (!_38.isOn(16))
            SoundMgr::instance()->_30->_78->sub_71010078A0(sStr_RelicBeamBgm);
        if (name == "Demo143_4") {
            sub_710105B7D0();
            _39 = 0;
        }
    }
}

// NON_MATCHING: live control-flag reloads and ducker forwarding use different scheduling.
void Unk_710105abc0::sub_710105B934(const sead::SafeString&, bool defer_bgm) {
    if (!_39) {
        auto* bgm = SoundMgr::instance()->_30;
        if (!defer_bgm) {
            if (_38.isOn(1))
                bgm->sub_7100FF8780(0);
            if (_38.isOn(2))
                bgm->sub_7100FF88A8(0);
        } else {
            if (_38.isOn(1))
                bgm->_88 |= 2;
            if (_38.isOn(2))
                bgm->_88 |= 4;
        }
        _38.reset(3);
    }
    auto* ducking = SoundMgr::instance()->mDuckingMgr;
    ducking->sub_7101042D6C(DuckingMgr::DuckerType(0x1e), false);
    ducking->sub_7101042D6C(DuckingMgr::DuckerType(0x1b), false);
    ducking->sub_7101042D6C(DuckingMgr::DuckerType(0x1c), false);
    ducking->sub_7101042D6C(DuckingMgr::DuckerType(0x1d), false);
    if (_38.isOn(4)) {
        ducking->sub_7101042024(DuckingMgr::DuckerType(0x1a));
        _38.reset(4);
    }
    if (_10.isPaused(0x40))
        _10.pause(0x40, false, 0.0f);
}

}  // namespace ksys::snd
