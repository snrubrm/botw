#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "Game/Actor/aiUnk_7100FFD79C.h"
#include "Game/Actor/aiUnk_7100FFDFDC.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndFxMgr.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include <gfx/seadTextWriter.h>
#include <nn/atk.h>
#include <aal/aalHandle.h>
#include <aal/aalSoundSource.h>
#include <xlink2/xlink2EventSLink.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

// The dragon, dungeon normal and dungeon reward BGMs: TU 0x71010010fc..0x71010073b4 in the original (static
// initialisers 0x71010010a4 before it and 0x71010073b4 at its end; the environment BGM code in sndEnvBgm.cpp follows
// in the same TU).

namespace {
sead::SafeString sStr_DungeonBattleBgm = "DungeonBattleBgm";
}  // namespace

namespace ksys::snd {

// NON_MATCHING: zero stores of 0x10 / 0x18..0x28 / 0x58 scheduled in another order.
Unk_710260f2a8::Unk_710260f2a8(const BgmInitArg& arg) : Bgm(arg.kind) {
    _38.setValueImmediate(1.0);
    sub_7101001194(arg);
}

namespace {
const char* sDragonBgmAssetNames[] = {"Dragon", "Dragon"};
}  // namespace

void Unk_710260f2a8::sub_7101001194(const BgmInitArg& arg) {
    sead::Heap* heap = arg.heap;
    for (s32 i = 0; i < DragonBgmInfo::DragonEnum::size(); ++i) {
        const char* name = DragonBgmInfo::DragonEnum::text(i);
        const DragonBgmInfo::DragonEnum type = i;
        auto* handle = new (heap, 8) Unk_71024fd3a0(arg.handle_type);
        handle->sub_7101022DEC(heap, name, sDragonBgmAssetNames[type]);
        handle->sub_710101D970();
        mHandles[type] = handle;
    }
    _10 = static_cast<DragonBgmInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::DragonBgm));
    _28 = mHandles[0];
}

Unk_710260f2a8::~Unk_710260f2a8() {
    for (auto*& handle : mHandles) {
        if (handle) {
            handle->sub_710101D9A4();
            delete handle;
            handle = nullptr;
        }
    }
}

void Unk_710260f2a8::m4(sead::Heap* heap) {
    DragonBgmInfo::DragonEnum type = DragonBgmInfo::DragonEnum::DragonBgm;
    if (mHandles[type])
        mHandles[type]->sub_7101020988(heap);
    type = DragonBgmInfo::DragonEnum::GrudgeDragonBgm;
    if (mHandles[type])
        mHandles[type]->sub_7101020988(heap);
}

// NON_MATCHING: the first size test is inverted (cmp #0 / b.le instead of cmp #1 / b.ge to the shared return).
// NON_MATCHING: the original copies the dragon index _30 to a stack slot before each parameter lookup (an
// enum-typed copy, e.g. a DragonEnum by value); ours indexes directly.
void Unk_710260f2a8::m5() {
    if (!mActive)
        return;

    bool near = false;
    if (_58)
        near = _5c < _10->mParamPerTypes[_30].mDistanceThreshold.ref();

    switch (_34) {
    case 0:
        if (!near) {
            _50 = 0;
            break;
        }
        _50 += sub_710105E3A4();
        if (_50 <= _10->mParamPerTypes[_30].mPlayWaitSec.ref())
            break;
        _28 = mHandles[_60];
        _30 = _60;
        _50 = _10->mParamPerTypes[_30].mPlayWaitSec.ref();
        _38.setValueImmediate(0.0f);
        _38.moveTo(1.0f, _10->mParamPerTypes[_30].mFadeInSec.ref());
        _54 = 0;
        _28->sub_710101D9D8();
        _34 = 1;
        break;
    case 1:
        if (near) {
            _54 = 0;
            break;
        }
        _54 += sub_710105E3A4();
        if (_54 <= _10->mParamPerTypes[_30].mFadeWaitSec.ref())
            break;
        _38.moveTo(0.0f, _10->mParamPerTypes[_30].mFadeOutSec.ref());
        _34 = 2;
        break;
    case 2:
        if (near) {
            _38.moveTo(1.0f, 1.0f);
            _34 = 1;
        }
        // fallthrough
    case 3:
        if (_38.getValue() == _38.getTarget()) {
            _28->sub_710101D9F4(0.0f);
            _50 = 0;
            _54 = 0;
            _34 = 0;
        }
        break;
    }

    _38.calc();
    _28->_a4 = _38.getValue();
}

