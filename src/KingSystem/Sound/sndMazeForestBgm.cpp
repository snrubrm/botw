#include "KingSystem/Sound/sndBgmMgr.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2ResourceAccessorSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

// TU 0x7101013c50..0x7101014300 in the original (after sndBgmCastle.cpp; no static initialiser).

namespace ksys::snd {

namespace {
sead::SafeString sStr_MazeForestBgm = "MazeForestBgm";
sead::SafeString sStr_MazeForestBgmMain = "main";
sead::SafeString sStr_MazeForestBgmGetLost = "GetLost";
}  // namespace

Unk_710260f288::Unk_710260f288(const BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, sStr_MazeForestBgm, nullptr);
    mInfo = static_cast<MazeForestBgmInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::_4));
}

// 0x710260fdf0: the original reads it PC-relative (a TU-local static that something else in the TU writes; no
// writer found). Placeholder name; non-static here so that it is not folded away.
bool sUnk_710260FDF0 = false;

// NON_MATCHING: sUnk_710260FDF0 is loaded through the GOT (the original's is TU-local); the three flags are
// combined with branches instead of orr, and the two moveTo + sub_710101D9D8 tails are not merged.
void Unk_710260f288::m5() {
    if (!mActive)
        return;

    f32 lost_woods = 0.0;
    f32 lost_woods_7 = 0.0;
    if (auto* env = world::Manager::instance()->getEnvMgr()) {
        if (env->getPaletteSet() == 1)
            lost_woods = env->getPaletteSetTransition();
        else if (env->getPaletteSet() == 7)
            lost_woods_7 = env->getPaletteSetTransition();
    }

    const f32 prev = _1cc;
    _1cc = lost_woods;
    _1c8 = lost_woods == prev ? lost_woods > 0.0f : lost_woods > prev;
    const f32 prev_7 = _1d4;
    _1d4 = lost_woods_7;
    _1d0 = lost_woods_7 == prev_7 ? lost_woods_7 > 0.0f : lost_woods_7 > prev_7;
    const bool in_forest = _1c8 || _1d0 || sUnk_710260FDF0;

    switch (mState) {
    case 0:
        if (!in_forest) {
            mTimer = 0;
            break;
        }
        mTimer += sub_710105E3A4();
        if (mTimer >= mInfo->mPlayWaitSec.ref() && (_68._18 & 1)) {
            mTimer = mInfo->mPlayWaitSec.ref();
            mFader.moveTo(mInfo->mVolumeNormal.ref(), mInfo->mFadeInSec.ref());
            sub_710101D9D8();
            mState = 1;
        }
        break;
    case 1:
        if (!in_forest) {
            mFader.moveTo(0.0, mInfo->mFadeOutSec.ref());
            sub_710101DA34();
            mState = 3;
        }
        mFader.calc();
        break;
    case 2:
        mFader.calc();
        break;
    case 3:
        if (in_forest) {
            mFader.moveTo(mInfo->mVolumeNormal.ref(), mInfo->mFadeInSec.ref());
            sub_710101D9D8();
            mState = 1;
        } else {
            mFader.calc();
            if (mFader.getValue() == mFader.getNextValue()) {
                sub_7101020C08(0.0);
                mState = 0;
                mTimer = 0;
            }
        }
        break;
    }
    _a4 = mFader.getValue();
}

void Unk_710260f288::m13(f32 fade_sec) {
    sub_710101DA34();
    sub_7101020C08(fade_sec);
    mFader.setValueImmediate(0.0);
    mState = 0;
}

void Unk_710260f288::playGetLostMaybe() {
    if (_124 != 3 && _124 != 4)
        return;
    sub_71010209FC(sStr_MazeForestBgmGetLost);
}

void Unk_710260f288::hm14() {
    if (mEntries.size() != 0)
        return;
    sub_71010209FC(sStr_MazeForestBgmMain);
}

}  // namespace ksys::snd

