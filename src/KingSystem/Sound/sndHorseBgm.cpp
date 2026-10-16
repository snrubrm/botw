#include <atomic>
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

// NON_MATCHING: regalloc (as Unk_71024feae8::sub_710100F798).
void Unk_71024fefe8::sub_71010121D8(s32 id) {
    while (mEntriesLock.load() == 1) {
    }
    while (!mEntriesLock.compareExchange(0, 1)) {
    }

    s32 free_idx = -1;
    bool found = false;
    for (s32 i = 0; i < mEntries.size(); ++i) {
        if (mEntries[i].id == id) {
            found = true;
            break;
        }
        if (mEntries[i].id == 0 && free_idx < 0)
            free_idx = i;
    }
    if (!found && free_idx >= 0) {
        mEntries[free_idx] = {};
        mEntries[free_idx].id = id;
    }

    std::atomic_thread_fence(std::memory_order_seq_cst);
    while (!mEntriesLock.compareExchange(1, 0)) {
    }
}

bool Unk_71024fefe8::m10() {
    if (_124 != 3 && _124 != 4)
        return false;
    return _160[1] >= mInfo->mFeelPlayingSec.ref();
}

bool Unk_71024fefe8::m11() {
    return mState == 2;
}

void Unk_71024fefe8::sub_71010122A0(s32 id) {
    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto& entry = mEntries[i];
        if (entry.id == id) {
            entry = {};
            return;
        }
    }
}

void Unk_71024fefe8::sub_71010122F0(bool value, s32 id) {
    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto& entry = mEntries[i];
        if (entry.id == id) {
            entry._4 = value;
            return;
        }
    }
}

void Unk_71024fefe8::sub_7101012340(s32 value, bool flag, s32 id) {
    if (_1ec < value)
        _1ec = value;
    if (flag)
        _1f0 = true;
    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto& entry = mEntries[i];
        if (entry.id == id) {
            entry._5 = flag;
            return;
        }
    }
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
