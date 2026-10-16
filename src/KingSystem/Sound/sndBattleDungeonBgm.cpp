#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include <random/seadGlobalRandom.h>

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

namespace {
const char* sRemainsBossBgmNames[] = {"RemainsWindBossBgm", "RemainsFireBossBgm", "RemainsElecBossBgm",
                                      "RemainsWaterBossBgm"};
}  // namespace

// NON_MATCHING: the original has one more (dead) reload of the spilled `type` after the store to mType.
Unk_71024fd448::Unk_71024fd448(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    auto* heap = arg.heap;
    ksys::snd::RemainsBossBgmType type;
    switch (arg.kind) {
    case ksys::snd::BgmKind::_27:
        type = ksys::snd::RemainsBossBgmType::Wind;
        break;
    case ksys::snd::BgmKind::_28:
        type = ksys::snd::RemainsBossBgmType::Elec;
        break;
    case ksys::snd::BgmKind::_29:
        type = ksys::snd::RemainsBossBgmType::Fire;
        break;
    case ksys::snd::BgmKind::_30:
        type = ksys::snd::RemainsBossBgmType::Water;
        break;
    default:
        return;
    }
    Unk_SpotBgmHandle::init(heap, sRemainsBossBgmNames[type], nullptr);
    mType = type;
}

Unk_71024fd448::~Unk_71024fd448() = default;

void Unk_71024fd448::m5() {
    if (_190)
        _1a0.calc();
}

bool Unk_71024fd448::m10() {
    return _190 != 0;
}

void Unk_71024fd448::m12(f32 fade_sec) {
    if (_190 == 4)
        _190 = 2;
    else if (_190 == 3)
        _190 = 1;
    else
        return;
    sub_710101D9D8();
}

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
    _34 = 0;
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

void Unk_71024fd948::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
}

void Unk_71024fd948::hm14() {
    _19c = 0;
    _1a0 = 0;
    _1b0 = 0;
    _1b4 = false;
}
