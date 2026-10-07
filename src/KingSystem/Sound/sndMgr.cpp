#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Event/evtManager.h"

namespace ksys::snd {

void SoundMgr::sub_71011FC29C() {
    mDuckingMgr->sub_7101042024(0x23);
    _238 |= 2;
}

void SoundMgr::sub_71011FC288() {
    if (!_f8.getDirect())
        _30->sub_7100FF8804();
}

// NON_MATCHING: the original spills both arguments to the stack and reads them back (they are not plain ints; the types are
// unknown).
void SoundMgr::sub_71011FC0C0(UiSoundKind kind, s32 bit) {
    _f8.setBit(bit);
    if (!_f8.isZero()) {
        switch (kind.value) {
        case 0:
            mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cScreenFadeL);
            break;
        case 1:
            mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cScreenFadeM);
            break;
        case 2:
            mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cScreenFadeS);
            break;
        case 3:
            mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cScreenFadeLogo);
            break;
        case 5:
            mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cScreenFadeForce);
            break;
        }
        _98->sub_710103D0D8(kind);
    }
}

// NON_MATCHING: the original spills `bit` to the stack and reads it back (the type is unknown).
void SoundMgr::sub_71011FC17C(UiSoundKind kind, s32 bit) {
    _f8.resetBit(bit);
    if (_f8.isZero()) {
        bool active = mDuckingMgr->mDuckers[DuckingMgr::DuckerType(DuckingMgr::DuckerType::cScreenFadeLogo)].isActive();
        mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cScreenFadeS, active);
        mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cScreenFadeM, active);
        mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cScreenFadeL, active);
        mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cScreenFadeForce, active);
        mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cScreenFadeLogo, false);
        mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cPlayTimeOver, false);
        _98->sub_710103D324(kind);
    }
}

void Unk_SoundMgr48::sub_7101055B44() {
    if (_18.isEnabled())
        _18.stop(0.1f, 0.0f);
}

void Unk_710104e5b4::sub_710104F86C() {
    if (evt::Manager::instance()->hasActiveEvent() && !_2a0.isOn(4))
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(0x10);
}

void Unk_710104e5b4::sub_710104F8C4(bool suspend) {
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(0x10, suspend);
}

void Unk_710104e5b4::sub_710104F8E0() {
    if (!_2a0.isOn(4))
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(0xf);
}

void Unk_710104e5b4::sub_710104F904() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(0xf, false);
}

void Unk_710104e5b4::sub_710104F920(bool on) {
    if (on) {
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(0x10, false);
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(0xf, false);
        _2a0.set(4);
    } else {
        _2a0.reset(4);
    }
}

Unk_SoundMgr30_10* sub_7100FFD754() {
    return SoundMgr::instance()->_30->_10;
}

Unk_SoundMgr30_78* sub_7100FFD784() {
    return SoundMgr::instance()->_30->_78;
}

void Unk_710103b704::sub_710103D094() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(0x30, false);
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(0x31, false);
}

void Unk_710103b704::sub_710103D418() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042024(0x1f);
}

f32 Unk_SoundMgr48::sub_7101055E3C() const {
    return 0.2f;
}

bool Unk_SoundMgra8::sub_710104B5DC(u32 idx) const {
    return _4a70 > idx;
}

bool Unk_SoundMgra8::sub_710104B68C(void* a, int b) {
    for (auto it = _50.begin(); it != _50.end(); ++it) {
        if (it->sub_710104B1D8(a))
            return it->sub_710104ADB8(b);
    }
    return false;
}

bool Unk_SoundMgra8::sub_710104B708(int a) {
    for (auto it = _50.begin(); it != _50.end(); ++it) {
        if (it->sub_710104AFBC(a))
            return true;
    }
    return false;
}

bool Unk_SoundMgra8::sub_710104B76C(void* a) {
    for (auto it = _50.begin(); it != _50.end(); ++it) {
        if (it->sub_710104AFC0(a))
            return true;
    }
    return false;
}

int Unk_SoundMgra8::sub_710104B7D0() {
    auto lock = sead::makeScopedLock(mCS);
    return ++_4a70;
}

void Unk_SoundMgra8::sub_710104B554(Unk_SoundInstance* instance) {}

f32 Unk_SoundMgra8::sub_710104B558(ksys::act::Actor* actor) {
    f32 volume = -1.0f;
    if (_48 && _49) {
        for (auto it = _50.begin(); it != _50.end(); ++it) {
            const f32 value = it->sub_710104AC00(actor);
            if (value >= 0.0f) {
                volume = value;
                break;
            }
        }
    }
    return volume;
}

void ListenerPoser::sub_7101055538(s32 value) {
    if (!_70) {
        _70 = true;
        _74 = value;
    }
}

}  // namespace ksys::snd

bool emitActorGetDemoSound(const sead::SafeString& name) {
    return ksys::snd::SoundMgr::instance()->mUiSoundMgr->emitGetItemSound(name);
}
