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

static const sead::SafeString sRemainsElecBattle = "RemainsElecBattle";

Unk_710260f2c8::Unk_710260f2c8(const BgmInitArg& arg)
    : Unk_71025ce3a0(arg.handle_type, 2),
      mInfo(static_cast<EventBgmRemainsElecBattleInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::_17))) {
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

namespace {
sead::SafeString sStr_RemainsFireA = "A";
sead::SafeString sStr_RemainsFireB = "B";
}  // namespace

Unk_71025ce390::Unk_71025ce390(const BgmInitArg& arg)
    : Unk_71025ce3a0(arg.handle_type, 1),
      mInfo(static_cast<EventBgmRemainsFireBattleInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::_18))) {
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

Unk_710260f848::Unk_710260f848(const BgmInitArg& arg) : Unk_71025ce3a0(arg.handle_type, 3) {
    Unk_SpotBgmHandle::init(arg.heap, "RemainsWaterBattleBgm", nullptr);
}

// NON_MATCHING: the original loads the asset call table before calling getResourceAccessor (C++14 argument order).
void Unk_71025ce3a0::hm14() {
    auto* entry = sub_7101020B40();
    _189 = false;
    if (entry && entry->sub_7100FF6DF4(this) && entry->mHandle.isActive()) {
        _189 = mUserInstance->getResourceAccessor().isNeedObserve(
            *entry->mHandle.getEvent()->getAssetCallTable());
    }
}

void Unk_71025ce3a0::hm15() {
    if (mEntries.size() == 0 && mStarted) {
        sub_710101D9F4(0.0f);
        m6(false);
        mStarted = false;
    }
}

Unk_710260f848::~Unk_710260f848() = default;

Unk_710260f2b8::Unk_710260f2b8(const BgmInitArg& arg) : Unk_71025ce3a0(arg.handle_type, 0) {
    Unk_SpotBgmHandle::init(arg.heap, "RemainsWindBattleBgm", nullptr);
}

namespace {
struct RemainsWindBgmParams {
    f32 jump_fade_out_sec;
    f32 jump_fade_in_sec;
    sead::SafeString intro;
    sead::SafeString main;
};
}  // namespace

// 0x71024fe240
static const RemainsWindBgmParams sRemainsWindParams = {0.5, 0.5, "Intro", "Main"};

void Unk_710260f2b8::fadeInMaybe(f32 fade_sec) {
    sub_7101020BB0(fade_sec);
    sub_710101D9D8();
}

void Unk_710260f2b8::sub_7101009040() {
    if (mJumped)
        return;
    if (mEntry && mEntry->sub_7100FF6DF4(this))
        mEntry->sub_7100FF6A64(sRemainsWindParams.jump_fade_out_sec);
    mEntry = sub_71010209FC(sRemainsWindParams.main);
    mFader.setValueImmediate(0.0f);
    mFader.moveTo(1.0f, sRemainsWindParams.jump_fade_in_sec);
    mJumped = true;
}

void Unk_710260f2b8::hm14() {
    mEntry = sub_71010209FC(mJumped ? sRemainsWindParams.main : sRemainsWindParams.intro);
}

void Unk_710260f2b8::hm15() {
    if (!mEntry)
        return;
    if (!mEntry->sub_7100FF6DF4(this))
        hm14();
    if (mEntry && mJumped) {
        mFader.calc();
        mEntry->_20 = sead::Mathf::clampMin(mFader.getValue(), 0.0f);
    }
}

Unk_710260f2b8::~Unk_710260f2b8() = default;

void Unk_710260f2b8::fadeOutMaybe(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
}

Unk_710260ecf8::~Unk_710260ecf8() = default;

// NON_MATCHING: the original loads the asset call table before calling getResourceAccessor (C++14 argument order).
void Unk_710260ecf8::hm14() {
    auto* entry = sub_7101020B40();
    _189 = false;
    if (entry && entry->sub_7100FF6DF4(this) && entry->mHandle.isActive()) {
        _189 = mUserInstance->getResourceAccessor().isNeedObserve(
            *entry->mHandle.getEvent()->getAssetCallTable());
    }
}

void Unk_710260ecf8::hm15() {
    if (mEntries.size() == 0 && mStarted) {
        sub_710101D9F4(0.0f);
        m6(false);
        mStarted = false;
    }
}

}  // namespace ksys::snd

