#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

// Defined here: the controller destructors inline it while it calls ~Unk_7100ff7444 (0x7100ff7444) out of line.
Unk_71024fca78::~Unk_71024fca78() = default;

Unk_710260f130* sub_7100FFD9D0() {
    Unk_71024fca78* controller = nullptr;
    if (auto* sound = SoundMgr::instance()) {
        if (sound->_30)
            controller = sound->_30->_48;
    }
    return sead::DynamicCast<Unk_710260f130>(controller);
}

Unk_710260f218* sub_7100FFDA7C() {
    Unk_71024fca78* controller = nullptr;
    if (auto* sound = SoundMgr::instance()) {
        if (sound->_30)
            controller = sound->_30->_48;
    }
    return sead::DynamicCast<Unk_710260f218>(controller);
}

Unk_710260f278* sub_7100FFDD38() {
    auto* controller = SoundMgr::instance()->_30->_48;
    return sead::DynamicCast<Unk_710260f278>(controller ? controller->_8.sub_7100FF7C74(2) : nullptr);
}

Unk_710260f2a8* sub_7100FFE094() {
    auto* controller = SoundMgr::instance()->_30->_48;
    return sead::DynamicCast<Unk_710260f2a8>(controller ? controller->_8.sub_7100FF7C74(15) : nullptr);
}

Unk_710260f198* sub_7100FFD7CC() {
    Unk_71024fca78* controller = nullptr;
    if (auto* sound = SoundMgr::instance()) {
        if (sound->_30)
            controller = sound->_30->_48;
    }
    return sead::DynamicCast<Unk_710260f198>(controller);
}

Unk_710260f1f8* sub_7100FFD878() {
    Unk_71024fca78* controller = nullptr;
    if (auto* sound = SoundMgr::instance()) {
        if (sound->_30)
            controller = sound->_30->_48;
    }
    return sead::DynamicCast<Unk_710260f1f8>(controller);
}

Unk_710260f150* sub_7100FFD924() {
    Unk_71024fca78* controller = nullptr;
    if (auto* sound = SoundMgr::instance()) {
        if (sound->_30)
            controller = sound->_30->_48;
    }
    return sead::DynamicCast<Unk_710260f150>(controller);
}

Unk_710260f0c0* sub_7100FFDB28() {
    Unk_71024fca78* controller = nullptr;
    if (auto* sound = SoundMgr::instance()) {
        if (sound->_30)
            controller = sound->_30->_48;
    }
    return sead::DynamicCast<Unk_710260f0c0>(controller);
}

Unk_710260f160* sub_7100FFDBD4() {
    Unk_71024fca78* controller = nullptr;
    if (auto* sound = SoundMgr::instance()) {
        if (sound->_30)
            controller = sound->_30->_48;
    }
    return sead::DynamicCast<Unk_710260f160>(controller);
}

// NON_MATCHING: the original passes kind 0 as `mov x1, xzr` (64-bit zero); ours is `mov w1, wzr`
Unk_71025ce350* sub_7100FFDC80() {
    auto* controller = SoundMgr::instance()->_30->_48;
    return sead::DynamicCast<Unk_71025ce350>(controller ? controller->_8.sub_7100FF7C74(0) : nullptr);
}

Unk_710260f288* sub_7100FFDDF0() {
    auto* controller = SoundMgr::instance()->_30->_48;
    return sead::DynamicCast<Unk_710260f288>(controller ? controller->_8.sub_7100FF7C74(6) : nullptr);
}

Unk_710260f048* sub_7100FFDFDC() {
    auto* controller = SoundMgr::instance()->_30->_48;
    return sead::DynamicCast<Unk_710260f048>(controller ? controller->_8.sub_7100FF7C74(14) : nullptr);
}

Unk_710260f1a8* sub_7100FFE14C() {
    auto* controller = SoundMgr::instance()->_30->_48;
    return sead::DynamicCast<Unk_710260f1a8>(controller ? controller->_8.sub_7100FF7C74(5) : nullptr);
}

void Unk_710260f218::sub_7100FFC7F4() {
    if (auto* bgm = sead::DynamicCast<Unk_710260f228>(_8.sub_7100FF7C74(21)))
        bgm->sub_71010267A8(Unk_71010267A8{1});
}

void Unk_710260f218::sub_7100FFC894() {
    if (auto* bgm = sead::DynamicCast<Unk_710260f228>(_8.sub_7100FF7C74(21)))
        bgm->sub_71010267A8(Unk_71010267A8{2});
}

void Unk_710260f218::sub_7100FFC934() {
    if (auto* bgm = sead::DynamicCast<Unk_710260f228>(_8.sub_7100FF7C74(21)))
        bgm->sub_71010267A8(Unk_71010267A8{3});
}

Unk_710260f130::Unk_710260f130() = default;

void Unk_710260f130::sub_7100FF9CC8(Bgm* bgm) {
    bgm->m8(_90);
}

void Unk_710260f130::m4(sead::Heap* heap) {
    _8.sub_7100FF75DC(3, heap);
    _8._30 = &_98;
    _8.sub_7100FF7920(20, heap);
    _8.sub_7100FF7920(19, heap);
    _8.sub_7100FF7920(18, heap);
}

void Unk_710260f130::m5() {
    if (_90)
        _8.sub_7100FF7698();
}

