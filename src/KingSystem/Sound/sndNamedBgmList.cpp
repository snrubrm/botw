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

namespace ksys::snd {

// This TU ends with the static initialiser 0x71010089f4. Its statics at 0x710260f810 start with InitConstants and
// InitTimeInfo (before "A" / "B"); declaring them here makes the whole static initialiser dynamic, which moves
// sRemainsElecBattle out of .data.rel.ro, so they are left out.
static const sead::SafeString sRemainsElecBattle = "RemainsElecBattle";

namespace {
sead::SafeString sStr_RemainsFireA = "A";
sead::SafeString sStr_RemainsFireB = "B";
}  // namespace

Unk_71010073f4::Unk_71010073f4() {
    mList.initOffset(0x190);
}

Unk_71010073f4::~Unk_71010073f4() = default;

void Unk_71010073f4::update() {
    auto lock = sead::makeScopedLock(mCS);
    for (auto it = mList.robustBegin(); it != mList.robustEnd(); ++it) {
        it->update();
        if (!it->mStarted && it->mEntries.size() == 0 && it->mRefCount <= 0) {
            mList.erase(&*it);
            sub_7100FFF0E4(&*it);
        }
    }
}

NamedBgm* Unk_71010073f4::find(const sead::SafeString& name) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& bgm : mList) {
        if (*bgm.getName() == name)
            return &bgm;
    }
    return nullptr;
}

bool Unk_71010073f4::hold(const sead::SafeString& name, sead::Heap* heap) {
    auto lock = sead::makeScopedLock(mCS);
    if (auto* bgm = find(name)) {
        ++bgm->mRefCount;
        return true;
    }
    auto* bgm = bgmStuff(name, heap);
    if (!bgm)
        return false;
    bgm->m8();
    bgm->mRefCount = 1;
    mList.pushBack(bgm);
    return true;
}

bool Unk_71010073f4::isFinished(const sead::SafeString& name) {
    auto lock = sead::makeScopedLock(mCS);
    if (auto* bgm = find(name))
        return bgm->sub_7101020CEC();
    return true;
}

void Unk_71010073f4::release(const sead::SafeString& name) {
    if (auto* bgm = find(name))
        --bgm->mRefCount;
}

// NON_MATCHING: the original has a discarded 32-bit load of the handle type (+0xd8) after the null check.
void Unk_71010073f4::sub_71010078A0(const sead::SafeString& name) {
    auto* bgm = find(name);
    if (!bgm || bgm->mStarted)
        return;
    bgm->sub_7101020BB0(0.0);
    bgm->sub_710101D9D8();
    bgm->m6(true);
    bgm->mStarted = true;
}

void Unk_71010073f4::sub_7101007904(f32 fade_sec, const sead::SafeString& name) {
    auto* bgm = find(name);
    if (!bgm || !bgm->mStarted)
        return;
    bgm->sub_710101D9F4(fade_sec);
    bgm->m6(false);
    bgm->mStarted = false;
}

// Stops all started BGMs.
void Unk_71010073f4::sub_7101007960(f32 fade_sec) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& bgm : mList) {
        if (!bgm.mStarted)
            continue;
        bgm.sub_710101D9F4(fade_sec);
        bgm.m6(false);
        bgm.mStarted = false;
    }
}

void Unk_71010073f4::sub_7101007A08(f32 fade_sec) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& bgm : mList) {
        if (bgm.mStarted && bgm._189)
            bgm.sub_710101D9F4(fade_sec);
    }
}

void Unk_71010073f4::sub_7101007AA0(f32 fade_sec) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& bgm : mList) {
        if (bgm.mStarted && bgm._189) {
            bgm.sub_7101020BB0(fade_sec);
            bgm.sub_710101D9D8();
        }
    }
}

// Stops and deletes all BGMs.
void Unk_71010073f4::sub_7101007B44() {
    auto lock = sead::makeScopedLock(mCS);
    for (auto it = mList.robustBegin(); it != mList.robustEnd(); ++it) {
        if (it->mStarted) {
            it->sub_710101D9F4(0.0);
            it->m6(false);
            it->mStarted = false;
        }
        mList.erase(&*it);
        sub_7100FFF0E4(&*it);
    }
}

bool Unk_71010073f4::sub_7101007C14() {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& bgm : mList) {
        if (bgm.mStarted)
            return true;
    }
    return false;
}

bool Unk_71010073f4::sub_7101007C90() {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& bgm : mList) {
        if (bgm._189 && bgm.mStarted)
            return true;
    }
    return false;
}

// The Remains battle BGMs. In the original, Elec and Fire (up to the static initialiser 0x71010089f4) and Water, Wind
// and Unk_710260ecf8 are two TUs.

// NON_MATCHING: the original adds +0x28c in each branch; ours hoists it.
void Unk_71025ce3a0::m6(bool started) {
    if (started)
        Unk_710104e5b4::instance()->mRemainsDucking.start(mDuckingKind);
    else
        Unk_710104e5b4::instance()->mRemainsDucking.stop();
}

