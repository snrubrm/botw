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

void Unk_71024fe368::hm14() {
    _1f8 = 0;
    _1f0 = 0;
    _1f4 = 0;
    _218 = 0;
    _21c = 0;
    _220 = 0;
    _224 = false;
    _228 = -1;
    _230 = nullptr;
    for (s32 i = 0; i < mEntries4.size(); ++i)
        mEntries4(i)._98 = -1;
    mHalfBeatSec = 60.0f / *mInfo->mBpm * 0.5f;
    _248->start();
}

void Unk_71024fe368::sub_710100B7E0(const sead::SafeString& name, s32 value, bool flag) {
    for (s32 i = 0; i < mEntries4.size(); ++i) {
        auto* entry = mEntries4.get(i);
        if (entry->_98 == -1) {
            entry->name.clear();
            entry->name.append(name);
            entry->_98 = value;
            entry->_9c = flag;
            return;
        }
    }
}

void Unk_71024fe368::hm16(s32 arg) {
    if (arg == 2)
        _248->_18 = 0;
    mSubHandle->sub_7101020C08(0.0f);
}

// Unk_71024fed48 (TU ..0x7101011210) and Unk_71024fee78 (TU ..0x7101011b2c) are separate TUs in the original.
Unk_71024fed48::~Unk_71024fed48() = default;

bool Unk_71024fed48::m10() {
    return mState != 0;
}

void Unk_71024fed48::m12(f32 fade_sec) {
    if (mState == 4)
        mState = 2;
    else if (mState == 3)
        mState = 1;
    else
        return;
    sub_710101D9D8();
}

void Unk_71024fed48::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    mState = mState == 1 ? 3 : mState == 2 ? 4 : 0;
}

Unk_71024fee78::~Unk_71024fee78() = default;

bool Unk_71024fee78::m11() {
    return mState == 2;
}

void Unk_71024fee78::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    mState = 0;
}
