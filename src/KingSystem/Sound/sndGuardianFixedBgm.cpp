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

// TU 0x710100f2a8..0x7101010a34 (static initialiser) in the original.

namespace {
sead::SafeString sStr_GuardianFixedBgm = "GuardianFixedBgm";
sead::SafeString sStr_GuardianFixedBgmMain = "main";
}  // namespace

Unk_71024feae8::Unk_71024feae8(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    auto* heap = arg.heap;
    Unk_SpotBgmHandle::init(heap, sStr_GuardianFixedBgm, nullptr);
    mInfo = static_cast<ksys::snd::GuardianFixedBgmInfo*>(
        ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::GuardianFixedBgm));
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

bool Unk_71024feae8::m10() {
    if (_124 != 3 && _124 != 4)
        return false;
    return _160[1] >= mInfo->mFeelPlayingSec.ref();
}

bool Unk_71024feae8::m11() {
    return mState == 2;
}

void Unk_71024feae8::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    mState = 0;
    _1dc = 0;
    _1e0 = 0;
    _1e4 = 0;
    _1e8 = 0;
}

Unk_71024fec18::Unk_71024fec18(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, "GanonBeastBgm", nullptr);
    mInfo = static_cast<ksys::snd::GanonBeastBgmInfo*>(
        ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::GanonBeastBgm));
}

Unk_71024fec18::~Unk_71024fec18() = default;

void Unk_71024fec18::m5() {
    if (_198 != 0 && _124 == 0)
        sub_710101D9D8();
    _1b0.calc();
}

bool Unk_71024fec18::m10() {
    return _198 != 0;
}

void Unk_71024fec18::m12(f32 fade_sec) {
    if (_198 != 1 && _198 != 2)
        return;
    _198 = 1;
    sub_710101D9D8();
}

void Unk_71024fec18::hm14() {
    if (_198 != 1)
        return;
    if (!_1a8 || !_1a8->sub_7100FF6DF4(this))
        _1a8 = sub_71010209FC(Level::text(_1a4));
    if (_1a8 && _1a8->sub_7100FF6DF4(this))
        _198 = 1;
}

void Unk_71024fec18::hm15() {
    if (_198 != 2)
        return;
    _19c += ksys::snd::sub_710105E3A4();
    if (_19c > _1a0) {
        _19c = _1a0;
        if (_1a8 && _1a8->sub_7100FF6DF4(this))
            _1a8->sub_7100FF6A64(mInfo->mFadeOutSec.ref());
        _1a8 = sub_71010209FC(Level::text(_1a4));
        if (_1a8 && _1a8->sub_7100FF6DF4(this))
            _198 = 1;
    }
}

// NON_MATCHING: regalloc (entry count / buffer registers swapped).
void Unk_71024feae8::sub_710100F798(s32 id) {
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

void Unk_71024feae8::sub_710100F860(s32 id) {
    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto& entry = mEntries[i];
        if (entry.id == id) {
            entry = {};
            return;
        }
    }
}

void Unk_71024feae8::sub_710100F8B0(bool value, s32 id) {
    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto& entry = mEntries[i];
        if (entry.id == id) {
            entry._4 = value;
            return;
        }
    }
}

void Unk_71024feae8::sub_710100F900(bool value, s32 id) {
    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto& entry = mEntries[i];
        if (entry.id == id) {
            entry._5 = value;
            return;
        }
    }
}
