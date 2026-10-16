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

// TU 0x710100f2a8..0x7101010a34 (static initialiser) in the original.

namespace {
sead::SafeString sStr_GuardianFixedBgm = "GuardianFixedBgm";
sead::SafeString sStr_GuardianFixedBgmMain = "main";
}  // namespace

// NON_MATCHING: the original zeroes 0x1d8 alone and 0x1dc / 0x1e4 as two unaligned doublewords (tried u32[2] and a
// two-word struct; clang merges 0x1d8..0x1e8 differently).
Unk_71024feae8::Unk_71024feae8(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    auto* heap = arg.heap;
    Unk_SpotBgmHandle::init(heap, sStr_GuardianFixedBgm, nullptr);
    mInfo = ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::GuardianFixedBgm);
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
    mInfo = ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::GanonBeastBgm);
}

Unk_71024fec18::~Unk_71024fec18() = default;
