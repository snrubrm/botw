#include <atomic>
#include "KingSystem/Sound/sndBgmMgr.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2EventSLink.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <aal/aalHandle.h>
#include <aal/aalMarkerController.h>
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

// NON_MATCHING: store scheduling (the original writes _1f4 after both merged zero stores).
void Unk_71024fefe8::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    _1dc = 0;
    _1e0 = 0;
    _1e1 = 0;
    _1e2 = 0;
    _1e3 = 0;
    _1e4 = 0;
    _1e8 = 0;
    _1f4 = 0;
    _1fc = -1;
    _200.clear();
    _220 = 0.0f;
    _224 = 0.0f;
    mState = 0;
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

namespace {
// 0x71024fefb8 / 0x71024fefc8
sead::SafeString sStr_GuardianBgmMain = "main";
sead::SafeString sStr_GuardianBgmHit = "hit";
}  // namespace

// 0x7101012470 (unnamed in the CSV): the marker callback installed by Unk_71024fefe8::hm14.
void sub_7101012470(const aal::MarkerController::MarkerCallbackInfo& info, void* user) {
    auto* bgm = static_cast<Unk_71024fefe8*>(user);
    if (info.type != 1)
        return;
    bgm->_1fc = info.id;
    if (bgm->_200.isEmpty())
        return;
    if (bgm->mState == 1)
        bgm->sub_71010209FC(bgm->_200);
    bgm->_220 = 0.0f;
    bgm->_224 = *bgm->mInfo->mIgnoreReserveCountDownSec;
    bgm->_200.clear();
}

void Unk_71024fefe8::hm14() {
    _228 = sub_71010209FC(sStr_GuardianBgmMain);
    if (!_228 || !_228->sub_7100FF6DF4(this))
        return;
    auto* entry = _228;
    if (entry->mHandle.isActive())
        entry->mHandle.getEvent()->resetFlagBit(1);
    if (!entry->mHandle.isActive())
        return;
    auto* event = static_cast<xlink2::EventSLink*>(entry->mHandle.getEvent());
    if (auto* executor = event->getAliveAssetExecutor()) {
        auto* handle = executor->getHandle();
        if (handle->getMarkerController()) {
            handle->getMarkerController()->setMarkerCallback(sub_7101012470,
                                                             *mInfo->mMarkerCallbackOffsetSample, this);
            _1fc = -1;
        }
    }
}

// NON_MATCHING: block placement of the "%sC" format call (the original puts it before the shared call)
void Unk_71024fefe8::hm15() {
    if (mState == 1 || mState == 2) {
        if (_228 && !_228->sub_7100FF6DF4(this)) {
            sub_710101D9F4(0.0f);
            return;
        }
        if (mState == 1) {
            if (_224 > 0.0f) {
                _224 -= ksys::snd::sub_710105E3A4();
                if (_224 < 0.0f)
                    _224 = 0.0f;
            }
            if (_1dc >= *mInfo->mDamageThresholdHitReserve && _224 == 0.0f) {
                const u32 next = _1fc + 1;
                if (next >= *mInfo->mMarkerIdHitSectionB && next < *mInfo->mMarkerIdHitSectionA) {
                    const u32 section_c = *mInfo->mMarkerIdHitSectionC;
                    if (next >= section_c)
                        _200.format("%sC", sStr_GuardianBgmHit.cstr());
                    else
                        _200.format("%sB", sStr_GuardianBgmHit.cstr());
                } else {
                    _200.format("%sA", sStr_GuardianBgmHit.cstr());
                }
                _220 = _160[1];
                _224 = *mInfo->mCancelHitSec;
            }
        }
    }
    if (_220 > 0.0f && _160[1] >= _220 + *mInfo->mCancelHitSec) {
        _200.clear();
        _220 = 0.0f;
        _224 = 0.0f;
    }
}

namespace ksys::snd {

// 0x710260fd64 / 0x710260fd68 / 0x710260fd6c: the horse BGM's debug flags (nothing in the game writes
// them): 0x...64 forces the state checks to pass, 0x...68 makes m5 / hm15 read the state counter from
// 0x...6c instead of _1a0.
KSYS_VISIBILITY_HIDDEN bool sUnk_710260FD64;
KSYS_VISIBILITY_HIDDEN bool sUnk_710260FD68;
KSYS_VISIBILITY_HIDDEN s32 sUnk_710260FD6C;

// The loop assets hm14 plays by the time of day (0x71024ff248; the night one when _1a4 is set).
const char* const sHorseLoopNames[] = {"horseDay_loop", "horseNight_loop"};
// The outro assets hm15 plays (0x71024ff258).
const char* const sHorseEndNames[] = {"horseDay_end", "horseNight_end"};

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
    _1ac = 0;
    _1b0 = 0;
}

