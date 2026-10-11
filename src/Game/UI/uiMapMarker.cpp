#include "Game/UI/uiUnkSingletons.h"
#include "Game/gameMotorcycleMgr.h"
#include "Game/gameWolfLinkMgr.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// 0x71009504f8
void UiSubsys1Entry::m4() {
    _3c &= ~0x777f;
    m11();
    m13();
}

// 0x710095053c
void UiSubsys1Entry::m5() {
    m12();
    m13();
}

// 0x7100950570
void UiSubsys1Entry::m6() {
    m14();
    m15();
}

// 0x71009505a4
void UiSubsys1Entry::m7() {
    m16();
    m17();
}

// 0x71009505d8
void UiSubsys1Entry::m8() {
    m20();
    m21();
}

// 0x710095060c
void UiSubsys1Entry::m9() {
    if (!(_3c & 8))
        _3c &= ~0x7566;
    _3c &= ~8;
}

// 0x710095062c
s32 UiSubsys1Entry::m10() {
    if ((_3c & 0x800) || _1c == 42)
        return (_3c >> 9) & 1;
    return 3;
}

// 0x7100951388
void UiSubsys1Entry::sub_7100951388(bool enabled) {
    _3c |= 8;
    m25(enabled);
}

// NON_MATCHING: the base reset remains out-of-line and its TU default objects are not modeled.
Unk_71024754c0::~Unk_71024754c0() {
    _50 = nullptr;
    _58 = nullptr;
    _60 = 0;
}

void Unk_71024754c0::m4() {
    m31();
    _3c &= ~0x777f;
    m11();
    m13();
}

void Unk_71024754c0::m5() {
    m32();
    m12();
    m13();
}

void Unk_71024754c0::m9() {
    if (!(_3c & 8))
        _3c &= ~0x7566;
    _3c &= ~0x10008;
}

void Unk_71024754c0::m11() {
    if (!_58)
        return;
    _60 = _58->_1c;
    _3c = _60 > 0 ? _3c | 0x8000 : _3c & ~0x8000;
    m25((_3c & 0x8000) != 0);
    _3c = (_3c & 0x8000) ? _3c | 0x80 : _3c & ~0x80;
}

void Unk_71024754c0::m12() {
    _3c = (_3c & 0x8000) ? _3c | 0x80 : _3c & ~0x80;
}

void Unk_71024754c0::m30() {
    auto* entry = _58;
    if (entry && entry->_10 && *entry->_10)
        entry->_18 = ksys::gdt::Manager::instance()->getS32Handle(entry->_10);
}

void Unk_71024754c0::m31() {
    _3c &= ~0x10000;
    if (!_58)
        return;
    _60 = _58->_1c;
    _3c = _60 > 0 ? _3c | 0x8000 : _3c & ~0x8000;
    m25((_3c & 0x8000) != 0);
    _3c = (_3c & 0x8000) ? _3c | 0x80 : _3c & ~0x80;
}

void Unk_71024754c0::m32() {
    if (!_58 || !ksys::gdt::Manager::instance()->getParam().get().getBuffer0()->hasCopiedS32Flags())
        return;
    _60 = _58->_1c;
    _3c = ((_60 > 0) != ((_3c & 0x8000) != 0)) ? _3c | 0x10000 : _3c & ~0x10000;
    if (_3c & 0x10000)
        _3c = _60 > 0 ? _3c | 0x8000 : _3c & ~0x8000;
}

bool UiSubsys1Entry::sub_7100951048() const {
    return _24 == 0;
}

// NON_MATCHING: cleanup keeps an extra address register across the control call.
void UiSubsys1Entry::m22() {
    if (_8) {
        _8->_18 = nullptr;
        _8->sub_710098CF9C();
    }
    _8 = nullptr;
    _10 = nullptr;
    _18 = -1.0f;
}

// NON_MATCHING: inlined base cleanup keeps an extra address register.
void Unk_71024754c0::m22() {
    UiSubsys1Entry::m22();
    if (_50) {
        _50->_18 = nullptr;
        _50->sub_710098CF9C();
    }
    _50 = nullptr;
}

