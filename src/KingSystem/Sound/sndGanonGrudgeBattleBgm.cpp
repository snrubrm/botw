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

bool Unk_71024fee78::m10() {
    if (_124 != 3 && _124 != 4)
        return false;
    return _160[1] >= mInfo->mFeelPlayingSec.ref();
}

bool Unk_71024fee78::m11() {
    return mState == 2;
}

void Unk_71024fee78::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    mState = 0;
}