void Unk_710260f130::m6(f32 fade_sec) {
    _92 = false;
    if (!_90) {
        _8.sub_7100FF7830(fade_sec);
        _90 = true;
    }
}

void Unk_710260f130::m7(f32 fade_sec) {
    if (_90) {
        _8.sub_7100FF78A8(fade_sec);
        _90 = false;
    }
}

void Unk_710260f130::m8(const Unk_BgmControllerM8Arg& arg) {
    if (auto* bgm = sead::DynamicCast<Unk_71024fd6c8>(_8.sub_7100FF7C74(18)))
        bgm->sub_710100215C(arg);
}

void Unk_710260f130::m10() {
    if (auto* bgm = sead::DynamicCast<Unk_71024fd6c8>(_8.sub_7100FF7C74(18)))
        bgm->sub_7101002194();
}

void Unk_710260f130::sub_7100FF9F0C() {
    if (auto* bgm = sead::DynamicCast<Unk_71024fd6c8>(_8.sub_7100FF7C74(18)))
        bgm->sub_7101002274();
}

void Unk_710260f130::sub_7100FF9FA8() {
    if (auto* bgm = sead::DynamicCast<Unk_71024fd808>(_8.sub_7100FF7C74(19)))
        bgm->sub_71010029B8();
    if (auto* bgm = sead::DynamicCast<Unk_71024fd948>(_8.sub_7100FF7C74(20)))
        bgm->sub_71010038AC();
}

void Unk_710260f130::sub_7100FFA0C4() {
    if (auto* bgm = sead::DynamicCast<Unk_71024fd808>(_8.sub_7100FF7C74(19)))
        bgm->sub_71010029CC();
    if (auto* bgm = sead::DynamicCast<Unk_71024fd948>(_8.sub_7100FF7C74(20)))
        bgm->sub_71010038C0();
}

void Unk_710260f130::sub_7100FFA1E0(bool value) {
    if (!_92)
        return;
    _91 = value;
    if (value)
        _8.sub_7100FF7BE0(Unk_7100FF7BE0{19});
    else
        _8.sub_7100FF7BE0(Unk_7100FF7BE0{20});
}

Unk_710260f150::Unk_710260f150(BgmControllerType type) : _91(type == BgmControllerType::_3) {}

void Unk_710260f150::sub_7100FFA46C(Bgm* bgm) {
    bgm->m8(_90);
}

void Unk_710260f150::m4(sead::Heap* heap) {
    _8.sub_7100FF75DC(2, heap);
    _8._30 = &_98;
    if (_91)
        _8.sub_7100FF7920(20, heap);
    else
        _8.sub_7100FF7920(19, heap);
    _8.sub_7100FF7920(18, heap);
}

void Unk_710260f150::m5() {
    if (_90)
        _8.sub_7100FF7698();
}

void Unk_710260f150::m6(f32 fade_sec) {
    if (!_90) {
        _8.sub_7100FF7830(fade_sec);
        _90 = true;
    }
}

void Unk_710260f150::m7(f32 fade_sec) {
    if (_90) {
        _8.sub_7100FF78A8(fade_sec);
        _90 = false;
    }
}

void Unk_710260f150::m8(const Unk_BgmControllerM8Arg& arg) {
    if (auto* bgm = sead::DynamicCast<Unk_71024fd6c8>(_8.sub_7100FF7C74(18)))
        bgm->sub_710100215C(arg);
}

void Unk_710260f150::sub_7100FFA610() {
    if (auto* bgm = sead::DynamicCast<Unk_71024fd808>(_8.sub_7100FF7C74(19)))
        bgm->sub_71010029B8();
    if (auto* bgm = sead::DynamicCast<Unk_71024fd948>(_8.sub_7100FF7C74(20)))
        bgm->sub_71010038AC();
}

void Unk_710260f150::sub_7100FFA72C() {
    if (auto* bgm = sead::DynamicCast<Unk_71024fd808>(_8.sub_7100FF7C74(19)))
        bgm->sub_71010029CC();
    if (auto* bgm = sead::DynamicCast<Unk_71024fd948>(_8.sub_7100FF7C74(20)))
        bgm->sub_71010038C0();
}

}  // namespace ksys::snd

// NON_MATCHING: placeholder destructor; the original (0x7100ffd044) also destroys members or bases
// this class does not declare yet.
Unk_71024fd0a8::~Unk_71024fd0a8() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100fff62c) also destroys members or bases
// this class does not declare yet.
Unk_71024fd188::~Unk_71024fd188() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100fffde4) also destroys members or bases
// this class does not declare yet.
Unk_71024fd318::~Unk_71024fd318() = default;

// NON_MATCHING: placeholder destructor; the original (0x710100094c) also destroys members or bases
// this class does not declare yet.
Unk_71024fd448::~Unk_71024fd448() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101002560) also destroys members or bases
// this class does not declare yet.
Unk_71024fd6c8::~Unk_71024fd6c8() = default;

// NON_MATCHING: placeholder destructor; the original (0x71010032f8) also destroys members or bases
// this class does not declare yet.
Unk_71024fd808::~Unk_71024fd808() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101003b40) also destroys members or bases
// this class does not declare yet.
Unk_71024fd948::~Unk_71024fd948() = default;
