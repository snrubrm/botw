#include "KingSystem/Sound/sndBgmMgr.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <aal/aalHandle.h>
#include <aal/aalMarkerController.h>
#include <aal/aalSoundSource.h>
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

void Unk_71024fe808::sub_710100D0B8(f32 wait_sec) {
    if (mState == 0 || mState == 6) {
        _19c = wait_sec;
        _1a0 = 0.0f;
        mState = 1;
    } else if (mState == 3) {
        _1a8.moveTo(1.0f, 1.0f);
        mState = 2;
    }
}

void Unk_71024fe808::sub_710100D114(f32 fade_sec) {
    switch (mState) {
    case 1:
        mState = 0;
        break;
    case 2:
        if (_124 == 3 || _124 == 4) {
            _1a8.moveTo(0.0f, fade_sec);
            mState = 3;
        } else {
            sub_710101D9F4(0.0f);
            mState = 0;
        }
        break;
    case 3:
        _1a8.moveTo(0.0f, fade_sec);
        break;
    case 6:
        sub_710101D9F4(0.0f);
        mState = 0;
        break;
    default:
        break;
    }
}

void Unk_71024fe808::sub_710100D1A4(bool on, u32 value, f32 wait_sec) {
    _1e0 = on;

    if (mState != 2)
        return;

    if (wait_sec > 0.0f) {
        _1d0 = wait_sec;
        mState = 4;
        return;
    }

    if (_124 == 3 || _124 == 4) {
        sub_7101020C08(-1.0f);
        _1d8 = sub_71010209FC("outro");
        if (_1d8 && _1d8->sub_7100FF6DF4(this)) {
            mState = 5;
            return;
        }
    }

    if (_1e0) {
        sub_710101D9F4(0.0f);
        mState = 0;
    } else {
        mState = 6;
    }
}

void Unk_71024fe808::m5() {
    if (!mActive)
        return;

    switch (mState) {
    case 1:
        _1a0 += ksys::snd::sub_710105E3A4();
        if (_1a0 >= _19c && (_68._18 & 1)) {
            _1a0 = _19c;
            _1a8.setValueImmediate(1.0f);
            sub_710101D9D8();
            mState = 2;
        }
        break;
    case 3:
        if (_1a8.getValue() != _1a8.getNextValue())
            break;
        sub_710101D9F4(0.0f);
        mState = 0;
        break;
    case 4:
        if (_1d0 > 0.0f)
            _1d0 -= ksys::snd::sub_710105E3A4();
        if (_1d0 <= 0.0f) {
            if (_124 == 3 || _124 == 4) {
                sub_7101020C08(-1.0f);
                _1d8 = sub_71010209FC("outro");
                if (_1d8 && _1d8->sub_7100FF6DF4(this)) {
                    mState = 5;
                    break;
                }
            }
            if (!_1e0) {
                mState = 6;
            } else {
                sub_710101D9F4(0.0f);
                mState = 0;
            }
        }
        break;
    case 5:
        if (_1d8 && _1d8->sub_7100FF6DF4(this))
            break;
        if (!_1e0) {
            mState = 6;
            break;
        }
        sub_710101D9F4(0.0f);
        mState = 0;
        break;
    default:
        break;
    }

    _1a8.calc();
    _a4 = _1a8.getValue();
}

Unk_71024fe970::Unk_71024fe970(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, "FinalTrialBossBgm", nullptr);
    mStateQueue.tryAllocBuffer(8, arg.heap);
    mInfo = static_cast<ksys::snd::FinalTrialBossBattleBgmInfo*>(
        ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::FinalTrialBossBattleBgm));
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

// NON_MATCHING: the original reloads the state after the push (ours merges the tails).
void Unk_71024fe970::sub_710100E124(const s32& state) {
    if (!(mFlags & 1) || _198 == state)
        return;
    if (mFlags & 0x78)
        mStateQueue.pushBack(state);
    _19c = state;
    mFlags |= 8;
}

