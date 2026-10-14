#include "KingSystem/Sound/sndBgmMgr.h"
#include <prim/seadScopedLock.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldEnvMgr.h"

namespace ksys::snd {

void Unk_SoundMgr30::sub_7100FF88A8(s32 fade_type) {
    if (_78)
        _78->sub_7101007AA0(fade_type == 1 ? _50 : 0.0f);
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

}  // namespace ksys::snd
