#include <gfx/seadTextWriter.h>
#include <math/seadVector.h>
#include "KingSystem/Sound/sndBgmMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/InitTimeInfo.h"

// The Ganon grudge battle BGM (Unk_71024fee78): TU 0x7101011274..0x7101011b90 (static initialiser
// 0x7101011b2c) in the original.

namespace {
// The TU statics at 0x710260fd20 (_GLOBAL__sub_I_sndGanonGrudgeBattleBgm.cpp is NON_MATCHING: GlobalMerge places the
// vector first).
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
// 0x710260fd38 (placeholder name; unused by the functions decompiled so far).
sead::Vector2f sUnk_710260FD38{920.0f, 80.0f};
sead::SafeString sStr_GanonGrudgeBattleBgm = "GanonGrudgeBattleBgm";
sead::SafeString sStr_GanonGrudgeBattleBgmMain = "main";
}  // namespace

Unk_71024fee78::Unk_71024fee78(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, sStr_GanonGrudgeBattleBgm, nullptr);
    mInfo = static_cast<ksys::snd::GanonGrudgeBattleBgmInfo*>(
        ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::GanonGrudgeBattleBgm));
    if (auto* queries = ksys::snd::SoundMgr::instance()->_c8) {
        if (queries->m5())
            _1d4 |= 2;
        else
            _1d4 &= ~2;
    }
}

Unk_71024fee78::~Unk_71024fee78() = default;

void Unk_71024fee78::hm14() {
    mEntry = sub_71010209FC(sStr_GanonGrudgeBattleBgmMain);
    if (mEntry && mEntry->sub_7100FF6DF4(this))
        _1a0.moveTo(1.0f, mInfo->mFadeInSec.ref());
}

void Unk_71024fee78::m5() {
    if (!mActive || !(_68._18 & 1))
        return;
    const bool in_battle = (_1d4 & 3) != 1 && _1d0 > 0;
    switch (mState) {
    case 0:
        if (in_battle) {
            _1a0.setValueImmediate(0.0f);
            sub_710101D9D8();
            mState = 1;
        }
        break;
    case 1:
        if (!in_battle) {
            _1a0.moveTo(0.0f, mInfo->mFadeOutSec.ref());
            mState = 2;
        }
        break;
    case 2:
        if (in_battle) {
            _1a0.moveTo(1.0f, 0.5f);
            mState = 1;
        }
        if (_1a0.getValue() == _1a0.getNextValue()) {
            sub_710101D9F4(0.1f);
            mState = 0;
        }
        break;
    }
    _1a0.calc();
    _a4 = _1a0.getValue();
}

bool Unk_71024fee78::m10() {
    if (_124 != 3 && _124 != 4)
        return false;
    return _160[1] >= mInfo->mFeelPlayingSec.ref();
}

bool Unk_71024fee78::m11() {
    return mState == 2;
}

void Unk_71024fee78::sub_710101157C(const ksys::snd::Unk_BgmControllerM8Arg& arg) {
    _1d0 = arg._0;
}

// 0x710260fca8: debug flag (never written).
KSYS_VISIBILITY_HIDDEN bool sUnk_710260FCA8;

// NON_MATCHING: sUnk_710260FD38 has a different offset in the merged TU statics (see the static initialiser).
void Unk_71024fee78::m14(sead::TextWriter& writer) {
    if (!sUnk_710260FCA8)
        return;
    writer.setCursorFromTopLeft(sUnk_710260FD38);
    writer.printf("---- 神獣内通常戦闘BGM ----\n");
    writer.printf("処理            :%s\n", mActive ? "有効" : "無効");
    writer.printf("戦闘中?         :%s\n", (_1d4 & 3) != 1 && _1d0 > 0 ? "Yes" : "No");
    writer.printf("状態            :%s\n", State::text(mState) ? State::text(mState) : "不明");
    writer.printf("フェード音量    :%.2f\n", _1a0.getValue());
}

void Unk_71024fee78::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    mState = 0;
}