// NON_MATCHING: the original selects the entry handle pointer (entry ? &entry->mHandle : nullptr) before its
// checks, and converts the sample rate as signed (lib getSampleRate converts it as unsigned).
void Unk_71024fe970::sub_710100E194(const s32& state) {
    if (!(mFlags & 1) || _198 == state)
        return;

    aal::Handle* handle = nullptr;
    {
        const Slot& current = (mFlags & 0x80) ? _1a0 : _1e8;
        if (current.mEntry && current.mEntry->mHandle.isActive()) {
            if (auto* executor = static_cast<xlink2::EventSLink*>(current.mEntry->mHandle.getEvent())
                                     ->getAliveAssetExecutor()) {
                handle = executor->getHandle();
            }
        }
    }
    const Slot& current = (mFlags & 0x80) ? _1a0 : _1e8;
    if (!current.mEntry || !current.mEntry->mHandle.isActive())
        return;
    auto* executor =
        static_cast<xlink2::EventSLink*>(current.mEntry->mHandle.getEvent())->getAliveAssetExecutor();
    if (!executor)
        return;
    auto* source = executor->getHandle()->getSoundSource();
    if (!handle || !source)
        return;

    const f32 wait_sec = state == 4 ? mInfo->mTransformDemoWaitSec.ref() : 1.0f;
    const s32 position = handle->getPlaySamplePosition();
    sub_710100E2FC(state, s32(wait_sec * source->getAssetInfo()->getSampleRate()) + position);
    _19c = state;
}

void Unk_71024fe970::sub_710100E0C4() {
    mFlags = (mFlags & ~0x101) | 1;
    sub_710101D9D8();
}

