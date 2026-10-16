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

// NON_MATCHING: the original sets up the stack frame before the null check of the list (ours after it).
Unk_710260f2b8* sub_7100FFE204() {
    auto* list = SoundMgr::instance()->_30->_78;
    if (!list)
        return nullptr;
    return sead::DynamicCast<Unk_710260f2b8>(list->find("RemainsWindBattleBgm"));
}

// NON_MATCHING: the original sets up the stack frame before the null check of the list (ours after it).
Unk_71025ce390* sub_7100FFE39C() {
    auto* list = SoundMgr::instance()->_30->_78;
    if (!list)
        return nullptr;
    return sead::DynamicCast<Unk_71025ce390>(list->find("RemainsFireBattleBgm"));
}

Unk_7102500a00* sub_7100FFE7A4() {
    if (auto* controller = sub_7100FFD878()) {
        BgmKind kind = 41;
        const auto type = controller->_94;
        switch (type) {
        case Unk_710260f1f8::Kind::_0:
            kind = BgmKind::_22;
            break;
        case Unk_710260f1f8::Kind::_1:
            kind = BgmKind::_24;
            break;
        case Unk_710260f1f8::Kind::_2:
            kind = BgmKind::_23;
            break;
        case Unk_710260f1f8::Kind::_3:
            kind = BgmKind::_25;
            break;
        }
        if (int(kind) != 41) {
            auto* bgm_controller = SoundMgr::instance()->_30->_48;
            return sead::DynamicCast<Unk_7102500a00>(
                bgm_controller ? bgm_controller->_8.sub_7100FF7C74(kind) : nullptr);
        }
    }
    if (sub_7100FFDBD4()) {
        auto* bgm_controller = SoundMgr::instance()->_30->_48;
        return sead::DynamicCast<Unk_7102500a00>(
            bgm_controller ? bgm_controller->_8.sub_7100FF7C74(34) : nullptr);
    }
    return nullptr;
}

Unk_71024fec18* sub_7100FFE468() {
    auto* controller = SoundMgr::instance()->_30->_48;
    return sead::DynamicCast<Unk_71024fec18>(controller ? controller->_8.sub_7100FF7C74(32) : nullptr);
}

Unk_71024fed48* sub_7100FFE6EC() {
    auto* controller = SoundMgr::instance()->_30->_48;
    return sead::DynamicCast<Unk_71024fed48>(controller ? controller->_8.sub_7100FF7C74(31) : nullptr);
}

Unk_71024fee78* sub_7100FFEA3C() {
    auto* controller = SoundMgr::instance()->_30->_48;
    return sead::DynamicCast<Unk_71024fee78>(controller ? controller->_8.sub_7100FF7C74(26) : nullptr);
}

// inline-only in the original; name is a guess. The controller BGM lookup `SoundMgr::_30->_48 ? ->_8.sub_7100FF7C74(kind)
// : nullptr` is inlined in sub_7100FFDD38, sub_7100FFE094, sub_7100FFE7A4, sub_7100FFEA3C and sub_7100FFEBE0.
static Bgm* getControllerBgm(BgmKind kind) {
    auto* controller = SoundMgr::instance()->_30->_48;
    return controller ? controller->_8.sub_7100FF7C74(kind) : nullptr;
}

void sub_7100FFEBE0(const RemainsBossBgmType& type) {
    Bgm* bgm;
    switch (type) {
    case RemainsBossBgmType::Wind:
        bgm = getControllerBgm(BgmKind::_27);
        break;
    case RemainsBossBgmType::Fire:
        bgm = getControllerBgm(BgmKind::_29);
        break;
    case RemainsBossBgmType::Elec:
        bgm = getControllerBgm(BgmKind::_28);
        break;
    case RemainsBossBgmType::Water:
        bgm = getControllerBgm(BgmKind::_30);
        break;
    default:
        return;
    }
    if (auto* boss_bgm = sead::DynamicCast<Unk_71024fd448>(bgm))
        boss_bgm->sub_7101000514();
}

void sub_7100FFECB0(const RemainsBossBgmType& type) {
    Bgm* bgm;
    switch (type) {
    case RemainsBossBgmType::Wind:
        bgm = getControllerBgm(BgmKind::_27);
        break;
    case RemainsBossBgmType::Fire:
        bgm = getControllerBgm(BgmKind::_29);
        break;
    case RemainsBossBgmType::Elec:
        bgm = getControllerBgm(BgmKind::_28);
        break;
    case RemainsBossBgmType::Water:
        bgm = getControllerBgm(BgmKind::_30);
        break;
    default:
        return;
    }
    if (auto* boss_bgm = sead::DynamicCast<Unk_71024fd448>(bgm))
        boss_bgm->sub_71010007B4();
}