bool Unk_710260f2a8::m9() {
    DragonBgmInfo::DragonEnum type = DragonBgmInfo::DragonEnum::DragonBgm;
    if (mHandles[type] && mHandles[type]->mEntries.size() >= 1)
        return false;
    type = DragonBgmInfo::DragonEnum::GrudgeDragonBgm;
    if (mHandles[type] && mHandles[type]->mEntries.size() > 0)
        return false;
    return true;
}

void Unk_710260f2a8::m12(f32 fade_sec) {
    for (auto* handle : mHandles)
        handle->sub_7101020BB0(fade_sec);
}

void Unk_710260f2a8::m13(f32 fade_sec) {
    DragonBgmInfo::DragonEnum type = DragonBgmInfo::DragonEnum::DragonBgm;
    mHandles[type]->sub_710101D9F4(fade_sec);
    type = DragonBgmInfo::DragonEnum::GrudgeDragonBgm;
    mHandles[type]->sub_710101D9F4(fade_sec);
    _28->sub_710101D9F4(0.0);
    _50 = 0;
    _54 = 0;
    _34 = 0;
}

// 0x710260f4d8: debug flag (never written).
KSYS_VISIBILITY_HIDDEN bool sUnk_710260F4D8;
// 0x71024fd5f8: the debug text position.
KSYS_VISIBILITY_HIDDEN sead::Vector2f sUnk_71024FD5F8{360.0f, 80.0f};

void Unk_710260f2a8::m14(sead::TextWriter& writer) {
    if (!sUnk_710260F4D8)
        return;
    writer.setCursorFromTopLeft(sUnk_71024FD5F8);
    writer.printf("---- ドラゴンBGM ----\n");
    writer.printf("処理              :%s\n", mActive ? "有効" : "無効");
    writer.printf("ドラゴン存在?     :%s\n", _58 ? "Yes" : "No");
    writer.printf("ドラゴン怨念付?   :%s\n", _60 ? "Yes" : "No");
    writer.printf("ドラゴンとの距離  :%f\n", _5c);
    writer.printf("現在のBGM種別     :%s\n",
                  DragonBgmInfo::DragonEnum::text(_30) ? DragonBgmInfo::DragonEnum::text(_30) : "不明");
    writer.printf("状態              :%s\n", State::text(_34) ? State::text(_34) : "不明");
    writer.printf("再生待ちカウンタ  :%f\n", _50);
    writer.printf("停止待ちカウンタ  :%f\n", _54);
    writer.printf("フェーダボリューム:%f\n", _38.getValue());
}

}  // namespace ksys::snd

Unk_71024fd6c8::Unk_71024fd6c8(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, sStr_DungeonBattleBgm, nullptr);
    mInfo = static_cast<ksys::snd::DungeonBattleBgmInfo*>(
        ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::DungeonBattleBgm));
}

Unk_71024fd6c8::~Unk_71024fd6c8() = default;

bool Unk_71024fd6c8::m11() {
    return mState == 2;
}

void Unk_71024fd6c8::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    _1ec = 0;
    mState = 0;
}

namespace {
// 0x71024fd6a8 / 0x71024fd6b8
const sead::SafeString sStr_Main = "main";
const sead::SafeString sStr_Outro = "outro";
}  // namespace

