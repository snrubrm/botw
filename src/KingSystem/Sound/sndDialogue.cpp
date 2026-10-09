#include "KingSystem/Sound/sndMgr.h"
#include <xlink2/xlink2UserInstanceSLink.h>

namespace ksys::snd {

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

extern const f32 sUnk_7102502500[2];

// NON_MATCHING: the original local data pair is accessed through the mapped external symbol.
void Unk_710104e5b4::sub_710104FD4C() {
    _250 = 1;
    _258.moveTo(sUnk_7102502500[0], sUnk_7102502500[1]);
}

}  // namespace ksys::snd
