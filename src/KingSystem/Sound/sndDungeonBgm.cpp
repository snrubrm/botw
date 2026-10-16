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
    _1b4 = false;
}