// 0x710260f5b8 (placeholder name): a debug override of _1e8 read by the stream region callback; hm14 resets it.
KSYS_VISIBILITY_HIDDEN s32 sUnk_710260F5B8;

// 0x7101002374 (declared only): the stream region callback of Unk_71024fd6c8.
nn::atk::StreamRegionCallbackResult sub_7101002374(nn::atk::StreamRegionCallbackParam* param,
                                                   void* user);

void Unk_71024fd6c8::hm14() {
    mEntry = sub_71010209FC(sStr_Main);
    if (mEntry && mEntry->sub_7100FF6DF4(this)) {
        auto* entry = mEntry;
        if (entry->mHandle.isActive())
            entry->mHandle.getEvent()->resetFlagBit(1);
        if (entry->mHandle.isActive()) {
            auto* event = static_cast<xlink2::EventSLink*>(entry->mHandle.getEvent());
            if (auto* executor = event->getAliveAssetExecutor()) {
                auto* handle = executor->getHandle();
                if (handle->isActive()) {
                    auto* source = handle->getSoundSource();
                    source->setStreamRegionCallback(sub_7101002374, this);
                    source->setVirtualizeMode(aal::VirtualizeMode::Restart);
                }
            }
        }
    }
    _1f0 = -1;
    _1f4 |= 7;
    _1e8 = 0;
    sUnk_710260F5B8 = 0;
}

// NON_MATCHING: the base pointer this + 0x10 is computed once up front in the original; block order of the tail.
void Unk_71024fd6c8::sub_7101002194() {
    _1f4 &= ~8;
    if (mEntry && mEntry->sub_7100FF6DF4(this))
        mEntry->sub_7100FF6A64(0.0f);
    _1d0 = sub_71010209FC(sStr_Outro);
    if (!_1d0 || !_1d0->sub_7100FF6DF4(this)) {
        sub_710101D9F4(0.0f);
        _1ec = 0;
        mState = 0;
        return;
    }
    if (_1f4 & 0x10)
        _1a0.setValueImmediate(1.0f);
    mState = 4;
}

void Unk_71024fd6c8::sub_7101002274() {
    _1f4 |= 8;
    _1ec = mInfo->mPlayWaitSec.ref();
}

bool Unk_71024fd6c8::m10() {
    if (_124 != 3 && _124 != 4)
        return false;
    return _160[1] > mInfo->mVolumeNormal.ref();
}

void Unk_71024fd6c8::hm15() {
    if (mState != 1 && mState != 2)
        return;
    if (!mEntry || mEntry->sub_7100FF6DF4(this))
        return;
    hm14();
}

namespace {
sead::SafeString sStr_DungeonNormalBgm = "DungeonNormalBgm";
}  // namespace

Unk_71024fd808::Unk_71024fd808(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    _1b8 = 0.8108108f;
    _198 = 9.72973f;
    Unk_SpotBgmHandle::init(arg.heap, sStr_DungeonNormalBgm, nullptr);
    mInfo = static_cast<ksys::snd::DungeonNormalBgmInfo*>(
        ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::DungeonNormalBgm));
}

Unk_71024fd808::~Unk_71024fd808() = default;

void Unk_71024fd808::m5() {
    if (!mActive || !(_68._18 & 1))
        return;
    if (_1b0 == 2) {
        _1b4 += ksys::snd::sub_710105E3A4();
        const f32 delay = mInfo->mTitleDelaySec.ref();
        if (_1b4 > delay) {
            _1b4 = delay;
            sub_710101D9D8();
            _1b0 = 0;
        }
    } else if (_1b0 == 0 && _124 == 0) {
        sub_710101D9D8();
    }
}

void Unk_71024fd808::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
}

void Unk_71024fd808::hm14() {
    _1bc = 0;
    _1ac = 0;
    _1ad = 0;
    _1a4 = 0;
    _1a6 = 0;
    _1a8 = 0;
    _1aa = 0;
    _19c = 0;
    _1a0 = 0;
}

