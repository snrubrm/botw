#include <aal/aalTimedFader.h>
#include <math/seadVector.h>
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include "KingSystem/Sound/sndOcclusionMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/InitTimeInfo.h"

// The TU statics at 0x710260da0 (_GLOBAL__sub_I_sndBgmCastle.cpp is NON_MATCHING: GlobalMerge orders them differently).
namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
// 0x710260ddb8 (placeholder name; unused by the functions decompiled so far).
sead::Vector2f sUnk_710260DDB8{360.0f, 320.0f};
sead::SafeString sStr_CastleBgm = "CastleBgm";
sead::SafeString sStr_CastleBgmMain = "Castle";
sead::SafeString sStr_CastleBgmSpot = "SpSpotBgm";
}  // namespace

// 0x710260fd90 / 0x710260fd94 / 0x710260fd98 (placeholder names): bytes the original reads PC-relative and
// nothing writes (debug switches: force playing / the inside mix / the battle part). Non-static here so that
// they are not folded away.
bool sUnk_710260FD90 = false;
bool sUnk_710260FD94 = false;
bool sUnk_710260FD98 = false;

Unk_71024ff268::Unk_71024ff268(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, sStr_CastleBgm, nullptr);
    mInfo = static_cast<ksys::snd::CastleBgmInfo*>(
        ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::_5));
}

Unk_71024ff268::~Unk_71024ff268() = default;

// NON_MATCHING: the debug switches are loaded through the GOT (the original's are TU-local).
void Unk_71024ff268::m5() {
    if (!mActive)
        return;
    if (!(_68._18 & 1))
        return;

    if (sUnk_710260FD90 || _1a8 || _198 != 0) {
        const bool inside =
            sUnk_710260FD94 || ksys::snd::SoundMgr::instance()->mOcclusionMgr->isInsideMaybe();
        switch (_19c) {
        case 0:
            if (inside) {
                _1b0 = 0;
                _19c = 1;
            }
            break;
        case 1:
            if (inside) {
                _1b0 += ksys::snd::sub_710105E3A4();
                if (_1b0 >= mInfo->mToIndoorWaitSec.ref()) {
                    _1b0 = mInfo->mToIndoorWaitSec.ref();
                    _1d0.moveTo(1.0, mInfo->mToIndoorFadeSec.ref());
                    _19c = 2;
                }
            } else {
                _1b0 = 0;
                _19c = 0;
            }
            break;
        case 2:
            if (inside) {
                if (_1d0.getValue() == _1d0.getTarget())
                    _19c = 3;
            } else {
                _1d0.moveTo(0.0, mInfo->mToOutdoorFadeSec.ref());
                _19c = 4;
            }
            break;
        case 3:
            if (!inside) {
                _1d0.moveTo(0.0, mInfo->mToOutdoorFadeSec.ref());
                _19c = 4;
            }
            break;
        case 4:
            if (inside) {
                _1b0 = 0;
                _19c = 1;
            } else if (_1d0.getValue() == _1d0.getTarget()) {
                _19c = 0;
            }
            break;
        }
        _1d0.calc();

        const bool no_battle = _1e8 < 1 && !sUnk_710260FD98;
        switch (_1ec) {
        case 0:
            if (no_battle) {
                _208 = 0;
            } else {
                _208 += ksys::snd::sub_710105E3A4();
                if (_208 >= mInfo->mBattleWaitSec.ref()) {
                    _208 = mInfo->mBattleWaitSec.ref();
                    _1f0.moveTo(1.0, mInfo->mBattleFadeInSec.ref());
                    _1ec = 1;
                }
            }
            break;
        case 1:
            if (no_battle) {
                _1f0.moveTo(0.0, mInfo->mBattleFadeOutSec.ref());
                _1ec = 3;
            } else {
                _1f0.calc();
                if (_1f0.getValue() == _1f0.getTarget())
                    _1ec = 2;
            }
            break;
        case 2:
            if (no_battle) {
                _1f0.moveTo(0.0, mInfo->mBattleFadeOutSec.ref());
                _1ec = 3;
            }
            break;
        case 3:
            if (no_battle) {
                _1f0.calc();
                if (_1f0.getValue() == _1f0.getTarget()) {
                    _208 = 0;
                    _1ec = 0;
                }
            } else {
                _1f0.moveTo(1.0, mInfo->mBattleFadeInSec.ref());
                _1ec = 1;
            }
            break;
        }
    }

    switch (_198) {
    case 0:
        if (!sUnk_710260FD90 && !_1a8)
            return;
        sub_710101D9D8();
        _1b8.setValueImmediate(1.0);
        _198 = 1;
        break;
    case 1:
        _1b8.calc();
        if (sUnk_710260FD90 || _1a8)
            return;
        _1ac = 0;
        _198 = 2;
        break;
    case 2:
        if (!sUnk_710260FD90 && !_1a8) {
            _1ac += ksys::snd::sub_710105E3A4();
            if (_1ac < mInfo->mFadeOutWaitSec.ref())
                return;
            _1ac = mInfo->mFadeOutWaitSec.ref();
            _1b8.moveTo(0.0, mInfo->mFadeOutSec.ref());
            _198 = 3;
            break;
        }
        _1ac = 0;
        _198 = 1;
        break;
    case 3:
        if (!sUnk_710260FD90 && !_1a8) {
            _1b8.calc();
            if (_1b8.getValue() != _1b8.getTarget())
                return;
            sub_710101D9F4(0.0);
            _198 = 0;
            return;
        }
        _1ac = 0;
        _1b8.moveTo(1.0, 1.0);
        _198 = 1;
        break;
    }
}

bool Unk_71024ff268::m10() {
    return (_124 == 3 || _124 == 4) && _1ec != 0;
}

void Unk_71024ff268::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    _198 = 0;
}

void Unk_71024ff268::hm15() {
    _a4 = _1b8.getValue();
    updateEntryVolumes();
}

// NON_MATCHING: sUnk_710260FD94 / sUnk_710260FD98 are loaded through the GOT (the original's are TU-local).
void Unk_71024ff268::hm14() {
    if (sUnk_710260FD94 || ksys::snd::SoundMgr::instance()->mOcclusionMgr->isInsideMaybe()) {
        _1d0.setValueImmediate(1.0f);
        _19c = 3;
    } else {
        _1d0.setValueImmediate(0.0f);
        _19c = 0;
    }
    if (_1e8 > 0 || sUnk_710260FD98) {
        _1f0.setValueImmediate(1.0f);
        _1ec = 2;
    } else {
        _1f0.setValueImmediate(0.0f);
        _1ec = 0;
    }
    mEntry = sub_71010209FC(sStr_CastleBgmMain);
    updateEntryVolumes();
}