Unk_710260f2c8::Unk_710260f2c8(const BgmInitArg& arg)
    : Unk_71025ce3a0(arg.handle_type, 2),
      mInfo(static_cast<EventBgmRemainsElecBattleInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::EventBgmRemainsElecBattle))) {
    Unk_SpotBgmHandle::init(arg.heap, "RemainsElecBattleBgm", nullptr);
}

Unk_710260f2c8::~Unk_710260f2c8() = default;

void Unk_710260f2c8::hm14() {
    mEntry = sub_71010209FC(sRemainsElecBattle);
    if (!mEntry || !mEntry->sub_7100FF6DF4(this))
        return;

    const f32 storm_volume = _1e8 && !_1e9 ? *mInfo->mMinVolumeOutStorm : 1.0f;
    mStormFader.setValueImmediate(storm_volume);
    mEntry->sub_7100FF6A50(1, storm_volume);

    const f32 wake_volume = _1ea ? 1.0f : *mInfo->mMinVolumeWakeBoarding;
    mWakeBoardingFader.setValueImmediate(wake_volume);
    mEntry->sub_7100FF6A50(2, wake_volume);
}

// NON_MATCHING: the original tests `_1e9 != 0` as a value against the target test and branches the other way.
void Unk_710260f2c8::hm15() {
    const bool storm_at_full = mStormFader.getTarget() == 1.0f;
    if (_1e8) {
        if (storm_at_full != _1e9) {
            if (!_1e9)
                mStormFader.moveTo(*mInfo->mMinVolumeOutStorm, *mInfo->mFadeOutSecOutStorm);
            else
                mStormFader.moveTo(1.0f, *mInfo->mFadeInSecOutStorm);
        }
    } else if (!storm_at_full) {
        mStormFader.moveTo(1.0f, *mInfo->mFadeInSecOutStorm);
    }

    if ((mWakeBoardingFader.getTarget() == 1.0f) != _1ea) {
        if (_1ea)
            mWakeBoardingFader.moveTo(1.0f, *mInfo->mFadeInSecWakeBoarding);
        else
            mWakeBoardingFader.moveTo(*mInfo->mMinVolumeWakeBoarding, *mInfo->mFadeOutSecWakeBoarding);
    }

    mStormFader.calc();
    mWakeBoardingFader.calc();

    if (mEntry && mEntry->sub_7100FF6DF4(this)) {
        mEntry->sub_7100FF6A50(1, mStormFader.getValue());
        mEntry->sub_7100FF6A50(2, mWakeBoardingFader.getValue());
    }
}

Unk_71025ce390::Unk_71025ce390(const BgmInitArg& arg)
    : Unk_71025ce3a0(arg.handle_type, 1),
      mInfo(static_cast<EventBgmRemainsFireBattleInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::EventBgmRemainsFireBattle))) {
    Unk_SpotBgmHandle::init(arg.heap, "RemainsFireBattleBgm", nullptr);
}

// NON_MATCHING: the original selects the parameter value addresses; and sStr_RemainsFireB sits at +0x28 of the TU's
// static block (+0x20 here).
void Unk_71025ce390::sub_71010084B4(bool alert) {
    sub_7101020C08(*mInfo->mFoundFadeOutSec);
    mWaitTimer = alert ? *mInfo->mFoundWaitSec : *mInfo->mFoundAgainWaitSec;
    if (mWaitTimer == 0.0f)
        sub_71010209FC(sStr_RemainsFireB);
}

// NON_MATCHING: `!(flags & 2)` is computed as ubfx / eor in the original; static block offset of sStr_RemainsFireA.
void Unk_71025ce390::hm14() {
    if (mType == Unk_710260f248Type::_3 || (_68._18 & 1)) {
        _1b4 = false;
    } else {
        _1b4 = !(_68._18 & 2);
        if (!(_68._18 & 2))
            return;
    }
    sub_71010209FC(sStr_RemainsFireA);
    mWaitTimer = 0.0f;
}

// NON_MATCHING: static block offsets of sStr_RemainsFireA / sStr_RemainsFireB (+0x18 / +0x28 in the original).
void Unk_71025ce390::hm15() {
    if (_1b4) {
        if (mType == Unk_710260f248Type::_3 || (_68._18 & 3)) {
            sub_71010209FC(sStr_RemainsFireA);
            mWaitTimer = 0.0f;
            _1b4 = false;
        }
    } else if (mWaitTimer > 0.0f) {
        mWaitTimer -= sub_710105E3A4();
        if (mWaitTimer <= 0.0f) {
            mWaitTimer = 0.0f;
            sub_71010209FC(sStr_RemainsFireB);
        }
    }
}

Unk_71025ce390::~Unk_71025ce390() = default;

}  // namespace ksys::snd