// NON_MATCHING: inherited resets remain out-of-line and their TU defaults are not modeled.
Unk_71024755d8::~Unk_71024755d8() {
    _68 = "";
    _78 = ksys::gdt::InvalidHandle;
    _7c = ksys::gdt::InvalidHandle;
    _80 = ksys::gdt::InvalidHandle;
    _84 = ksys::gdt::InvalidHandle;
}

void Unk_71024755d8::m9() {
    if (!(_3c & 8))
        _3c &= ~0x7566;
    _3c &= ~0x150008;
}

void Unk_71024755d8::m11() {
    Unk_71024754c0::m11();
}

void Unk_71024755d8::m12() {
    _3c = (_3c & 0x8000) ? _3c | 0x80 : _3c & ~0x80;
}

void Unk_71024755d8::m21() {
    if (_3c & 1)
        sub_710095156C((_3c & 0x20000) != 0);
}

void Unk_71024755d8::m31() {
    Unk_71024754c0::m31();
    _3c &= ~0x140000;
    if (_7c != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_7c) ? _3c | 0x20000 : _3c & ~0x20000;
    if (_80 != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_80) ? _3c | 0x80000 : _3c & ~0x80000;
    if (_84 != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_84) ? _3c | 0x200000 : _3c & ~0x200000;
}

// NON_MATCHING: changed-flag guards for bits 18/20 become selects and omit intermediate stores.
void Unk_71024755d8::m32() {
    Unk_71024754c0::m32();
    if (!ksys::gdt::Manager::instance()->getParam().get().getBuffer0()->hasCopiedBoolFlags())
        return;
    if (_7c != ksys::gdt::InvalidHandle) {
        bool value = ksys::gdt::getFlagGenericBool(_7c);
        _3c = (value != ((_3c & 0x20000) != 0)) ? _3c | 0x40000 : _3c & ~0x40000;
        if (_3c & 0x40000)
            _3c = value ? _3c | 0x20000 : _3c & ~0x20000;
    }
    if (_80 != ksys::gdt::InvalidHandle) {
        bool value = ksys::gdt::getFlagGenericBool(_80);
        _3c = (value != ((_3c & 0x80000) != 0)) ? _3c | 0x100000 : _3c & ~0x100000;
        if (_3c & 0x100000)
            _3c = value ? _3c | 0x80000 : _3c & ~0x80000;
    }
    if (_84 != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_84) ? _3c | 0x200000 : _3c & ~0x200000;
}

// NON_MATCHING: inherited resets remain out-of-line and their TU defaults are not modeled.
Unk_7102475808::~Unk_7102475808() {
    _64 = false;
    _68 = ksys::gdt::InvalidHandle;
}

void Unk_7102475808::m9() {
    if (!(_3c & 8))
        _3c &= ~0x7566;
    _3c &= ~0x50008;
}

void Unk_7102475808::m21() {
    if (_3c & 1)
        sub_710095156C(_64);
}

void Unk_7102475808::m31() {
    Unk_71024754c0::m31();
    _3c &= ~0x40000;
    if (u32(_44) < 15 && _68 != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_68) ? _3c | 0x20000 : _3c & ~0x20000;
}

// NON_MATCHING: the changed-flag guard becomes selects and omits the intermediate store.
void Unk_7102475808::m32() {
    Unk_71024754c0::m32();
    if (!ksys::gdt::Manager::instance()->getParam().get().getBuffer0()->hasCopiedBoolFlags())
        return;
    if (u32(_44) < 15 && _68 != ksys::gdt::InvalidHandle) {
        bool value = ksys::gdt::getFlagGenericBool(_68);
        _3c = (value != ((_3c & 0x20000) != 0)) ? _3c | 0x40000 : _3c & ~0x40000;
        if (_3c & 0x40000)
            _3c = value ? _3c | 0x20000 : _3c & ~0x20000;
    }
}

// NON_MATCHING: inherited entry destruction remains out of line.
Unk_7102475d70::~Unk_7102475d70() = default;