bool sub_7100FFED80() {
    auto* sound = SoundMgr::instance();
    if (!sound)
        return false;
    auto* bgm = sound->_30;
    if (!bgm)
        return false;
    auto* controller = bgm->_48;
    if (!controller)
        return false;
    return controller->_8._80;
}

bool sub_7100FFEDC8() {
    auto* sound = SoundMgr::instance();
    if (!sound)
        return false;
    auto* bgm = sound->_30;
    if (!bgm)
        return false;
    auto* controller = bgm->_48;
    if (!controller)
        return false;
    return controller->_8._81;
}

void sub_7100FFEE10() {}

Unk_710260ecf8::Unk_710260ecf8(const BgmInitArg& arg, const sead::SafeString& name)
    : NamedBgm(arg.handle_type) {
    Unk_SpotBgmHandle::init(arg.heap, name, nullptr);
}

// NON_MATCHING: the original stores the kind and handle type of the init arg as one 64-bit constant.
NamedBgm* bgmStuff(const sead::SafeString& name, sead::Heap* heap) {
    const BgmInitArg arg{BgmKind::_33, Unk_710260f248Type::_0, heap};
    NamedBgm* bgm;
    if (name == "RemainsWindBattleBgm")
        bgm = new (heap) Unk_710260f2b8(arg);
    else if (name == "RemainsElecBattleBgm")
        bgm = new (heap) Unk_710260f2c8(arg);
    else if (name == "RemainsFireBattleBgm")
        bgm = new (heap) Unk_71025ce390(arg);
    else if (name == "RemainsWaterBattleBgm")
        bgm = new (heap) Unk_710260f848(arg);
    else
        bgm = new (heap) Unk_710260ecf8(arg, name);

    if (bgm)
        bgm->sub_710101D970();
    return bgm;
}

void sub_7100FFF0E4(NamedBgm* bgm) {
    if (!bgm)
        return;
    bgm->sub_710101D9A4();
    delete bgm;
}

Unk_SoundMgr30_240* sub_7100FFF124() {
    return SoundMgr::instance()->_30->_240;
}

Unk_710260f218::Unk_710260f218() = default;

void Unk_710260f218::sub_7100FFC5C8(Bgm* bgm) {
    bgm->m8(_90);
}

void Unk_710260f218::m4(sead::Heap* heap) {
    _8.sub_7100FF75DC(2, heap);
    _8._30 = &_98;
    _8.sub_7100FF7920(19, heap);
    _8.sub_7100FF7920(21, heap);
}

void Unk_710260f218::m5() {
    if (_90)
        _8.sub_7100FF7698();
}

void Unk_710260f218::m6(f32 fade_sec) {
    if (!_90) {
        _8.sub_7100FF7830(fade_sec);
        _90 = true;
    }
}

void Unk_710260f218::m7(f32 fade_sec) {
    if (_90) {
        _8.sub_7100FF78A8(fade_sec);
        _90 = false;
    }
}

void Unk_710260f218::m10() {
    if (auto* bgm = sead::DynamicCast<Unk_710260f228>(_8.sub_7100FF7C74(21)))
        bgm->sub_7101026888();
}

