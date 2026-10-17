#include "KingSystem/Sound/sndSound.h"
#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
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
    updateHandles();
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

// inline-only in the original; name is a guess (the same locked loop is inlined in 0x710104e964, 0x710104ee64
// and 0x710104f1b8): drops the handles whose event is gone and refreshes the others while bit 0 of _2a0 is set.
inline void Unk_710104e5b4::updateHandles() {
    sead::ScopedLock<sead::CriticalSection> lock(&mHandleCS);
    for (auto it = mHandles.robustBegin(); it != mHandles.robustEnd(); ++it) {
        if (!it->isActive())
            mHandles.erase(&*it);
        else if (_2a0.isOn(1))
            sub_710104FB40(&*it);
    }
}

void Unk_710104e5b4::sub_710104E964() {
    auto* user = _28;
    user->preCalc();
    user->postCalc();
    sub_710104EA7C();
    updateHandles();
    if (_2a0.isOn(1)) {
        sub_710104EBBC();
        _2a0.reset(1);
    }
    if (_b8 != 0)
        --_b8;
    mRemainsDucking.calc();
    _294.calc();
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
    updateHandles();
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

// [2..5]: the volume, pitch, biquad filter and bus volume of the slowed groups (0x710104ebbc).
KSYS_VISIBILITY_HIDDEN f32 sUnk_7102502500[6] = {1.6f, 0.05f, 0.8f, 0.7f, 0.3f, 0.65f};

// NON_MATCHING: the original walks the buffer with an end pointer (sign-extended size) and schedules the last
// filter argument differently.
void Unk_710104e5b4::sub_710104EBBC() {
    for (auto& group : _48) {
        if (_30 == 2) {
            group->getParam().setVolume(1.0f);
            group->getParam().setPitch(1.0f);
            group->getParam().setBiquadFilter(-1, 0.0f);
            group->getParam().setBusVolume(aal::BusType::AuxB, 0.0f);
        } else {
            group->getParam().setVolume(sUnk_7102502500[2]);
            group->getParam().setPitch(sUnk_7102502500[3]);
            group->getParam().setBiquadFilter(2, sUnk_7102502500[4]);
            group->getParam().setBusVolume(aal::BusType::AuxB, sUnk_7102502500[5]);
        }
    }
    if (!_98)
        return;
    if (_30 == 2) {
        _98->getParam().setVolume(1.0f);
        _98->getParam().setBiquadFilter(-1, 0.0f);
        _98->getParam().setBusVolume(aal::BusType::AuxB, 0.0f);
    } else {
        _98->getParam().setVolume(sUnk_7102502500[2]);
        _98->getParam().setBiquadFilter(2, sUnk_7102502500[4]);
        _98->getParam().setBusVolume(aal::BusType::AuxB, sUnk_7102502500[5]);
    }
}

void Unk_710104e5b4::sub_710104ED9C() {
    SoundMgr::instance()->_50->sub_7101050CCC();
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cPauseEvent, false);
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cPauseIngame, false);
    if (aal::GroupMgr* group_mgr = aal::SystemAccessor::getGroupMgr()) {
        aal::Group* root = group_mgr->getRootGroup();
        root->allowEmit(sead::BitFlag8(1), true);
        root->pauseAllSound(sead::BitFlag8(1), false, 0.3f);
    }
    SoundMgr::instance()->_98->_5e0._20.moveTo(1.0f, 0.3f);
}

void Unk_710104e5b4::sub_710104FD68(aal::Group* group, sead::PtrArray<aal::Group>* groups, s32 type) {
    if (group->get_13c() & (1 << type)) {
        groups->pushBack(group);
        return;
    }
    for (auto* node = group->treeNode().child(); node; node = node->next())
        sub_710104FD68(node->value(), groups, type);
}

void Unk_710104e5b4::sub_710104FD4C() {
    _250 = 1;
    _258.moveTo(sUnk_7102502500[0], sUnk_7102502500[1]);
}

}  // namespace ksys::snd
