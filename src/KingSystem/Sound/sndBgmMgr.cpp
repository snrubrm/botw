#include "KingSystem/Sound/sndBgmMgr.h"
#include <math/seadVector.h>
#include <prim/seadScopedLock.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndMusicDefinition.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldEnvMgr.h"

namespace ksys::snd {

// The TU statics at 0x710260f070 (static initialiser 0x7100ff8c18; the same layout as sndBgmCastle.cpp's).
namespace {
util::InitConstants sInitConstants;
util::InitTimeInfo sInitTimeInfo;
// 0x710260f088 (placeholder name; unused by the functions decompiled so far).
sead::Vector2f sUnk_710260F088{920.0f, 480.0f};
// 0x710260f090
sead::SafeString sMusicListPath = "Sound/Music/MusicList.bmscdef";
}  // namespace

// NON_MATCHING: the original skips the m4 call for an unknown type instead of testing the current _48.
// NON_MATCHING: store order of the FixedObjList setup (the original stores the list head before _a0)
Unk_SoundMgr30::Unk_SoundMgr30() = default;

Unk_SoundMgr30::~Unk_SoundMgr30() {
    if (_10) {
        delete _10;
        _10 = nullptr;
    }
    if (_18) {
        delete _18;
        _18 = nullptr;
    }
    if (_240) {
        delete _240;
        _240 = nullptr;
    }
    if (_78) {
        delete _78;
        _78 = nullptr;
    }
    if (mHeap) {
        mHeap->destroy();
        mHeap = nullptr;
    }
    mEntryPool.freeBuffer();
    mSpeakerBalanceSuppliers.freeBuffer();
}

void Unk_SoundMgr30::sub_7100FF8338(sead::Heap* heap) {
    _8 = sead::DynamicCast<MusicDefinition>(
        SoundMgr::instance()->_60->tryLoadResource(sMusicListPath, nullptr, 4));
    _10 = new (heap) Unk_SoundMgr30_10;
    _10->init(heap);
    _18 = new (heap) Unk_SoundMgr30_18;
    _18->init(heap);
}

void Unk_SoundMgr30::sub_7100FF8464(sead::Heap* heap, BgmControllerType type) {
    switch (type) {
    case BgmControllerType::_1:
        _48 = new (heap) Unk_710260f198();
        break;
    case BgmControllerType::_2:
    case BgmControllerType::_3:
        _48 = new (heap) Unk_710260f150(type);
        break;
    case BgmControllerType::_4:
        _48 = new (heap) Unk_710260f130();
        break;
    case BgmControllerType::_5:
        _48 = new (heap) Unk_710260f218();
        break;
    case BgmControllerType::_6:
    case BgmControllerType::_7:
    case BgmControllerType::_8:
    case BgmControllerType::_9:
        _48 = new (heap) Unk_710260f1f8(type);
        break;
    case BgmControllerType::_10:
        _48 = new (heap) Unk_710260f0c0();
        break;
    case BgmControllerType::_11:
        _48 = new (heap) Unk_710260f160();
        break;
    default:
        break;
    }
    if (_48)
        _48->m4(heap);
    _40 = type;
    _88 &= ~7;
}

void Unk_SoundMgr30::sub_7100FF85E0() {
    if (_48 && (_88 & 1)) {
        const f32 fade_sec = _54;
        _48->m7(fade_sec);
        _60.setValueImmediate(0.0f);
        _60.moveTo(1.0f, fade_sec);
        _88 &= ~1;
    }
    _88 &= ~2;
    if (_78)
        _78->sub_7101007960(_54);
    _88 &= ~4;
}

void Unk_SoundMgr30::sub_7100FF8684(s32 fade_type) {
    if (_48 && (_88 & 1)) {
        f32 fade_sec = 0.1f;
        if (fade_type == 1)
            fade_sec = _54;
        else if (fade_type == 2)
            fade_sec = _58;
        _48->m7(fade_sec);
        _60.setValueImmediate(0.0f);
        _60.moveTo(1.0f, fade_sec);
        _88 &= ~1;
    }
    _88 &= ~2;
}

void Unk_SoundMgr30::sub_7100FF8730() {
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
    if (_78)
        _78->sub_7101007B44();
    _40 = BgmControllerType::_0;
}

void Unk_SoundMgr30::sub_7100FF8780(s32 fade_type) {
    if (_48 && !(_88 & 1)) {
        const f32 fade_sec = fade_type == 1 ? _50 : 0.0f;
        _48->m6(fade_sec);
        _60.setValueImmediate(0.0f);
        _60.moveTo(1.0f, fade_sec);
        _88 |= 1;
    }
}

// NON_MATCHING: the inlined sub_7100FF8780 tests _48 before the flag in the original.
void Unk_SoundMgr30::sub_7100FF8804() {
    if (_88 & 2) {
        sub_7100FF8780(0);
        _88 &= ~2;
    }
    if (_88 & 4) {
        sub_7100FF88A8(0);
        _88 &= ~4;
    }
}

void Unk_SoundMgr30::sub_7100FF88A8(s32 fade_type) {
    if (_78)
        _78->sub_7101007AA0(fade_type == 1 ? _50 : 0.0f);
}

Unk_SoundMgr30_30* Unk_SoundMgr30::sub_7100FF8A24() {
    for (s32 i = 0; i < mSpeakerBalanceSuppliers.size(); ++i) {
        auto* supplier = mSpeakerBalanceSuppliers.get(i);
        if (!supplier->mHandle.isActive())
            return supplier;
    }
    return nullptr;
}

void Unk_SoundMgr30::sub_7100FF8AC4(s32 fade_type) {
    if (_78) {
        f32 fade_sec = 0.1f;
        if (fade_type == 1)
            fade_sec = _54;
        else if (fade_type == 2)
            fade_sec = _58;
        _78->sub_7101007A08(fade_sec);
    }
    _88 &= ~4;
}

}  // namespace ksys::snd