s32 Unk_7102475d70::m10() {
    return 2;
}

void Unk_7102475d70::m14() {
    sead::Vector3f position{0.0f, 0.0f, 0.0f};
    ksys::gdt::getFlag_Horse_Pos_For_Map(&position);
    updateDistrictFromPos(&position);
}

void Unk_7102475d70::m16() {
    sead::Vector3f position{0.0f, 0.0f, 0.0f};
    ksys::gdt::getFlag_Horse_Pos_For_Map(&position);
    updateDistrictFromPos(&position);
}

// NON_MATCHING: direct list search removes the nullable-find guard and changes argument setup.
void UiSubsys1Entry::sub_710095156C(bool enabled) {
    _3c = (enabled != ((_3c & 0x200) != 0)) ? _3c | 0x400 : _3c & ~0x400;
    _3c = enabled ? _3c | 0x200 : _3c & ~0x200;
    if (!(_3c & 0x400))
        return;
    auto& list = UiSubsys1::instance()->_2b0;
    for (auto& entry : list) {
        if (entry == this) {
            list.erase(&entry);
            break;
        }
    }
    if (!UiSubsys1::instance()->_2b0.isFull()) {
        if (auto* entry = UiSubsys1::instance()->_2b0.emplaceBack(nullptr))
            *entry = this;
    }
}

// NON_MATCHING: direct list search removes the nullable-find guard and changes argument setup.
void UiSubsys1Entry::m24(bool enabled) {
    m28(enabled);
    if ((_3c & 3) != 3)
        return;
    auto& list = UiSubsys1::instance()->_280;
    for (auto& entry : list) {
        if (entry == this) {
            list.erase(&entry);
            break;
        }
    }
    if (!UiSubsys1::instance()->_280.isFull()) {
        if (auto* entry = UiSubsys1::instance()->_280.emplaceBack(nullptr))
            *entry = this;
    }
}

// NON_MATCHING: direct list search removes the nullable-find guard and changes argument setup.
void UiSubsys1Entry::m27(bool enabled) {
    _3c = (enabled != ((_3c & 0x10) != 0)) ? _3c | 0x20 : _3c & ~0x20;
    _3c = enabled ? _3c | 0x10 : _3c & ~0x10;
    if ((_3c & 0x28) != 0x20)
        return;
    auto& list = UiSubsys1::instance()->_2b0;
    for (auto& entry : list) {
        if (entry == this) {
            list.erase(&entry);
            break;
        }
    }
    if (!UiSubsys1::instance()->_2b0.isFull()) {
        if (auto* entry = UiSubsys1::instance()->_2b0.emplaceBack(nullptr))
            *entry = this;
    }
}

// NON_MATCHING: direct list search removes the nullable-find guard and changes argument setup.
void UiSubsys1Entry::m28(bool enabled) {
    _3c = (enabled != ((_3c & 1) != 0)) ? _3c | 2 : _3c & ~2;
    _3c = enabled ? _3c | 1 : _3c & ~1;
    _3c |= (_3c & 2) << 13;
    if (!(_3c & 2))
        return;
    auto& list = UiSubsys1::instance()->_2b0;
    for (auto& entry : list) {
        if (entry == this) {
            list.erase(&entry);
            break;
        }
    }
    if (!UiSubsys1::instance()->_2b0.isFull()) {
        if (auto* entry = UiSubsys1::instance()->_2b0.emplaceBack(nullptr))
            *entry = this;
    }
}

// NON_MATCHING: inherited entry resets and their TU defaults remain out of line.
Unk_7102475c68::~Unk_7102475c68() {
    _50 = nullptr;
}

void Unk_7102475c68::m29() {
    auto* record = _50;
    if (record && record->_0 && *record->_0)
        record->_8 = ksys::gdt::Manager::instance()->getBoolHandle(record->_0);
}