void Unk_710260f218::sub_7100FFC758() {
    if (auto* bgm = sead::DynamicCast<Unk_710260f228>(_8.sub_7100FF7C74(21)))
        bgm->sub_71010267A8(Unk_71010267A8{0});
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

void Unk_710260f218::sub_7100FFC9D4() {
    if (auto* bgm = sead::DynamicCast<Unk_71024fd808>(_8.sub_7100FF7C74(19)))
        bgm->sub_71010029B8();
}

void Unk_710260f218::sub_7100FFCA70() {
    if (auto* bgm = sead::DynamicCast<Unk_71024fd808>(_8.sub_7100FF7C74(19)))
        bgm->sub_71010029CC();
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
        _8.sub_7100FF7BE0(BgmKind::_19);
    else
        _8.sub_7100FF7BE0(BgmKind::_20);
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

Unk_710260f160::Unk_710260f160() = default;

void Unk_710260f160::sub_7100FFAAB0(Bgm* bgm) {
    bgm->m8(_90);
    if (bgm->_c == BgmKind::_34)
        _d8 = sead::DynamicCast<::Unk_7102500a00>(bgm);
}

void Unk_710260f160::sub_7100FFAB58(Bgm* bgm) {
    if (bgm->_c == BgmKind::_34)
        _d8 = nullptr;
}

void Unk_710260f160::m4(sead::Heap* heap) {
    _8.sub_7100FF75DC(3, heap);
    _8._30 = &_98;
    _8._38 = &_b8;
    _8.sub_7100FF7920(34, heap);
    _8.sub_7100FF7920(35, heap);
    _91 = !SoundMgr::instance()->_c8->m9();
}

void Unk_710260f160::m5() {
    if (_91 && SoundMgr::instance()->_c8->m9() && _90 && _d8) {
        _d8->m6(0.5f);
        _91 = false;
    }
    if (_90)
        _8.sub_7100FF7698();
}

void Unk_710260f160::m6(f32 fade_sec) {
    if (!_90) {
        _8.sub_7100FF7830(fade_sec);
        if (_91 && _d8)
            _d8->m7(0.001f);
        _90 = true;
    }
}

void Unk_710260f160::m7(f32 fade_sec) {
    if (_90) {
        _8.sub_7100FF78A8(fade_sec);
        _90 = false;
    }
}

Unk_710260f1f8::Unk_710260f1f8(BgmControllerType type) {
    switch (type) {
    case BgmControllerType::_6:
        _94 = Kind::_0;
        break;
    case BgmControllerType::_7:
        _94 = Kind::_2;
        break;
    case BgmControllerType::_8:
        _94 = Kind::_1;
        break;
    case BgmControllerType::_9:
        _94 = Kind::_3;
        break;
    default:
        break;
    }
}

void Unk_710260f1f8::sub_7100FFC1C8(Bgm* bgm) {
    bgm->m8(_90);
}

void Unk_710260f1f8::m4(sead::Heap* heap) {
    _8.sub_7100FF75DC(3, heap);
    _8._30 = &_98;
    s32 kind;
    switch (_94) {
    case 0:
        kind = 22;
        break;
    case 1:
        kind = 24;
        break;
    case 2:
        kind = 23;
        break;
    case 3:
        kind = 25;
        break;
    default:
        kind = 0;
        break;
    }
    _8.sub_7100FF7920(kind, heap);
    _8.sub_7100FF7920(26, heap);
}

void Unk_710260f1f8::m5() {
    if (_90)
        _8.sub_7100FF7698();
}

void Unk_710260f1f8::m6(f32 fade_sec) {
    if (!_90) {
        _8.sub_7100FF7830(fade_sec);
        _90 = true;
    }
}

void Unk_710260f1f8::m7(f32 fade_sec) {
    if (_90) {
        _8.sub_7100FF78A8(fade_sec);
        _90 = false;
    }
}

void Unk_710260f1f8::m8(const Unk_BgmControllerM8Arg& arg) {
    if (auto* bgm = sead::DynamicCast<Unk_71024fee78>(_8.sub_7100FF7C74(26)))
        bgm->sub_710101157C(arg);
}

}  // namespace ksys::snd

ksys::snd::Unk_71024fca78* sub_7100FFD79C() {
    auto* sound = ksys::snd::SoundMgr::instance();
    if (!sound || !sound->_30)
        return nullptr;
    return sound->_30->_48;
}

Unk_71024fd448* sub_7100FFE520(const ksys::snd::RemainsBossBgmType* type) {
    ksys::snd::Bgm* bgm;
    switch (*type) {
    case ksys::snd::RemainsBossBgmType::Wind:
        bgm = ksys::snd::getControllerBgm(ksys::snd::BgmKind::_27);
        break;
    case ksys::snd::RemainsBossBgmType::Fire:
        bgm = ksys::snd::getControllerBgm(ksys::snd::BgmKind::_29);
        break;
    case ksys::snd::RemainsBossBgmType::Elec:
        bgm = ksys::snd::getControllerBgm(ksys::snd::BgmKind::_28);
        break;
    case ksys::snd::RemainsBossBgmType::Water:
        bgm = ksys::snd::getControllerBgm(ksys::snd::BgmKind::_30);
        break;
    default:
        return nullptr;
    }
    return sead::DynamicCast<Unk_71024fd448>(bgm);
}

Unk_7100ffe5ec* sub_7100FFE5EC() {
    for (auto it = ksys::snd::RemainsBossBgmType::begin(); it != ksys::snd::RemainsBossBgmType::end(); ++it) {
        const ksys::snd::RemainsBossBgmType type = *it;
        if (auto* bgm = sub_7100FFE520(&type))
            return bgm;
    }
    return nullptr;
}

Unk_71024fe970* sub_7100FFEB28() {
    return sead::DynamicCast<Unk_71024fe970>(ksys::snd::getControllerBgm(ksys::snd::BgmKind::_35));
}

void* sub_7100FFEAF4() {
    if (auto* controller = sub_7100FFD79C())
        return controller->m11();
    return nullptr;
}

Unk_71024fd010::~Unk_71024fd010() = default;

// NON_MATCHING: member store order around the vtable store.
Unk_71024fd0a8::Unk_71024fd0a8(const ksys::snd::BgmInitArg& arg) : Bgm(arg.kind) {
    mAppearanceFlag = ksys::gdt::Manager::instance()->getBoolHandle("AnimalMaster_Appearance");
    init(arg);
}

Unk_71024fd0a8::~Unk_71024fd0a8() {
    _10->sub_710101D9A4();
    if (_10)
        delete _10;
    _10 = nullptr;
    _18->sub_710101D9A4();
    if (_18)
        delete _18;
    _18 = nullptr;
}

void Unk_71024fd0a8::m12(f32 fade_sec) {
    _10->sub_7101020BB0(fade_sec);
    _18->sub_7101020BB0(fade_sec);
}

void Unk_71024fd0a8::m13(f32 fade_sec) {
    auto* first = _10;
    first->sub_710101D9F4(fade_sec);
    first->_180 = 0;
    auto* second = _18;
    second->sub_710101D9F4(fade_sec);
    second->_180 = 0;
}

namespace {
sead::SafeString sStr_BigMazeBgm = "BigMazeBgm";
sead::SafeString sStr_maze = "maze";
}  // namespace

Unk_71024fd188::Unk_71024fd188(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, sStr_BigMazeBgm, nullptr);
    mInfo = static_cast<ksys::snd::BigMazeBgmInfo*>(
        ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::BigMazeBgm));
}