// NON_MATCHING: placeholder destructor; the original (0x710100ac6c) also destroys members or bases
// this class does not declare yet.
Unk_71024fe368::~Unk_71024fe368() = default;

void Unk_71024fe368::calc() {
    Unk_SpotBgmHandle::calc();
    mSubHandle->_a4 = _138.getValue() * _1b0.getValue();
    mSubHandle->calc();
}

void Unk_71024fe368::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    mSubHandle->sub_7101020C08(fade_sec);
    _248->_18 = 0;
    _1e8 = 0;
    mState = 0;
    mSubHandle->sub_7101020C08(fade_sec);
}

void Unk_71024fe368::sub_710100B30C(const ksys::snd::Unk_BgmControllerM8Arg& arg) {
    _1d8 = arg;
}

bool Unk_71024fe368::m10() {
    if (_124 == 3 || _124 == 4)
        return _160[1] > *mInfo->mFeelPlayingSec;
    return false;
}

void Unk_71024fe368::hm16(s32 arg) {
    if (arg == 2)
        _248->_18 = 0;
    mSubHandle->sub_7101020C08(0.0f);
}

Unk_71024fe808::~Unk_71024fe808() = default;

// NON_MATCHING: placeholder destructor; the original (0x710100df48) also destroys members or bases
// this class does not declare yet.
Unk_71024fe970::~Unk_71024fe970() = default;

namespace {
sead::SafeString sStr_GuardianFixedBgm = "GuardianFixedBgm";
sead::SafeString sStr_GuardianFixedBgmMain = "main";
}  // namespace

// NON_MATCHING: the original zeroes 0x1d8 alone and 0x1dc / 0x1e4 as two unaligned doublewords (tried u32[2] and a
// two-word struct; clang merges 0x1d8..0x1e8 differently).
Unk_71024feae8::Unk_71024feae8(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    auto* heap = arg.heap;
    Unk_SpotBgmHandle::init(heap, sStr_GuardianFixedBgm, nullptr);
    mInfo = ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::_14);
    mEntries.tryAllocBuffer(64, heap);
}

Unk_71024feae8::~Unk_71024feae8() {
    mEntries.freeBuffer();
}

void Unk_71024feae8::hm14() {
    mMainEntry = sub_71010209FC(sStr_GuardianFixedBgmMain);
    if (mMainEntry)
        mMainEntry->sub_7100FF6DF4(this);
}

void Unk_71024feae8::hm15() {
    if (mState != 1 && mState != 2)
        return;
    if (!mMainEntry || mMainEntry->sub_7100FF6DF4(this))
        return;
    sub_710101D9F4(0.0);
}

Unk_71024fec18::Unk_71024fec18(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, "GanonBeastBgm", nullptr);
    mInfo = ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::_24);
}

Unk_71024fec18::~Unk_71024fec18() = default;

Unk_71024fed48::~Unk_71024fed48() = default;

Unk_71024fee78::~Unk_71024fee78() = default;

// NON_MATCHING: the two secondary-vtable thunks (0x7101011d98 / 0x7101011e3c) differ in register allocation.
Unk_71024fefe8::~Unk_71024fefe8() {
    mEntries.freeBuffer();
}

namespace ksys::snd {

Unk_710260f278::Unk_710260f278(const BgmInitArg& arg) : Unk_71025ce380(arg) {
    _1c0.setCurveType(aal::FadeCurveType::Square);
    auto* heap = arg.heap;
    mInfo = static_cast<HorseBgmInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::_1));
    Unk_SpotBgmHandle::init(heap, "HorseBgm", nullptr);
}

Unk_710260f278::~Unk_710260f278() = default;

void Unk_710260f278::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    _198 = 0;
    _1a8 = 0;
    _1b0 = 0;
}

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