void Unk_7102475c68::m11() {
    if (UiSubsys1::instance()->_848 == 0) {
        _3c &= ~0x80;
    } else if (_50 && _50->_8 != ksys::gdt::InvalidHandle) {
        _3c = ksys::gdt::getFlagGenericBool(_50->_8) ? _3c | 0x80 : _3c & ~0x80;
    }
}

void Unk_7102475c68::m12() {
    if (UiSubsys1::instance()->_848 == 0) {
        _3c &= ~0x80;
    } else if (_50 && _50->_8 != ksys::gdt::InvalidHandle) {
        _3c = ksys::gdt::getFlagGenericBool(_50->_8) ? _3c | 0x80 : _3c & ~0x80;
    }
}

void Unk_7102475c68::m17() {
    if (!(_3c & 0x10) && UiSubsys1::instance()->_848 == 0)
        m24(false);
    UiSubsys1Entry::m17();
}

void Unk_7102475c68::m26() {}

// NON_MATCHING: inherited entry destruction remains out of line.
Unk_7102476058::~Unk_7102476058() = default;

void Unk_7102476058::m11() {
    auto* manager = MotorcycleMgr::instance();
    auto* player = ksys::act::PlayerInfo::instance()->getPlayer_();
    if (!manager || !player || manager->checkIsActorRidingMotorcycle(player))
        m25(false);
    else
        m25(manager->x_0());
}

void Unk_7102476058::m12() {
    auto* manager = MotorcycleMgr::instance();
    auto* player = ksys::act::PlayerInfo::instance()->getPlayer_();
    if (!manager || !player || manager->checkIsActorRidingMotorcycle(player))
        m25(false);
    else
        m25(manager->x_0());
}

// NON_MATCHING: the flag test uses a word load instead of the native byte load.
void Unk_7102476058::m14() {
    if ((_3c & 0x10) && MotorcycleMgr::instance()) {
        sead::Vector3f position{0.0f, 0.0f, 0.0f};
        if (MotorcycleMgr::instance()->sub_710067B63C(&position))
            updateDistrictFromPos(&position);
    }
}

// NON_MATCHING: the flag test uses a word load instead of the native byte load.
void Unk_7102476058::m16() {
    if ((_3c & 0x10) && MotorcycleMgr::instance()) {
        sead::Vector3f position{0.0f, 0.0f, 0.0f};
        if (MotorcycleMgr::instance()->sub_710067B63C(&position))
            updateDistrictFromPos(&position);
    }
}

// NON_MATCHING: inherited entry destruction remains out of line.
Unk_7102475f60::~Unk_7102475f60() = default;

// NON_MATCHING: singleton and virtual-target loads are ordered differently.
void Unk_7102475f60::m11() {
    m25(WolfLinkMgr::instance() && WolfLinkMgr::instance()->_60 == 2);
}

// NON_MATCHING: singleton and virtual-target loads are ordered differently.
void Unk_7102475f60::m12() {
    m25(WolfLinkMgr::instance() && WolfLinkMgr::instance()->_60 == 2);
}

// NON_MATCHING: flag load width and virtual-target scheduling differ.
void Unk_7102475f60::m14() {
    if ((_3c & 0x10) && WolfLinkMgr::instance()) {
        auto position = WolfLinkMgr::instance()->sub_71006831BC();
        updateDistrictFromPos(&position);
    }
}

// NON_MATCHING: flag load width and virtual-target scheduling differ.
void Unk_7102475f60::m16() {
    if ((_3c & 0x10) && WolfLinkMgr::instance()) {
        auto position = WolfLinkMgr::instance()->sub_71006831BC();
        updateDistrictFromPos(&position);
    }
}

// NON_MATCHING: inherited entry reset defaults remain unmodeled.
Unk_7102476150::~Unk_7102476150() {
    _50 = nullptr;
    _58 = ksys::gdt::InvalidHandle;
}

void Unk_7102476150::m11() {
    if (_58 != ksys::gdt::InvalidHandle)
        m25(!ksys::gdt::getFlagGenericBool(_58));
    else if (_50)
        m25(true);
}

void Unk_7102476150::m21() {
    sub_710095156C(true);
}

}  // namespace uking::ui
