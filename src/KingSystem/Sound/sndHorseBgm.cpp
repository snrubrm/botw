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

// TU 0x7101011274..0x71010131cc (static initialiser) in the original.

// NON_MATCHING: the two secondary-vtable thunks (0x7101011d98 / 0x7101011e3c) differ in register allocation.
Unk_71024fefe8::~Unk_71024fefe8() {
    mEntries.freeBuffer();
}

namespace ksys::snd {

Unk_710260f278::Unk_710260f278(const BgmInitArg& arg) : Unk_71025ce380(arg) {
    _1c0.setCurveType(aal::FadeCurveType::Square);
    auto* heap = arg.heap;
    mInfo = static_cast<HorseBgmInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::HorseBgm));
    Unk_SpotBgmHandle::init(heap, "HorseBgm", nullptr);
}

Unk_710260f278::~Unk_710260f278() = default;

void Unk_710260f278::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    _198 = 0;
    _1a8 = 0;
    _1b0 = 0;
}

}  // namespace ksys::snd
