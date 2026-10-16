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

// NON_MATCHING: placeholder destructor; the original (0x710100df48) also destroys members or bases
// this class does not declare yet.
Unk_71024fe970::~Unk_71024fe970() = default;

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
