#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndMgr.h"

namespace ksys::snd {

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

void Unk_710260f130::sub_7100FFA1E0(bool value) {
    if (!_92)
        return;
    _91 = value;
    if (value)
        _8.sub_7100FF7BE0(Unk_7100FF7BE0{19});
    else
        _8.sub_7100FF7BE0(Unk_7100FF7BE0{20});
}

}  // namespace ksys::snd