Unk_71024fd188::~Unk_71024fd188() = default;

void Unk_71024fd188::hm14() {
    mEntry = sub_71010209FC(sStr_maze);
    if (mEntry && mEntry->sub_7100FF6DF4(this))
        _1a0.moveTo(1.0, *mInfo->mFadeInSec);
}

void Unk_71024fd188::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    _198 = 0;
    _19c = 0;
}

// 0x710260f33c: debug flag (never written); 0x710260f338: debug flag that forces "in the big maze" (never
// written).
KSYS_VISIBILITY_HIDDEN bool sUnk_710260F33C;
KSYS_VISIBILITY_HIDDEN bool sUnk_710260F338;
// 0x71024fd180: the debug text position.
KSYS_VISIBILITY_HIDDEN sead::Vector2f sUnk_71024FD180{920.0f, 80.0f};

void Unk_71024fd188::m14(sead::TextWriter& writer) {
    if (!sUnk_710260F33C)
        return;
    writer.setCursorFromTopLeft(sUnk_71024FD180);
    writer.printf("---- 巨大迷路BGM ----\n");
    writer.printf("処理            :%s\n", mActive ? "有効" : "無効");
    bool in_maze = sUnk_710260F338;
    if (!in_maze) {
        auto* wm = ksys::world::Manager::instance();
        ksys::world::EnvMgr* env_mgr;
        in_maze = wm && (env_mgr = wm->getEnvMgr()) && env_mgr->getPaletteSet() == 11;
    }
    writer.printf("巨大迷路内?     :%s\n", in_maze ? "Yes" : "No");
    writer.printf("状態            :%s\n", State::text(_198) ? State::text(_198) : "不明");
    writer.printf("再生待ちカウント:%.2f\n", _19c);
    writer.printf("フェード音量    :%.2f\n", _1a0.getValue());
}

Unk_71024fd3a0::~Unk_71024fd3a0() = default;

void Unk_71024fd318::sub_7100FFFCF0(const ksys::snd::BgmInitArg& arg) {
    sead::Heap* heap = arg.heap;
    _10 = new (heap, 8) Unk_71024fd3a0(arg.handle_type);
    if (_10) {
        _10->sub_7101022DEC(heap, "OmenOfBloodyMoonBgm", "Omen");
        _10->sub_710101D970();
    }
}

Unk_71024fd318::~Unk_71024fd318() {
    if (_10) {
        _10->sub_710101D9A4();
        if (_10)
            delete _10;
    }
}

bool Unk_71024fd318::m9() {
    if (!_10)
        return true;
    return _10->mEntries.size() == 0;
}

void Unk_71024fd318::m12(f32 fade_sec) {
    if (_10)
        _10->sub_7101020BB0(fade_sec);
}

void Unk_71024fd318::m13(f32 fade_sec) {
    if (_10)
        _10->sub_710101D9F4(fade_sec);
    _1c = 0;
    ksys::snd::SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(
        ksys::snd::DuckingMgr::DuckerType::cBloody, false);
}