Unk_71024fc990::~Unk_71024fc990() = default;

namespace ksys::snd {

Unk_710260f0c0::Unk_710260f0c0() = default;

Unk_710260f0c0::~Unk_710260f0c0() {
    if (_90) {
        delete _90;
        _90 = nullptr;
    }
}

void Unk_710260f0c0::m4(sead::Heap* heap) {
    _90 = new (heap) Unk_71024fe948();
    if (_90)
        _90->sub_710100D604(heap);
    _8.sub_7100FF75DC(32, heap);
    _8._30 = &_c8;
    _8._38 = &_e8;
    _8.sub_7100FF7920(1, heap);
    _8.sub_7100FF7920(3, heap);
    _8.sub_7100FF7920(18, heap);
    _8.sub_7100FF7920(16, heap);
    _8.sub_7100FF7920(17, heap);
    _8.sub_7100FF7920(20, heap);
}

// NON_MATCHING: the original loads 1.25f from 0x71024fca70 (next to the root vtable) instead of an fmov immediate.
void Unk_710260f0c0::m5() {
    if (!(_c4 & 1))
        return;
    if (_90)
        _90->sub_710100D694();
    _8.sub_7100FF7698();

    auto* wm = world::Manager::instance();
    world::EnvMgr* env_mgr;
    if (wm && (env_mgr = wm->getEnvMgr()) && env_mgr->getPaletteSet() == 40) {
        if (_b8 && (_c4 & 4)) {
            _c0 += sub_710105E3A4();
            if (_c0 > 1.25f) {
                _b8->sub_71010038C0();
                _c4 &= ~4;
            }
        }
    } else {
        _c0 = 0;
        if (_b8 && !(_c4 & 4)) {
            _b8->m7(0.0f);
            _b8->sub_71010038AC();
            _b8->m6(0.0f);
            _c4 |= 4;
        }
    }
}

void Unk_710260f0c0::m6(f32 fade_sec) {
    if (_c4 & 1)
        return;
    if (_b8) {
        _b8->sub_71010038AC();
        _c4 |= 4;
        _c0 = 0;
    }
    if (_90)
        _90->_8 = true;
    _8.sub_7100FF7830(fade_sec);
    _c4 |= 1;
}

void Unk_710260f0c0::m7(f32 fade_sec) {
    if (_c4 & 1) {
        if (_90)
            _90->sub_710100D860();
        _8.sub_7100FF78A8(fade_sec);
        _c4 &= ~1;
    }
}

void Unk_710260f0c0::sub_7100FF8F34(Bgm* bgm) {
    bgm->m8(_c4 & 1);
    switch (bgm->getKind()) {
    case BgmKind::_3:
        _a8 = sead::DynamicCast<::Unk_71024fe368>(bgm);
        break;
    case BgmKind::_11:
        if (_90)
            _90->sub_710100D874(Unk_71024fe948Slot::_1, sead::DynamicCast<::Unk_71024fe808>(bgm));
        break;
    case BgmKind::_12:
        if (_90)
            _90->sub_710100D874(Unk_71024fe948Slot::_2, sead::DynamicCast<::Unk_71024fe808>(bgm));
        break;
    case BgmKind::_16:
        _98 = sead::DynamicCast<::Unk_71024fefe8>(bgm);
        break;
    case BgmKind::_17:
        _a0 = sead::DynamicCast<::Unk_71024feae8>(bgm);
        break;
    case BgmKind::_18:
        _b0 = sead::DynamicCast<::Unk_71024fd6c8>(bgm);
        _b0->_1f4 |= 0x10;
        break;
    case BgmKind::_20:
        _b8 = sead::DynamicCast<::Unk_71024fd948>(bgm);
        break;
    default:
        break;
    }
}

void Unk_710260f0c0::sub_7100FF92BC(Bgm* bgm) {
    switch (bgm->getKind()) {
    case BgmKind::_11:
        if (_90)
            _90->sub_710100D874(Unk_71024fe948Slot::_1, nullptr);
        break;
    case BgmKind::_12:
        if (_90)
            _90->sub_710100D874(Unk_71024fe948Slot::_2, nullptr);
        break;
    case BgmKind::_16:
        _98 = nullptr;
        break;
    case BgmKind::_17:
        _a0 = nullptr;
        break;
    case BgmKind::_20:
        _b8 = nullptr;
        break;
    default:
        break;
    }
}

void Unk_710260f0c0::m9(const Unk_BgmControllerM8Arg& arg) {
    auto* state = _90;
    if (!state)
        return;
    state->_c = arg._0;
    state->_14 = arg._8;
    state->_10 = arg._4;
    state->_18 = arg._c;
}

void Unk_710260f0c0::m10() {
    _a8->_224 = true;
    if (!_b0)
        return;
    if (_b0->m10() || (_c4 & 8))
        _b0->sub_7101002194();
}

void Unk_710260f0c0::sub_7100FF9810(s32 id, bool use_a0) {
    if (use_a0) {
        if (_a0)
            _a0->sub_710100F798();
    } else if (_98) {
        _98->sub_71010121D8();
    }
}

void Unk_710260f0c0::sub_7100FF9830(s32 id, bool use_a0) {
    if (use_a0) {
        if (_a0)
            _a0->sub_710100F860();
    } else if (_98) {
        _98->sub_71010122A0();
    }
}

void Unk_710260f0c0::sub_7100FF9850(s32 a, bool b, s32 id, bool use_a0) {
    if (use_a0) {
        if (_a0)
            _a0->sub_710100F900(b, id);
    } else if (_98) {
        _98->sub_7101012340(a, b);
    }
}

void Unk_710260f0c0::sub_7100FF987C(bool a, s32 id, bool use_a0) {
    if (use_a0) {
        if (_a0)
            _a0->sub_710100F8B0(a);
    } else if (_98) {
        _98->sub_71010122F0(a);
    }
}

void Unk_710260f0c0::sub_7100FF98A4() {
    if (_b0) {
        _b0->sub_7101002274();
        _c4 |= 2;
    }
}

// Only read here (0x710260f058); set by code that is not in the release build.
bool sUnk_710260F058;

// NON_MATCHING: the original reads sUnk_710260F058 with adrp (TU-local; a static would be folded away here) and walks
// the list nodes in other registers.
void Unk_SoundMgr30::sub_7100FF88D0() {
    if (!_89) {
        if (_48)
            _48->m5();
        if (_78)
            _78->update();
        if (_10)
            _10->sub_710101CFEC();
        _60.calc();
    }
    if (sUnk_710260F058)
        return;
    for (auto it = mObjects.begin(), end = mObjects.end(); it != end;) {
        auto& obj = *it;
        ++it;
        if (obj->sub_7101020CEC())
            mObjects.erase(&obj);
    }
}

// NON_MATCHING: the original schedules the list address (`add x0, x20, #0x90`) after the first zero store of the node.
void Unk_SoundMgr30::sub_7100FF8B24(Unk_710260f248* obj) {
    if (mObjects.isFull())
        return;
    *mObjects.emplaceBack() = obj;
}

void Unk_SoundMgr30::sub_7100FF8B94(Unk_710260f248* obj) {
    for (auto& it : mObjects) {
        if (it == obj) {
            mObjects.erase(&it);
            return;
        }
    }
}

Unk_710260f248Entry* Unk_SoundMgr30::sub_7100FF89A0() {
    for (s32 i = 0; i < mEntryPool.size(); ++i) {
        auto* entry = mEntryPool.get(i);
        if (!entry->mNode.isLinked()) {
            entry->sub_7100FF6A44();
            return entry;
        }
    }
    return nullptr;
}

Unk_SoundMgr30_18::~Unk_SoundMgr30_18() = default;

}  // namespace ksys::snd