void Unk_710260f278::m5() {
    if (!mActive || !(_68._18 & 1))
        return;

    const f32 dt = sub_710105E3A4();
    if (_1b0 >= 0.0f) {
        _1b0 -= dt;
        if (_1b0 < 0.0f)
            _1b0 = 0.0f;
    }

    if (_198 == 0) {
        const f32 wait_target = mInfo->mPlayWaitSec.ref();
        if (sUnk_710260FD64 || _19c) {
            const s32 state = sUnk_710260FD68 ? sUnk_710260FD6C : _1a0;
            if (state >= 3) {
                f32 wait = _1a8;
                if (wait < wait_target) {
                    wait += dt;
                    _1a8 = wait;
                    if (wait > wait_target) {
                        wait = wait_target;
                        _1a8 = wait_target;
                    }
                }
                if (wait >= wait_target && _1b0 <= 0.0f)
                    sub_710101D9D8();
            } else {
                _1a8 = 0.0f;
            }
        } else {
            _1a8 = 0.0f;
        }
    }

    if (_1e8) {
        sub_710101D9F4(0.0f);
        _1a8 = 0.0f;
        _1ac = 0.0f;
        _1c0.setValueImmediate(0.0f);
        _198 = 0;
        _1e8 = false;
    }

    _1c0.calc();
    if (auto* status = SoundMgr::instance()->_288) {
        if (_19c) {
            PlayingPart part = PlayingPart::RidingHorse;
            status->mPlayingPart[part] = true;
        }
    }
}

void Unk_710260f278::hm14() {
    if (!(sUnk_710260FD64 || _19c)) {
        _1e8 = true;
        return;
    }

    const s32* state = sUnk_710260FD68 == false ? &_1a0 : &sUnk_710260FD6C;
    if (*state <= 1) {
        _1e8 = true;
        return;
    }

    const f32 time = world::Manager::instance()->getTimeMgrUnchecked()->getTime() / 15.0f;
    bool night = false;
    if (!(time >= mInfo->mTimeDay.ref()))
        night = true;
    else if (!(time < mInfo->mTimeNight.ref()))
        night = true;
    _1a4 = night;
    sub_71010209FC(sHorseLoopNames[night]);
    _198 = 1;
    _1c0.setValueImmediate(mInfo->mMinVolume.ref());
    _1c0.moveTo(1.0f, mInfo->mFadeInSec.ref());
    _1b0 = 0.0f;
}

void Unk_710260f278::hm15() {
    if (_1e8)
        return;

    switch (_198) {
    case 1: {
        bool fade_out;
        if (sUnk_710260FD64 || _19c) {
            const s32* state = sUnk_710260FD68 == false ? &_1a0 : &sUnk_710260FD6C;
            if (*state <= 1)
                _1ac += sub_710105E3A4();
            else
                _1ac = 0.0f;
            fade_out = false;
        } else {
            fade_out = true;
        }
        const f32 wait = mInfo->mFadeOutWaitSec.ref();
        if (_1ac >= wait) {
            _1ac = wait;
            fade_out = true;
        }
        if (fade_out) {
            _1c0.moveTo(0.0f, mInfo->mFadeOutSec.ref());
            _1b0 = mInfo->mIgnoreRequestSec.ref();
            _198 = 2;
        }
        break;
    }
    case 2:
        if (_1c0.getValue() != _1c0.getNextValue())
            break;
        if ((sUnk_710260FD64 || _19c) && _160[1] >= mInfo->mPlayingSecUseOutro.ref()) {
            sub_7101020C08(0.0f);
            _1b8 = sub_71010209FC(sHorseEndNames[_1a4]);
            _1c0.setValueImmediate(1.0f);
            _198 = 3;
            break;
        }
        sub_710101D9F4(0.0f);
        _1a8 = 0.0f;
        _1ac = 0.0f;
        _1c0.setValueImmediate(0.0f);
        _198 = 0;
        break;
    case 3:
        if (_1b8 && _1b8->sub_7100FF6DF4(this))
            break;
        sub_710101D9F4(0.0f);
        _1a8 = 0.0f;
        _1ac = 0.0f;
        _1c0.setValueImmediate(0.0f);
        _198 = 0;
        break;
    }

    _a4 = _1c0.getValue();
    if (auto* status = SoundMgr::instance()->_288) {
        PlayingPart part = PlayingPart::PlayingHorseBgm;
        status->mPlayingPart[part] = true;
    }
}

}  // namespace ksys::snd
