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

// TU 0x710100ce68..0x710100f268 (static initialiser) in the original.

Unk_71024fe808::~Unk_71024fe808() = default;

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
