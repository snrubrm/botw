#include "KingSystem/Sound/sndSound.h"
#include <prim/seadScopedLock.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndFxMgr.h"

namespace ksys::snd {

void Unk_710104e5b4::sub_710104F030() {
    _38.fade(0);
    mFilter.fade(0);
    _b8 = 0;
    _2a0.reset(8);
    mRemainsDucking.stop();
    _294.stop(false);
}

// NON_MATCHING: the original copies the argument as a 64-bit register (a 4-byte class type, like UiSoundKind?).
void Unk_710104e5b4::sub_710104F1B8(s32 state) {
    if (_30 != 2)
        return;
    _38 = _28->searchAndEmit("Slow");
    auto* ducking = SoundMgr::instance()->mDuckingMgr;
    ducking->sub_7101042024(DuckingMgr::DuckerType::cSlowSe);
    if (!sub_7100FFDA7C()) {
        auto* bgm = sub_7100FFE468();
        if (!bgm || bgm->_124 == 0)
            ducking->sub_7101042024(DuckingMgr::DuckerType::cSlowBgm);
    }
    if (auto* fx = SoundMgr::instance()->_50)
        fx->sub_710105126C();
    _30 = state;
    _2a0.set(1);
    sead::ScopedLock<sead::CriticalSection> lock(&mHandleCS);
    for (auto it = mHandles.robustBegin(); it != mHandles.robustEnd(); ++it) {
        if (!it->isActive())
            mHandles.erase(&*it);
        else if (_2a0.isOn(1))
            sub_710104FB40(&*it);
    }
}

xlink2::HandleSLink Unk_710104e5b4::sub_710104F30C(const sead::SafeString& label) {
    return _28->searchAndEmit(label.cstr());
}

void Unk_710104e5b4::sub_710104F354() {
    if (!_2a0.isOn(2)) {
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cSquat);
        _2a0.set(2);
    }
}

void Unk_710104e5b4::sub_710104F39C() {
    if (_2a0.isOn(2)) {
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cSquat, false);
        _2a0.reset(2);
    }
}

void Unk_710104e5b4::sub_710104F3EC() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cFocus);
}

void Unk_710104e5b4::sub_710104F404() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cFocus, false);
}

void Unk_710104e5b4::sub_710104F420() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cFocus);
}

void Unk_710104e5b4::sub_710104F438() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cFocus, false);
}

void Unk_710104e5b4::sub_710104F454() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cFocus);
}

void Unk_710104e5b4::sub_710104F46C() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cFocus, false);
}

void Unk_710104e5b4::sub_710104F488() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cFocus);
}

void Unk_710104e5b4::sub_710104F4A0() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cFocus, false);
}

void Unk_710104e5b4::sub_710104E92C(sead::Heap* heap) {
    _28 = sub_710105E3D0("ExpressionSound", heap, nullptr, nullptr, nullptr);
}

// 0x71025024f0: the FX delay gain restored when the slow motion ends.
KSYS_VISIBILITY_HIDDEN f32 sUnk_71025024F0 = 0.7f;

void Unk_710104e5b4::sub_710104EE64() {
    if (_30 == 2)
        return;
    _38.fade();
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cSlowBgm, false);
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cSlowSe, false);
    if (auto* fx = SoundMgr::instance()->_50)
        fx->sub_7101051154(sUnk_71025024F0);
    _30 = 2;
    _2a0.set(1);
    sead::ScopedLock<sead::CriticalSection> lock(&mHandleCS);
    for (auto it = mHandles.robustBegin(); it != mHandles.robustEnd(); ++it) {
        if (!it->isActive())
            mHandles.erase(&*it);
        else if (_2a0.isOn(1))
            sub_710104FB40(&*it);
    }
}

void Unk_710104e5b4::sub_710104EE50() {
    if (_30 != 2)
        sub_710104EE64();
}

extern const f32 sUnk_7102502518[2];

void Unk_710104e5b4::sub_710104FD38(const xlink2::HandleSLink& handle) {
    _278 = handle;
}

// NON_MATCHING: state branches, clamp scheduling and mapped data access differ.
void Unk_710104e5b4::sub_710104EA7C() {
    if (_250 == 3) {
        _258.calc();
        _278.setVolumeScale(_258.getValue() <= 0.0f ? 0.0f : _258.getValue());
        if (_258.getValue() == _258.getTarget())
            _250 = 0;
    } else if (_250 == 2) {
        _270 += sub_710105E3A4();
        if (sUnk_7102502518[0] <= _270) {
            _270 = sUnk_7102502518[0];
            _258.moveTo(1.0f, sUnk_7102502518[1]);
            _250 = 3;
        }
    } else if (_250 == 1) {
        _258.calc();
        _278.setVolumeScale(_258.getValue() <= 0.0f ? 0.0f : _258.getValue());
        if (_258.getValue() == _258.getTarget()) {
            _250 = 2;
            _270 = 0.0f;
        }
    }
}

KSYS_VISIBILITY_HIDDEN f32 sUnk_7102502500[2] = {1.6f, 0.05f};

void Unk_710104e5b4::sub_710104FD4C() {
    _250 = 1;
    _258.moveTo(sUnk_7102502500[0], sUnk_7102502500[1]);
}

}  // namespace ksys::snd
