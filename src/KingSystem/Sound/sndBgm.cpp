#include "KingSystem/Sound/sndBgmMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndMusicInfo.h"

namespace ksys::snd {

namespace {
sead::SafeString sStr_AssassinBossBgm = "AssassinBossBgm";
sead::SafeString sStr_main = "main";
}  // namespace

Unk_710260f048::Unk_710260f048(const BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, sStr_AssassinBossBgm, nullptr);
    mInfo = static_cast<AssassinSeniorBgmInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::_12));
}

void Unk_710260f048::m5() {
    if (mState == 2 && mStopTimer != 0 && --mStopTimer == 0) {
        sub_710101D9F4(0.0);
        mState = 0;
    }
}

void Unk_710260f048::m12(f32 fade_sec) {
    if (mState == 1)
        sub_710101D9D8();
}

void Unk_710260f048::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    if (mState == 2) {
        mStopTimer = 0;
        mState = 0;
    }
}

void Unk_710260f048::sub_7100FF61BC() {}

void Unk_710260f048::sub_7100FF61C0() {
    if (mState == 1)
        return;
    sub_710101D9D8();
    mState = 1;
}

void Unk_710260f048::sub_7100FF61F8(bool battle) {
    if (battle)
        mMainFader.moveTo(1.0, *mInfo->mToBattleFadeSec);
    else
        mMainFader.moveTo(0.0, *mInfo->mToDemoFadeSec);
}

void Unk_710260f048::sub_7100FF6220() {
    if (mState != 1)
        return;
    sub_7101020C08(0.1);
    mState = 2;
    mStopTimer = 300;
}

void Unk_710260f048::sub_7100FF6268() {
    if (mState == 0)
        return;
    sub_710101D9F4(*mInfo->mFadeOutSec);
    mState = 0;
}

bool Unk_710260f048::m10() {
    if (_124 == 3 || _124 == 4)
        return _160[1] >= *mInfo->mFeelPlayingSec;
    return false;
}

void Unk_710260f048::hm14() {
    mMainEntry = sub_71010209FC(sStr_main);
    if (mMainEntry && mMainEntry->sub_7100FF6DF4(this))
        mMainEntry->sub_7100FF6A50(1, 1.0);
}

void Unk_710260f048::hm15() {
    mMainFader.calc();
    if (mMainEntry && mMainEntry->sub_7100FF6DF4(this))
        mMainEntry->sub_7100FF6A50(1, mMainFader.getValue());
}

void Bgm::m4() {}

void Bgm::m6(f32 fade_sec) {
    if (mActive)
        return;
    m12(fade_sec);
    m8(true);
}

void Bgm::m7(f32 fade_sec) {
    if (mActive) {
        m13(fade_sec);
        m8(false);
    }
}

void Bgm::m8(bool active) {
    mActive = active;
}

bool Bgm::m10() {
    return false;
}

bool Bgm::m11() {
    return false;
}

void Bgm::m12(f32 fade_sec) {}
void Bgm::m13(f32 fade_sec) {}
void Bgm::m14(sead::TextWriter& writer) {}

// Defined in this TU: the BGM controllers (sndBgmMgr.cpp, sndBattleDungeonBgm.cpp) call the constructor 0x7100ff7408
// and destructor 0x7100ff7444 out of line.
Unk_7100ff7444::Unk_7100ff7444() = default;

Unk_7100ff7444::~Unk_7100ff7444() {
    sub_7100FF74D0();
    mEntries.freeBuffer();
}

void Unk_7100ff7444::sub_7100FF75DC(s32 capacity, sead::Heap* heap) {
    mEntries.allocBuffer(capacity, heap, 8);
}

void Unk_7100ff7444::sub_7100FF7830(f32 fade_sec) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& entry : mEntries)
        entry.bgm->m6(fade_sec);
}

void Unk_7100ff7444::sub_7100FF78A8(f32 fade_sec) {
    auto lock = sead::makeScopedLock(mCS);
    for (auto& entry : mEntries)
        entry.bgm->m7(fade_sec);
}

}  // namespace ksys::snd
