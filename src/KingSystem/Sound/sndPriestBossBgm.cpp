#include "KingSystem/Sound/sndBgmMgr.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <aal/aalHandle.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2EventSLink.h>
#include <xlink2/xlink2ResourceAccessorSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

// TU 0x710100ce68..0x710100f268 (static initialiser) in the original.

Unk_71024fe808::~Unk_71024fe808() = default;

bool Unk_71024fe808::m10() {
    if (_124 == 3 || _124 == 4)
        return _160[1] >= static_cast<ksys::snd::BossBgmInfo*>(mInfo)->mFeelPlayingSec.ref();
    return false;
}

void Unk_71024fe808::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    mState = 0;
}

namespace {
// 0x71024fe7f8
const sead::SafeString sStr_Main = "main";
}  // namespace

void Unk_71024fe808::hm14() {
    sub_71010209FC(sStr_Main);
}

// NON_MATCHING: the original's RingBuffer::freeBuffer also zeroes head and size before the delete[] (our sead
// zeroes them after).
Unk_71024fe970::~Unk_71024fe970() {
    mStateQueue.freeBuffer();
}

// NON_MATCHING: the address of mFlags is computed once for both branches here.
void Unk_71024fe970::hm14() {
    if (mType == ksys::snd::Unk_710260f248Type::_3 || (_68._18 & 3))
        mFlags &= ~2;
    else
        mFlags |= 2;
    if (!(mFlags & 2))
        sub_710100E6A8();
}

void Unk_71024fe970::sub_710100E0C4() {
    mFlags = (mFlags & ~0x101) | 1;
    sub_710101D9D8();
}

void Unk_71024fe970::sub_710100E108() {
    mFlags |= 4;
    _1a0._41 = true;
    _1e8._41 = true;
}

namespace {
// 0x71024feaa0
const char* sPriestBossBgmLevelNames[] = {"Level1", "Level2", "Level3", "Level4", "Transform"};
}  // namespace

// NON_MATCHING: the level name and the SafeString vtable are loaded in another order around the stores.
void Unk_71024fe970::sub_710100E6A8() {
    mFlags = (mFlags & ~0x88) | 0x80;
    _1a0.reset();
    _1e8.reset();
    auto* entry = sub_71010209FC(sPriestBossBgmLevelNames[_198]);
    if (!entry || !entry->sub_7100FF6DF4(this))
        return;
    _1a0.sub_710100D9FC(entry);
    if (!entry->mHandle.isActive())
        return;
    auto* executor = static_cast<xlink2::EventSLink*>(entry->mHandle.getEvent())->getAliveAssetExecutor();
    if (!executor)
        return;
    auto* marker = executor->getHandle()->getMarkerController();
    if (mFlags & 0x100)
        _1a0.sub_710100DB1C(2.5f);
    if (marker)
        marker->setMarkerCallback(markerCallback, -32000, this);
}

void Unk_71024fe970::markerCallback(const aal::MarkerController::MarkerCallbackInfo& info, void* user) {
    if (user)
        static_cast<Unk_71024fe970*>(user)->sub_710100EAD8(info);
}

bool Unk_71024fe970::m10() {
    return mFlags & 1;
}

void Unk_71024fe970::m12(f32 fade_sec) {
    if (!(mFlags & 1))
        return;
    mFlags |= 0x101;
    sub_710101D9D8();
}

void Unk_71024fe970::m13(f32 fade_sec) {
    if (mFlags & 0x78)
        _198 = _19c;
    mFlags = (mFlags & ~0x178) | 0x100;
    sub_710101D9F4(fade_sec);
}

namespace ksys::snd {

// NON_MATCHING: the original zeroes _c / _10 with one unaligned doubleword store.
Unk_71024fe958::Unk_71024fe958() = default;

Unk_71024fe958::~Unk_71024fe958() = default;

void Unk_71024fe958::m2() {}

void Unk_71024fe958::init(sead::Heap* heap) {
    mInfos[1] = sub_7100FFD76C()->getInfo(MusicInfoType::GolemBgm);
    mInfos[2] = sub_7100FFD76C()->getInfo(MusicInfoType::GiantBgm);
    mInfos[3] = sub_7100FFD76C()->getInfo(MusicInfoType::SandwormBgm);
}

void Unk_71024fe958::sub_710100D860() {
    if (!_8)
        return;
    _1c = 0;
    _8 = false;
}

void Unk_71024fe958::sub_710100D874(Index idx, Unk_71024fe808* bgm) {
    mBgms[idx] = bgm;
    if (bgm)
        bgm->mInfo = mInfos[idx];
}

}  // namespace ksys::snd