// NON_MATCHING: the original keeps the two parts in a stack pair and reloads them after the calls.
void Unk_71024fd808::sub_71010029B8() {
    _1b0 = !mActive;
}

void Unk_71024fd808::sub_71010029CC() {
    if (_1b0 == 1) {
        _1b0 = 2;
        _1b4 = 0;
    } else {
        _1b0 = 0;
    }
}

void Unk_71024fd808::sub_7101003198() {
    Part::ValueType first;
    Part::ValueType second;
    switch (sead::GlobalRandom::instance()->getU32(3)) {
    case 0:
        first = Part::Bass;
        second = Part::Strings;
        break;
    case 1:
        first = Part::Bass;
        second = Part::Arp;
        break;
    default:
        first = Part::Strings;
        second = Part::Arp;
        break;
    }
    if (_68._18 & 1) {
        sub_71010209FC(Part::text(second));
        sub_71010209FC(Part::text(first));
    }
    _1ac |= (1 << second) | (1 << first);
}

namespace {
sead::SafeString sStr_DungeonRewardBgm = "DungeonRewardBgm";
}  // namespace

Unk_71024fd948::Unk_71024fd948(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    _1ac = 0.8108108f;
    _198 = 9.72973f;
    Unk_SpotBgmHandle::init(arg.heap, sStr_DungeonRewardBgm, nullptr);
    mInfo = static_cast<ksys::snd::DungeonRewardBgmInfo*>(
        ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::DungeonRewardBgm));
}

Unk_71024fd948::~Unk_71024fd948() = default;

void Unk_71024fd948::m5() {
    if (!mActive || !(_68._18 & 1))
        return;
    if (_1a4 == 2) {
        _1a8 += ksys::snd::sub_710105E3A4();
        const f32 delay = mInfo->mTitleDelaySec.ref();
        if (_1a8 > delay) {
            _1a8 = delay;
            sub_710101D9D8();
            _1a4 = 0;
        }
    } else if (_1a4 == 0 && _124 == 0) {
        sub_710101D9D8();
    }
}

void Unk_71024fd948::sub_71010038AC() {
    _1a4 = !mActive;
}

void Unk_71024fd948::sub_71010038C0() {
    if (_1a4 == 1) {
        _1a4 = 2;
        _1a8 = 0;
    } else {
        _1a4 = 0;
    }
}

void Unk_71024fd948::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
}

void Unk_71024fd948::hm14() {
    _19c = 0;
    _1a0 = 0;
    _1b0 = 0;
    _1b4 = 0;
}

void Unk_71024fd948::sub_7101003A74() {
    if (_68._18 & 1) {
        const u32 first = sead::GlobalRandom::instance()->getU32(8);
        u32 second = sead::GlobalRandom::instance()->getU32(7);
        if (first == second)
            ++second;
        const sead::FormatFixedSafeString<32> first_name("Piano_0%d", first);
        sub_71010209FC(first_name);
        const sead::FormatFixedSafeString<32> second_name("Piano_0%d", second);
        sub_71010209FC(second_name);
    }
    _1b4 |= 1;
}

// NON_MATCHING: scheduling of the two floor divisions; the original recomputes this + 0x10 per call.
void Unk_71024fd948::hm15() {
    if (_19c == 0.0f || sead::Mathf::floor(_160[1] / _198) != sead::Mathf::floor(_19c / _198)) {
        if (_19c != 0.0f)
            ++_1a0;
        if (_68._18 & 1)
            sub_71010209FC("Bell");
        sub_7101003A74();
        if (sead::GlobalRandom::instance()->getF32() * 100.0f < mInfo->mOddsPlayableString.ref()) {
            if (_68._18 & 1)
                sub_71010209FC("Strings");
            _1b4 |= 2;
        } else {
            _1b4 &= ~2;
        }
    }
    _19c = _160[1];
}