void Unk_71024fe970::sub_710100E0E0() {
    mFlags = (mFlags & ~0x119) | 0x100;
    sub_710101D9F4(mInfo->mStopFadeSec.ref());
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

// NON_MATCHING: ring buffer index computed differently; block layout around the slot selection and the curve
// parameter loads differs.
void Unk_71024fe970::hm15() {
    if (mFlags & 2) {
        if (mType != ksys::snd::Unk_710260f248Type::_3 && !(_68._18 & 3))
            return;
        sub_710100E6A8();
        mFlags &= ~2;
    }

    if ((mFlags & 1) && !(_1a0.mEntry && _1a0.mEntry->sub_7100FF6DF4(this)) &&
        !(_1e8.mEntry && _1e8.mEntry->sub_7100FF6DF4(this))) {
        hm14();
    }

    if (mStateQueue.size() != 0 && !(mFlags & 0x78)) {
        if (mFlags & 1) {
            const s32 state = mStateQueue(0);
            if (_198 != state) {
                _19c = state;
                mFlags |= 8;
            }
        }
        mStateQueue.popFront();
    }

    if (mFlags & 0x20) {
        Slot& current = (mFlags & 0x80) ? _1a0 : _1e8;
        s32 position = -1;
        if (current.mEntry && current.mEntry->mHandle.isActive()) {
            if (auto* executor = static_cast<xlink2::EventSLink*>(current.mEntry->mHandle.getEvent())
                                     ->getAliveAssetExecutor()) {
                position = executor->getHandle()->getPlaySamplePosition();
            }
        }
        ((mFlags & 0x80) ? _1e8 : _1a0)._30 = position;
    }

    _1a0.sub_710100D8B8();
    _1e8.sub_710100D8B8();

    if ((mFlags & 0x20) && ((mFlags & 0x80) ? _1e8 : _1a0)._3c == 2) {
        Slot& current = (mFlags & 0x80) ? _1a0 : _1e8;
        f32 fade_sec;
        aal::FadeCurveType curve;
        if (!mInfo) {
            fade_sec = 1.0f;
            curve = aal::FadeCurveType::Square;
        } else {
            if (u32(_19c) < 3)
                fade_sec = mInfo->mFadeSecFromTransformDemo.ref();
            else if (_19c == 3)
                fade_sec = mInfo->mFadeSeLevel3To4.ref();
            else if (_19c == 4)
                fade_sec = mInfo->mFadeSecToTransformDemo.ref();
            else
                fade_sec = 1.0f;

            if (u32(_19c) < 3)
                curve = mInfo->toFadeCurveTypeMaybe(mInfo->mCurveTypeFromTransformDemo.ref());
            else if (_19c == 3)
                curve = mInfo->toFadeCurveTypeMaybe(mInfo->mCurveTypeLevel3To4.ref());
            else if (_19c == 4)
                curve = mInfo->toFadeCurveTypeMaybe(mInfo->mCurveTypeToTransformDemo.ref());
            else
                curve = aal::FadeCurveType::Square;
        }
        current.sub_710100DC60(fade_sec, curve);
        mFlags = (mFlags & ~0x60) | 0x40;
    }

    if ((mFlags & 0x40) && ((mFlags & 0x80) ? _1a0 : _1e8)._3c == 0) {
        mFlags = (mFlags & ~0x40) ^ 0x80;
        _198 = _19c;
    }
}

// NON_MATCHING: branch layout (the original reloads the state after each case).
void Unk_71024fe970::Slot::sub_710100D8B8() {
    if (!mEntry)
        return;
    switch (_3c) {
    case 4:
        if (mFader.getValue() == mFader.getNextValue()) {
            mEntry->sub_7100FF6A64(0.01f);
            _34 = -1;
            mEntry = nullptr;
            _38 = 0.0f;
            _3c = 0;
            _40 = true;
        }
        break;
    case 2:
        if (mFader.getValue() == mFader.getNextValue())
            _3c = 3;
        break;
    case 1:
        if (_34 < _30 || sead::Mathi::abs(_30 - _34) < 1600) {
            if (!mEntry->mHandle.isActive())
                break;
            auto* executor =
                static_cast<xlink2::EventSLink*>(mEntry->mHandle.getEvent())->getAliveAssetExecutor();
            if (!executor)
                break;
            if (auto* source = executor->getHandle()->getSoundSource()) {
                source->startPrepared();
                mFader.setValueImmediate(0.0f);
                mFader.moveTo(1.0f, _38);
                _3c = 2;
            }
        }
        break;
    }
    if (_3c != 0) {
        mFader.calc();
        if (mEntry)
            mEntry->_20 = sead::Mathf::max(mFader.getValue(), 0.0f);
    }
}

// NON_MATCHING: the original selects the entry handle pointer (entry ? &entry->mHandle : nullptr) before its checks.
void Unk_71024fe970::Slot::sub_710100DB1C(f32 fade_sec) {
    if (!mEntry)
        return;
    aal::Handle* handle = nullptr;
    if (mEntry->mHandle.isActive()) {
        if (auto* executor =
                static_cast<xlink2::EventSLink*>(mEntry->mHandle.getEvent())->getAliveAssetExecutor()) {
            handle = executor->getHandle();
        }
        if (!mEntry)
            return;
    }
    if (!mEntry->mHandle.isActive())
        return;
    auto* executor = static_cast<xlink2::EventSLink*>(mEntry->mHandle.getEvent())->getAliveAssetExecutor();
    if (!executor)
        return;
    auto* source = executor->getHandle()->getSoundSource();
    if (!handle || !source)
        return;
    const s32 position = source->mMarkerController->getMarkerSamplePos("ReEntryPoint");
    source->setStartSamplePos(ksys::snd::sub_710105E6CC(position, handle->getAssetInfo()));
    _38 = fade_sec;
    _3c = 2;
    mFader.setCurveType(aal::FadeCurveType::Linear);
    mFader.setValueImmediate(0.0f);
    mFader.moveTo(1.0f, fade_sec);
}

// NON_MATCHING: fmax instead of fmaxnm for the clamp; the original keeps the handle pointer select of the reloaded
// entry.
void Unk_71024fe970::Slot::sub_710100DC60(f32 fade_sec, const aal::FadeCurveType& curve) {
    if (_3c == 3)
        mFader.setValueImmediate(1.0f);
    mFader.moveTo(0.0f, fade_sec);
    mFader.setCurveType(curve);
    mEntry->_20 = sead::Mathf::max(mFader.getValue(), 0.0f);
    _3c = 4;
    auto* handle = mEntry ? &mEntry->mHandle : nullptr;
    if (!handle || !handle->isActive())
        return;
    auto* executor = static_cast<xlink2::EventSLink*>(handle->getEvent())->getAliveAssetExecutor();
    if (!executor)
        return;
    if (auto* marker = executor->getHandle()->getMarkerController())
        marker->setMarkerCallback(emptyMarkerCallback, 0, this);
}

void Unk_71024fe970::Slot::emptyMarkerCallback(const aal::MarkerController::MarkerCallbackInfo& info, void* user) {}

// NON_MATCHING: the entry handle pointer select (as in sub_710100E194) and the curve parameter load order.
s32 Unk_71024fe970::sub_710100E2FC(const s32& state, s32 position) {
    Slot& next = (mFlags & 0x80) ? _1e8 : _1a0;
    if (next._3c != 0)
        return -1;
    if (((mFlags & 0x80) ? _1a0 : _1e8)._3c == 0)
        return -1;

    aal::Handle* handle = nullptr;
    {
        const Slot& current = (mFlags & 0x80) ? _1a0 : _1e8;
        if (current.mEntry && current.mEntry->mHandle.isActive()) {
            if (auto* executor = static_cast<xlink2::EventSLink*>(current.mEntry->mHandle.getEvent())
                                     ->getAliveAssetExecutor()) {
                handle = executor->getHandle();
            }
        }
    }
    const Slot& current = (mFlags & 0x80) ? _1a0 : _1e8;
    if (!current.mEntry || !current.mEntry->mHandle.isActive())
        return -1;
    auto* executor =
        static_cast<xlink2::EventSLink*>(current.mEntry->mHandle.getEvent())->getAliveAssetExecutor();
    if (!executor)
        return -1;
    auto* source = executor->getHandle()->getSoundSource();
    if (!handle || !source)
        return -1;

    const s32 end = source->mMarkerController->getMarkerSamplePos("[NW]#4");
    if (end == -1)
        return -1;
    if (end < position) {
        const s32 loop_start = source->mMarkerController->getMarkerSamplePos("[NW]#3");
        if (loop_start == -1)
            return -1;
        position -= loop_start;
    }
    _230 = ksys::snd::sub_710105E6CC(position, handle->getAssetInfo());

    auto* entry = sub_71010209FC(sPriestBossBgmLevelNames[state]);
    if (!entry || !entry->sub_7100FF6DF4(this))
        return -1;
    next.sub_710100D9FC(entry);
    if (!entry->mHandle.isActive())
        return -1;
    auto* entry_executor =
        static_cast<xlink2::EventSLink*>(entry->mHandle.getEvent())->getAliveAssetExecutor();
    if (!entry_executor)
        return -1;
    entry_executor->getHandle()->getMarkerController()->setMarkerCallback(markerCallback, -32000, this);

    const s32 start = _230;
    f32 fade_sec;
    aal::FadeCurveType curve;
    if (!mInfo) {
        fade_sec = 1.0f;
        curve = aal::FadeCurveType::Square;
    } else {
        if (u32(state) < 3)
            fade_sec = mInfo->mFadeSecFromTransformDemo.ref();
        else if (state == 3)
            fade_sec = mInfo->mFadeSeLevel3To4.ref();
        else if (state == 4)
            fade_sec = mInfo->mFadeSecToTransformDemo.ref();
        else
            fade_sec = 1.0f;

        if (u32(state) < 3)
            curve = mInfo->toFadeCurveTypeMaybe(mInfo->mCurveTypeFromTransformDemo.ref());
        else if (state == 3)
            curve = mInfo->toFadeCurveTypeMaybe(mInfo->mCurveTypeLevel3To4.ref());
        else if (state == 4)
            curve = mInfo->toFadeCurveTypeMaybe(mInfo->mCurveTypeToTransformDemo.ref());
        else
            curve = aal::FadeCurveType::Square;
    }

    if (next.mEntry && next.mEntry->mHandle.isActive()) {
        if (auto* next_executor =
                static_cast<xlink2::EventSLink*>(next.mEntry->mHandle.getEvent())->getAliveAssetExecutor()) {
            if (auto* next_source = next_executor->getHandle()->getSoundSource()) {
                next_source->setStartSamplePos(start);
                next_source->prepare(true);
                next._34 = start;
                next._38 = fade_sec;
                next._3c = 1;
                next.mFader.setValueImmediate(0.0f);
                next.mFader.setCurveType(curve);
            }
        }
    }
    mFlags |= 0x20;
    return _230;
}

// NON_MATCHING: slot selection registers and the entry handle pointer select (as in sub_710100E194).
void Unk_71024fe970::sub_710100EAD8(const aal::MarkerController::MarkerCallbackInfo& info) {
    const sead::SafeString name = info.name;
    if (name.findIndex("[NW]") != -1)
        return;
    if (name == "ReEntryPoint")
        return;
    _250 = name;
    if ((mFlags & 0x68) != 8)
        return;
    if (name == "73")
        return;
    if (((mFlags & 0x80) ? _1e8 : _1a0)._3c != 0)
        return;

    auto* entry = sub_71010209FC(sPriestBossBgmLevelNames[_19c]);
    Slot& next = (mFlags & 0x80) ? _1e8 : _1a0;
    if (!entry || !entry->sub_7100FF6DF4(this))
        return;
    if (next._3c != 0)
        return;
    next.sub_710100D9FC(entry);
    if (!entry->mHandle.isActive())
        return;
    auto* entry_executor =
        static_cast<xlink2::EventSLink*>(entry->mHandle.getEvent())->getAliveAssetExecutor();
    if (!entry_executor)
        return;
    auto* marker = entry_executor->getHandle()->getMarkerController();
    if (!marker)
        return;
    marker->setMarkerCallback(markerCallback, -32000, this);

    const Slot& current = (mFlags & 0x80) ? _1a0 : _1e8;
    if (current._3c == 0)
        return;
    if (!current.mEntry || !current.mEntry->mHandle.isActive())
        return;
    auto* executor =
        static_cast<xlink2::EventSLink*>(current.mEntry->mHandle.getEvent())->getAliveAssetExecutor();
    if (!executor)
        return;
    auto* handle = executor->getHandle();
    if (!handle->isActive())
        return;
    const s32 start = ksys::snd::sub_710105E6CC(info.sample_position, handle->getAssetInfo());
    _230 = start;

    f32 fade_sec;
    aal::FadeCurveType curve;
    if (!mInfo) {
        fade_sec = 1.0f;
        curve = aal::FadeCurveType::Square;
    } else {
        if (u32(_19c) < 3)
            fade_sec = mInfo->mFadeSecFromTransformDemo.ref();
        else if (_19c == 3)
            fade_sec = mInfo->mFadeSeLevel3To4.ref();
        else if (_19c == 4)
            fade_sec = mInfo->mFadeSecToTransformDemo.ref();
        else
            fade_sec = 1.0f;

        if (u32(_19c) < 3)
            curve = mInfo->toFadeCurveTypeMaybe(mInfo->mCurveTypeFromTransformDemo.ref());
        else if (_19c == 3)
            curve = mInfo->toFadeCurveTypeMaybe(mInfo->mCurveTypeLevel3To4.ref());
        else if (_19c == 4)
            curve = mInfo->toFadeCurveTypeMaybe(mInfo->mCurveTypeToTransformDemo.ref());
        else
            curve = aal::FadeCurveType::Square;
    }

    if (next.mEntry && next.mEntry->mHandle.isActive()) {
        if (auto* next_executor =
                static_cast<xlink2::EventSLink*>(next.mEntry->mHandle.getEvent())->getAliveAssetExecutor()) {
            if (auto* next_source = next_executor->getHandle()->getSoundSource()) {
                next_source->setStartSamplePos(start);
                next_source->prepare(true);
                next._34 = start;
                next._38 = fade_sec;
                next._3c = 1;
                next.mFader.setValueImmediate(0.0f);
                next.mFader.setCurveType(curve);
            }
        }
    }
    mFlags = (mFlags & ~0x28) | 0x20;
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

// The debug override of the boss BGM index and the flag that forces the outro (never written in the release build).
struct Unk_710260FAB8Debug {
    u8 flag;
    u32 value;
};
KSYS_VISIBILITY_HIDDEN Unk_710260FAB8Debug sUnk_710260FAB8;

// NON_MATCHING: register allocation and the safe-array index CSE differ (the original reloads the
// index for every access).
void Unk_71024fe958::sub_710100D694() {
    if (!_8)
        return;

    const u32 next = sUnk_710260FAB8.value ? sUnk_710260FAB8.value : _c;
    if (next != _1c) {
        if (mBgms[_1c]) {
            f32 fade_sec = static_cast<BossBgmInfo*>(mInfos[_1c])->mFadeOutSec.ref();
            if (mBgms[next])
                fade_sec = static_cast<BossBgmInfo*>(mInfos[_1c])->mChangeTypeFadeOutSec.ref();
            mBgms[_1c]->sub_710100D114(fade_sec);
        }
        if (mBgms[next]) {
            mBgms[next]->sub_710100D0B8(
                static_cast<BossBgmInfo*>(mInfos[next])->mPlayWaitSec.ref());
        }
        _1c = next;
    }

    if (mBgms[_1c]) {
        const s32 state = mBgms[_1c]->mState;
        if (state == 0) {
            _1c = 0;
        } else if (state == 2 && ((sUnk_710260FAB8.flag & 1) || (_14 >> 8))) {
            mBgms[_1c]->sub_710100D1A4(
                true, _18, static_cast<BossBgmInfo*>(mInfos[_1c])->mOutroWaitSec.ref());
        }
    }

    _18 = 0;
    _c = 0;
    _10 = 0;
    _14 = 0;
    sUnk_710260FAB8.flag = 0;
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
