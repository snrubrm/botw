#include "Game/gameRumble.h"
#include <container/seadSafeArray.h>
#include <controller/seadPatternRumbleAddon.h>
#include <prim/seadScopedLock.h>

namespace uking {

// 0x71008991c4 (420 B, not decompiled; placeholder name): the rumble addon of the active controller.
sead::PatternRumbleAddon* sub_71008991C4();
// 0x7100899368 (436 B, not decompiled; placeholder name): stops the pattern on every controller.
void sub_7100899368();

// lane4 s85 (placeholder names): the default pattern strings (0x71025d0370, 0x71025d03a0, 0x71025d03d0).
static sead::SafeString sDefaultPatterns0[3] = {
    "************-------------",
    "*********************-------------------",
    "********************************************------",
};
static sead::SafeString sDefaultPatterns1[3] = {
    "*-*-*-*------",
    "**-**-*-*-*------",
    "*-***********-*-*--*------",
};
static sead::SafeString sDefaultPatterns2[3] = {
    "*---*--*---*--*----*--*---*---*--*-----*---*----*------*--*---",
    "*--*--**-----*-*--*--*-",
    "*-**-*-**-**-*-****-",
};

// Pattern buffers (Rumble::init copies the defaults into them).
sead::FixedSafeString<128> sPatternBuffer0;
sead::FixedSafeString<128> sPatternBuffer1;
sead::FixedSafeString<128> sPatternBuffer2;
sead::FixedSafeString<128> sPatternBuffer3;
sead::FixedSafeString<128> sPatternBuffer4;
sead::FixedSafeString<128> sPatternBuffer5;
sead::FixedSafeString<2048> sPatternBuffer6;
sead::FixedSafeString<2048> sPatternBuffer7;
sead::FixedSafeString<2048> sPatternBuffer8;

// 0x71025d0400: the pattern strings indexed by RumblePattern.
static sead::SafeString sPatterns[RumblePattern::size()] = {
    sPatternBuffer0, sPatternBuffer1, sPatternBuffer2,
    sPatternBuffer6, sPatternBuffer7, sPatternBuffer8,
};
// 0x71025d0460
static sead::SafeString sPatterns2[RumblePattern::size()] = {
    sPatternBuffer3, sPatternBuffer4, sPatternBuffer5,
    sPatternBuffer6, sPatternBuffer7, sPatternBuffer8,
};

// 0x71025d0300 (placeholder name): Rumble::calc only runs 0x7100898a20 when it is set. Nothing in this file
// writes it; the original loads it without the GOT.
bool sUnk_71025D0300;

SEAD_SINGLETON_DISPOSER_IMPL(Rumble)

// inline-only in the original; name is a guess. 0x7100897fe4 and 0x710089813c both copy the two patterns to the
// stack and compare `u32(p) < 6 ? p : 0` (a switch over the six patterns, folded to a linear map).
static int getPriority_(RumblePattern pattern) {
    switch (pattern) {
    case RumblePattern::_0:
        return 0;
    case RumblePattern::_1:
        return 1;
    case RumblePattern::_2:
        return 2;
    case RumblePattern::_3:
        return 3;
    case RumblePattern::_4:
        return 4;
    case RumblePattern::_5:
        return 5;
    }
    return 0;
}

// NON_MATCHING: the two stack slots of the getPriority_ copies are swapped (0x710089813c gets them right)
void Rumble::sub_7100897FE4(RumblePattern pattern, s32 count) {
    const int idx = pattern;
    const sead::SafeString* str = &sPatterns[idx];
    if (str == nullptr || str->calcLength() == 0)
        return;

    auto lock = sead::makeScopedLock(mMutex);
    if (!mState.mIsPlaying || getPriority_(mCurrentPattern) < getPriority_(idx)) {
        mState.mPattern = str->cstr();
        mState.mDurationSeconds = 0;
        mState.mPatternDuration = count;
        mState.mStartRequested = true;
        mCurrentPattern = idx;
    }
}

// NON_MATCHING: the original stores mPattern after the GetSystemTick call (cstr() is still called first)
void Rumble::sub_710089813C(RumblePattern pattern, s32 seconds) {
    const int idx = pattern;
    const sead::SafeString* str = &sPatterns[idx];
    if (str == nullptr || str->calcLength() == 0)
        return;

    auto lock = sead::makeScopedLock(mMutex);
    if (mState.mIsPlaying && getPriority_(mCurrentPattern) >= getPriority_(idx))
        return;

    mState.mPattern = str->cstr();
    mState.mDurationSeconds = seconds;
    mState.mStartTime.setNow();
    mState.mPatternDuration = 0;
    mState.mStartRequested = true;
    mCurrentPattern = idx;
}

void Rumble::init() {
    sPatternBuffer0 = sDefaultPatterns0[0];
    sPatternBuffer1 = sDefaultPatterns0[1];
    sPatternBuffer2 = sDefaultPatterns0[2];
    sPatternBuffer6 = sDefaultPatterns2[0];
    sPatternBuffer7 = sDefaultPatterns2[1];
    sPatternBuffer8 = sDefaultPatterns2[2];
}

void Rumble::sub_710089878C() {
    mState.stop();
}

void Rumble::State::calc() {
    if (mDurationSeconds != 0 &&
        mDurationSeconds < sead::TickTime().diff(mStartTime).toSeconds()) {
        stop();
        mDurationSeconds = 0;
    }

    auto* addon = sub_71008991C4();
    if (!addon)
        return;

    if (mStartRequested) {
        sub_7100899368();
        addon->startPattern(mPattern, mPatternDuration);
        mStartRequested = false;
    }
    mIsPlaying = addon->isPatternEnable();
}

// NON_MATCHING: sUnk_71025D0300 is loaded through the GOT (the original addresses it directly)
void Rumble::calc() {
    mState.calc();
    if (sUnk_71025D0300)
        sub_7100898A20();
}

}  // namespace uking
