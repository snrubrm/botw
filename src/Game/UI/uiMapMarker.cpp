#include "Game/UI/uiUnkSingletons.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "Game/UI/uiManager.h"
#include "Game/Actor/actGuardian.h"
#include "KingSystem/Quest/qstIndicator.h"
#include "Game/gameMotorcycleMgr.h"
#include "Game/gameHorseMgr.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/euiMessageString.h"
#include "Game/gameWolfLinkMgr.h"
#include "Game/gameSceneSubsys13.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ui {

KSYS_VISIBILITY_HIDDEN extern bool sUnk_71025d6a98;

// Written by the native marker initializer at 0x94F9E4.
static sead::Vector3f sUnk_71025d6cf4{0.2f, 0.0f, -0.2f};
static sead::Vector3f sUnk_71025d6d00{2.0f, 0.0f, -2.0f};

static sead::Vector2f sUnk_71025d6a88{-100000.0f, 0.0f};
static sead::Vector3f sUnk_71025d6d0c{-100000.0f, 0.0f, 0.0f};


// NON_MATCHING: the original reaches sUnk_71025d6d0c through the TU's merged static block at 0x71025d6c70
// (+0x9c); the statics before it (0x25d6c70..0x25d6cf4) are not defined yet, so our offset differs.
UiSubsys1Entry::~UiSubsys1Entry() {
    _8 = nullptr;
    _10 = nullptr;
    _18 = -1.0f;
    _1c = 45;
    _20 = 25;
    _24 = 33;
    _28.set(sUnk_71025d6d0c);
    _34.set(sUnk_71025d6a88);
    _3c = 0;
    _40 = -1;
    _44 = -1;
    _48 = nullptr;
}

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

// NON_MATCHING: virtual-target loading and boolean-setup branches differ.
void UiSubsys1Entry::m19() {
    m24(UiSubsys1::instance()->_6d4 <= _28.x && _28.x <= UiSubsys1::instance()->_6dc &&
        UiSubsys1::instance()->_6d8 <= _28.z && _28.z <= UiSubsys1::instance()->_6e0);
}

// 0x7100951388
void UiSubsys1Entry::sub_7100951388(bool enabled) {
    _3c |= 8;
    m25(enabled);
}

// NON_MATCHING: base vector reset uses component copies instead of the native paired loads/stores.
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

// 0x7101e7ce54: two display values per marker type (46 types; the default type is 45)
struct MarkerTypeInfo {
    s32 _0;
    s32 _4;
};
static const MarkerTypeInfo sUnk_7101e7ce54[46] = {
    {0, 0},   {1, 1},   {2, 2},   {3, 3},   {4, 4},   {5, 5},   {6, 6},   {7, 7},   {7, 8},   {7, 9},
    {7, 10},  {8, 11},  {8, 12},  {8, 13},  {8, 14},  {8, 15},  {9, 16},  {11, 18}, {12, 19}, {13, 20},
    {14, 21}, {15, 22}, {16, 23}, {17, 24}, {18, 25}, {19, 26}, {20, 27}, {21, 28}, {21, 28}, {21, 28},
    {21, 28}, {21, 28}, {21, 28}, {21, 28}, {21, 28}, {21, 28}, {21, 28}, {22, 29}, {22, 29}, {22, 29},
    {22, 29}, {22, 29}, {23, 30}, {10, 17}, {24, 31}, {25, 33},
};

// inline-only in the original; name is a guess: the m29 of Unk_71024754c0 / Unk_71024755d8 / Unk_7102475808
// (0x710095192c / 0x7100951ff8 / 0x71009535a0) each clamp the type and index the table twice
static const MarkerTypeInfo& getMarkerTypeInfo(s32 type) {
    return sUnk_7101e7ce54[sead::Mathi::clamp(type, 0, 45)];
}

// 0x710095192c
// NON_MATCHING: the original stores the type to the stack and reloads it before the compare with _1c.
void Unk_71024754c0::m29(Unk_710095192c* entry) {
    const s32 type = entry->_48;
    if (type != _1c) {
        _3c |= 0x4000;
        _1c = type;
    }
    _20 = getMarkerTypeInfo(entry->_48)._0;
    _24 = getMarkerTypeInfo(entry->_48)._4;
    updateDistrictFromPos(&entry->_38);
    _3c = entry->_8 ? _3c | 0x800 : _3c & ~0x800;
    _58 = entry;
}

// 0x7100951e0c
void Unk_71024754c0::m26() {
    if (!_58 || !_58->_8)
        return;
    eui::MessageString message;
    if (getLocationMarker(_58->_8, &message) != 0)
        return;
    sead::FixedSafeString<64> name;
    sub_71010BA648(&name, message);
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

// 0x7100951058
// NON_MATCHING: the original selects the out-of-range result with a csel; ours branches
bool UiSubsys1Entry::sub_7100951058() const {
    switch (_24) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
        return true;
    default:
        return false;
    }
}

// 0x7100951074
bool UiSubsys1Entry::sub_7100951074() const {
    return u32(_24) < 18;
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

// NON_MATCHING: static block offset of sUnk_71025d6d0c only (see UiSubsys1Entry::~UiSubsys1Entry).
Unk_71024755d8::~Unk_71024755d8() {
    _68 = sead::SafeString();
    _78 = ksys::gdt::InvalidHandle;
    _7c = ksys::gdt::InvalidHandle;
    _80 = ksys::gdt::InvalidHandle;
    _84 = ksys::gdt::InvalidHandle;
}

// 0x7100951ff8
// NON_MATCHING: as Unk_71024754c0::m29 (the type is spilled to the stack in the original).
void Unk_71024755d8::m29(Unk_710095192c* entry) {
    Unk_71024754c0::m29(entry);
    sub_71009520D4();
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

// 0x71009529ec (placeholder name): whether the area's dungeon has been entered
bool Unk_71024755d8::isDungeonEntered() const {
    return ksys::gdt::isDungeonEntered(_68);
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

}  // namespace uking::ui

// 0x71009529f8
// NON_MATCHING: static block offset of sUnk_71025d6d0c only (see UiSubsys1Entry::~UiSubsys1Entry).
Unk_71024756f0::~Unk_71024756f0() {
    _68 = sead::SafeString();
    _78 = ksys::gdt::InvalidHandle;
    _7c = ksys::gdt::InvalidHandle;
    _80 = ksys::gdt::InvalidHandle;
    _84 = ksys::gdt::InvalidHandle;
}

// 0x7100952b24
// NON_MATCHING: as Unk_71024754c0::m29 (the type is spilled to the stack in the original).
void Unk_71024756f0::m29(uking::ui::Unk_710095192c* entry) {
    Unk_71024754c0::m29(entry);
    sub_7100952C00();
}

void Unk_71024756f0::m9() {
    if (!(_3c & 8))
        _3c &= ~0x7566;
    _3c &= ~0x150008;
}

void Unk_71024756f0::m11() {
    Unk_71024754c0::m11();
}

void Unk_71024756f0::m31() {
    Unk_71024754c0::m31();
    _3c &= ~0x140000;
    if (_7c != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_7c) ? _3c | 0x20000 : _3c & ~0x20000;
    if (_80 != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_80) ? _3c | 0x80000 : _3c & ~0x80000;
    if (_84 != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_84) ? _3c | 0x200000 : _3c & ~0x200000;
}

void Unk_71024756f0::m12() {
    _3c = (_3c & 0x8000) ? _3c | 0x80 : _3c & ~0x80;
}

// NON_MATCHING: as Unk_71024755d8::m32 (the changed-flag guards become selects).
void Unk_71024756f0::m32() {
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

void Unk_71024756f0::m21() {
    if (_3c & 1)
        sub_710095156C((_3c & 0x20000) != 0);
}

// 0x7100953518 (placeholder name): whether the area's dungeon has been entered
bool Unk_71024756f0::isDungeonEntered() const {
    return ksys::gdt::isDungeonEntered(_68);
}

// 0x710095394c
// NON_MATCHING: static block offset of sUnk_71025d6d0c only (see UiSubsys1Entry::~UiSubsys1Entry).
Unk_7102475920::~Unk_7102475920() {
    _68 = sead::SafeString();
    _78 = ksys::gdt::InvalidHandle;
}

// 0x7100953a74
// NON_MATCHING: as Unk_71024754c0::m29 (the type is spilled to the stack in the original).
void Unk_7102475920::m29(uking::ui::Unk_710095192c* entry) {
    Unk_71024754c0::m29(entry);
    sub_7100953B50();
}

void Unk_7102475920::m9() {
    if (!(_3c & 8))
        _3c &= ~0x7566;
    _3c &= ~0x50008;
}

void Unk_7102475920::m31() {
    Unk_71024754c0::m31();
    _3c &= ~0x40000;
    if (_78 != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_78) ? _3c | 0x20000 : _3c & ~0x20000;
}

// NON_MATCHING: as Unk_71024755d8::m32 (the changed-flag guard becomes a select).
void Unk_7102475920::m32() {
    Unk_71024754c0::m32();
    if (!ksys::gdt::Manager::instance()->getParam().get().getBuffer0()->hasCopiedBoolFlags())
        return;
    if (_78 != ksys::gdt::InvalidHandle) {
        bool value = ksys::gdt::getFlagGenericBool(_78);
        _3c = (value != ((_3c & 0x20000) != 0)) ? _3c | 0x40000 : _3c & ~0x40000;
        if (_3c & 0x40000)
            _3c = value ? _3c | 0x20000 : _3c & ~0x20000;
    }
}

void Unk_7102475920::m21() {
    if (_3c & 1)
        sub_710095156C((_3c & 0x20000) != 0);
}

// 0x71009540e4
// NON_MATCHING: static block offset of sUnk_71025d6d0c only (see UiSubsys1Entry::~UiSubsys1Entry).
Unk_7102475a38::~Unk_7102475a38() {
    if (_68.hasProc())
        _68.reset();
    _78 = sead::SafeString();
    _88 = ksys::gdt::InvalidHandle;
    _8c = ksys::gdt::InvalidHandle;
    _90 = false;
    _91 = true;
}

void Unk_7102475a38::m9() {
    if (!(_3c & 8))
        _3c &= ~0x7566;
    _3c &= ~0x150008;
}

// NON_MATCHING: the original branches on _90 once before the m25 call and keeps both results apart
void Unk_7102475a38::m11() {
    Unk_71024754c0::m11();
    if (_3c & 0x10) {
        m25(((_3c & 0x80000) != 0) ^ !_90);
        _3c = (((_3c & 0x80000) != 0) ^ !_90) ? _3c | 0x80 : _3c & ~0x80;
    }
}

void Unk_7102475a38::m31() {
    Unk_71024754c0::m31();
    _3c &= ~0x140000;
    if (_88 != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_88) ? _3c | 0x20000 : _3c & ~0x20000;
    if (_8c != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_8c) ? _3c | 0x80000 : _3c & ~0x80000;
}

// NON_MATCHING: scheduling of the `_90 == 0` compare
void Unk_7102475a38::m12() {
    Unk_71024754c0::m12();
    if (_3c & 0x80)
        _3c = (((_3c & 0x80000) != 0) ^ !_90) ? _3c | 0x80 : _3c & ~0x80;
}

// NON_MATCHING: as Unk_71024755d8::m32 (the changed-flag guards become selects).
void Unk_7102475a38::m32() {
    Unk_71024754c0::m32();
    if (!ksys::gdt::Manager::instance()->getParam().get().getBuffer0()->hasCopiedBoolFlags())
        return;
    if (_88 != ksys::gdt::InvalidHandle) {
        bool value = ksys::gdt::getFlagGenericBool(_88);
        _3c = (value != ((_3c & 0x20000) != 0)) ? _3c | 0x40000 : _3c & ~0x40000;
        if (_3c & 0x40000)
            _3c = value ? _3c | 0x20000 : _3c & ~0x20000;
    }
    if (_8c != ksys::gdt::InvalidHandle) {
        bool value = ksys::gdt::getFlagGenericBool(_8c);
        _3c = (value != ((_3c & 0x80000) != 0)) ? _3c | 0x100000 : _3c & ~0x100000;
        if (_3c & 0x100000)
            _3c = value ? _3c | 0x80000 : _3c & ~0x80000;
    }
}

void Unk_7102475a38::m21() {
    if (_3c & 1)
        sub_710095156C((_3c & 0x20000) != 0);
}

// 0x71009550f8
// NON_MATCHING: static block offset of sUnk_71025d6d0c only (see UiSubsys1Entry::~UiSubsys1Entry).
Unk_7102475b50::~Unk_7102475b50() {
    _68 = sead::SafeString();
    _78 = ksys::gdt::InvalidHandle;
}

// 0x7100955220
// NON_MATCHING: as Unk_71024754c0::m29 (the type is spilled to the stack in the original).
void Unk_7102475b50::m29(uking::ui::Unk_710095192c* entry) {
    Unk_71024754c0::m29(entry);
    sub_71009552FC();
}

void Unk_7102475b50::m9() {
    if (!(_3c & 8))
        _3c &= ~0x7566;
    _3c &= ~0x50008;
}

void Unk_7102475b50::m31() {
    Unk_71024754c0::m31();
    _3c &= ~0x40000;
    if (_78 != ksys::gdt::InvalidHandle)
        _3c = ksys::gdt::getFlagGenericBool(_78) ? _3c | 0x20000 : _3c & ~0x20000;
}

// NON_MATCHING: as Unk_71024755d8::m32 (the changed-flag guard becomes a select).
void Unk_7102475b50::m32() {
    Unk_71024754c0::m32();
    if (!ksys::gdt::Manager::instance()->getParam().get().getBuffer0()->hasCopiedBoolFlags())
        return;
    if (_78 != ksys::gdt::InvalidHandle) {
        bool value = ksys::gdt::getFlagGenericBool(_78);
        _3c = (value != ((_3c & 0x20000) != 0)) ? _3c | 0x40000 : _3c & ~0x40000;
        if (_3c & 0x40000)
            _3c = value ? _3c | 0x20000 : _3c & ~0x20000;
    }
}

void Unk_7102475b50::m21() {
    if (_3c & 1)
        sub_710095156C((_3c & 0x20000) != 0);
}

namespace uking::ui {

// NON_MATCHING: static block offset of sUnk_71025d6d0c only (see UiSubsys1Entry::~UiSubsys1Entry).
Unk_7102475808::~Unk_7102475808() {
    _64 = false;
    _68 = ksys::gdt::InvalidHandle;
}

// 0x71025d6f08 (in the TU's merged static block at 0x71025d6c70)
static sead::SafeString sUnk_71025d6f08 = "MapTower_";

// 0x7100953684
// NON_MATCHING: the original reaches sUnk_71025d6f08 through the TU's merged static block (+0x298).
void Unk_7102475808::m30() {
    Unk_71024754c0::m30();
    sead::FormatFixedSafeString<64> name("%s%02d", sUnk_71025d6f08.cstr(), _44 + 1);
    _68 = ksys::gdt::Manager::instance()->getBoolHandle(name);
}

// 0x71009535a0
// NON_MATCHING: as Unk_71024754c0::m29 (the type is spilled to the stack in the original).
void Unk_7102475808::m29(Unk_710095192c* entry) {
    Unk_71024754c0::m29(entry);
    m30();
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

Unk_7102475d70::~Unk_7102475d70() = default;

s32 Unk_7102475d70::m10() {
    return 2;
}

void Unk_7102475d70::m11() {
    if (auto* player = uking::act::PlayerInfo::instance()->getPlayer())
        _50 = player->isRidingHorse();
    m25(!_50 && ksys::gdt::getFlag_Horse_ActiveIndex(false) != -1);
}

void Unk_7102475d70::m12() {
    bool riding = false;
    if (auto* player = uking::act::PlayerInfo::instance()->getPlayer_()) {
        if (auto* ride = player->getPlayerRideInfo()) {
            if ((ride->_30 & 3) == 3 && ride->_18.hasProc()) {
                if (auto* manager = HorseMgr::instance())
                    riding = manager->sub_7100E85334(ride->_18);
            }
        }
    }
    if (riding != _50) {
        m25(!riding && ksys::gdt::getFlag_Horse_ActiveIndex(false) != -1);
    } else if (!riding) {
        const bool active = ksys::gdt::getFlag_Horse_ActiveIndex(false) != -1;
        if (active != ((_3c & 0x10) != 0))
            m25(active);
    }
    _50 = riding;
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

// 0x7100955f2c
// NON_MATCHING: block layout of the owned-horse branch (the original falls through to its m24(true) call).
void Unk_7102475d70::m18() {
    bool owned_horse_ok = false;
    if (auto* manager = HorseMgr::instance(); manager && manager->mOwnedHorse.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&manager->mOwnedHorse, &accessor);
        owned_horse_ok = act::sub_7100E6ED04(accessor);
    }
    if (owned_horse_ok) {
        m24(true);
        return;
    }
    auto* screen = sead::DynamicCast<ScreenAppMap>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppMap));
    if (screen && screen->sub_71009F1A64(&_28))
        m24(true);
    else
        m24(false);
}

}  // namespace uking::ui

// 0x7100956070
void Unk_7102475e68::m11() {
    m25(_50);
}

// 0x7100956080
void Unk_7102475e68::m12() {
    m25(_50);
}

// 0x7100956090
void Unk_7102475e68::m14() {
    if (!(_3c & 0x10))
        return;
    if (_58 == 1)
        updateDistrictFromPos(&_70);
    else if (_54 == 0)
        updateDistrictFromPos(&_64);
}

// 0x71009560d0
void Unk_7102475e68::m16() {
    if (!uking::ui::Manager::instance()->isPausedMaybe())
        _7c = 0;
    if (_3c & 0x10) {
        if (_58 == 1) {
            updateDistrictFromPos(&_70);
            _7c = _60;
        } else if (_54 == 0) {
            updateDistrictFromPos(&_64);
            _7c = _5c;
        }
    }
    _54 = 2;
    _58 = 2;
}

namespace uking::ui {

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

Unk_7102476058::~Unk_7102476058() = default;

void Unk_7102476058::m11() {
    auto* manager = MotorcycleMgr::instance();
    auto* player = uking::act::PlayerInfo::instance()->getPlayer_();
    if (!manager || !player || manager->checkIsActorRidingMotorcycle(player))
        m25(false);
    else
        m25(manager->x_0());
}

void Unk_7102476058::m12() {
    auto* manager = MotorcycleMgr::instance();
    auto* player = uking::act::PlayerInfo::instance()->getPlayer_();
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

void Unk_7102476150::m12() {
    if (!ksys::gdt::Manager::instance()->getParam().get().getBuffer0()->hasCopiedBoolFlags() ||
        _58 == ksys::gdt::InvalidHandle)
        return;
    bool visible = !ksys::gdt::getFlagGenericBool(_58);
    if (visible != ((_3c & 0x10) != 0))
        m25(visible);
}

// NON_MATCHING: vector addition uses one selected pointer and paired loads instead of component selections.
void Unk_7102476150::m14() {
    if (_50) {
        auto position = _50->getPosition();
        if (_50->kind == 1)
            position += _50->is_remains ? sUnk_71025d6d00 : sUnk_71025d6cf4;
        updateDistrictFromPos(&position);
    }
}

// NON_MATCHING: vector addition uses one selected pointer and paired loads instead of component selections.
void Unk_7102476150::m16() {
    if (_50) {
        auto position = _50->getPosition();
        if (_50->kind == 1)
            position += _50->is_remains ? sUnk_71025d6d00 : sUnk_71025d6cf4;
        updateDistrictFromPos(&position);
    }
}

void Unk_7102476150::m29() {
    if (_50 && _50->off_flag && *_50->off_flag)
        _58 = ksys::gdt::Manager::instance()->getBoolHandle(_50->off_flag);
}

// NON_MATCHING: direct search removes nullable-find guards and merges the two native insertion paths.
void UiSubsys1Entry::m25(bool enabled) {
    m27(enabled);
    if ((_3c & 0x30) == 0x30) {
        auto& list = UiSubsys1::instance()->_250;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                break;
            }
        }
        if (!UiSubsys1::instance()->_250.isFull()) {
            if (auto* entry = UiSubsys1::instance()->_250.emplaceBack(nullptr))
                *entry = this;
        }
    } else if ((_3c & 0x31) == 0x20) {
        auto& list = UiSubsys1::instance()->_250;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                break;
            }
        }
    }
}

void Unk_7102476250::m11() {
    bool visible = false;
    if (_50 != ksys::gdt::InvalidHandle && _40 != -1) {
        if (_54 == ksys::gdt::FlagType::Bool)
            visible = ksys::gdt::getFlagGenericBool(_50);
        else if (_54 == ksys::gdt::FlagType::S32)
            visible = ksys::gdt::getFlagGenericS32(_50) > 0;
    }
    if (_58 != ksys::gdt::InvalidHandle && _40 != -1) {
        if (_5c == ksys::gdt::FlagType::Bool)
            visible &= !ksys::gdt::getFlagGenericBool(_58);
        else if (_5c == ksys::gdt::FlagType::S32)
            visible &= ksys::gdt::getFlagGenericS32(_58) <= 0;
    }
    m25(visible);
}

void Unk_7102476250::m12() {
    const auto* param = ksys::gdt::Manager::instance()->getParam().get().getBuffer0();
    if (!param->hasCopiedBoolFlags() && !param->hasCopiedS32Flags())
        return;
    bool visible = false;
    if (_50 != ksys::gdt::InvalidHandle && _40 != -1) {
        if (_54 == ksys::gdt::FlagType::Bool)
            visible = ksys::gdt::getFlagGenericBool(_50);
        else if (_54 == ksys::gdt::FlagType::S32)
            visible = ksys::gdt::getFlagGenericS32(_50) > 0;
    }
    if (_58 != ksys::gdt::InvalidHandle && _40 != -1) {
        if (_5c == ksys::gdt::FlagType::Bool)
            visible &= !ksys::gdt::getFlagGenericBool(_58);
        else if (_5c == ksys::gdt::FlagType::S32)
            visible &= ksys::gdt::getFlagGenericS32(_58) <= 0;
    }
    m25(visible);
}

// NON_MATCHING: SafeString setup is reordered and handle-prefix combination is duplicated across type branches.
void Unk_7102476250::m29() {
    if (_40 < 0)
        return;
    const char* key = nullptr;
    ksys::gdt::getFlag_MapApp_PointGuideVisibleKey(&key, _40);
    if (key && *key) {
        _54 = ksys::gdt::Manager::instance()->getParam().get1().getBuffer()->getFlagType(key);
        if (_54 == ksys::gdt::FlagType::Bool)
            _50 = ksys::gdt::Manager::instance()->getBoolHandle(key);
        else if (_54 == ksys::gdt::FlagType::S32)
            _50 = ksys::gdt::Manager::instance()->getS32Handle(key);
        else
            _50 = ksys::gdt::InvalidHandle;
    }
    key = nullptr;
    ksys::gdt::getFlag_MapApp_PointGuideInvisibleKey(&key, _40);
    if (key && *key) {
        _5c = ksys::gdt::Manager::instance()->getParam().get1().getBuffer()->getFlagType(key);
        if (_5c == ksys::gdt::FlagType::Bool)
            _58 = ksys::gdt::Manager::instance()->getBoolHandle(key);
        else if (_5c == ksys::gdt::FlagType::S32)
            _58 = ksys::gdt::Manager::instance()->getS32Handle(key);
        else
            _58 = ksys::gdt::InvalidHandle;
    }
}

Unk_7102476250::~Unk_7102476250() = default;

// 0x7100956fd4
void Unk_7102476350::m26() {
    if (!_50 || !_50->_10)
        return;
    eui::MessageString message;
    if (getLocationMarker(_50->_10, &message) != 0)
        return;
    sead::FixedSafeString<64> name;
    sub_71010BA648(&name, message);
}

void Unk_7102476350::m29() {
    auto* record = _58;
    if (record && record->_28 && *record->_28)
        record->_30 = ksys::gdt::Manager::instance()->getS32Handle(record->_28);
}

bool UiSubsys1::sub_7100956C10(u32 index) const {
    return index == 0xff || (_120 & (1u << index));
}

// NON_MATCHING: the bool branch precedes native virtual-target loads.
void Unk_7102476350::m11() {
    if ((_44 == 0xff || (UiSubsys1::instance()->_120 & (1u << _44))) && sub_7100956C34())
        m25(true);
    else
        m25(false);
}

// NON_MATCHING: the bool branch precedes native virtual-target loads.
void Unk_7102476350::m12() {
    if ((_44 == 0xff || (UiSubsys1::instance()->_120 & (1u << _44))) && sub_7100956C34())
        m25(true);
    else
        m25(false);
}

void Unk_7102476350::m17() {
    if (!(_3c & 0x10) && UiSubsys1::instance()->_848 == 0)
        m24(false);
    UiSubsys1Entry::m17();
}

// NON_MATCHING: static block offset of sUnk_71025d6d0c only (see UiSubsys1Entry::~UiSubsys1Entry).
Unk_7102476350::~Unk_7102476350() {
    _50 = nullptr;
    _58 = nullptr;
}



void Unk_7102476450::m11() {
    if (GameSceneSubsys13::instance()->_38 > _40) {
        m25(true);
        updateDistrictFromPos(&GameSceneSubsys13::instance()->_28);
    } else {
        m25(false);
    }
}

void Unk_7102476450::m12() {
    if (GameSceneSubsys13::instance()->_38 > _40) {
        m25(true);
        updateDistrictFromPos(&GameSceneSubsys13::instance()->_28);
    } else {
        m25(false);
    }
}

Unk_7102476450::~Unk_7102476450() = default;


void Unk_7102476548::m4() {
    _3c &= ~0x777f;
    m11();
    m14();
}

void Unk_7102476548::m5() {
    UiSubsys1Entry::m13();
    m16();
}

void Unk_7102476548::m7() {
    UiSubsys1Entry::m17();
}

void Unk_7102476548::m11() {
    m25(true);
}

void Unk_7102476548::m21() {
    sub_710095156C(true);
}

// NON_MATCHING: static block offset of sUnk_71025d6d0c only (see UiSubsys1Entry::~UiSubsys1Entry).
Unk_7102476548::~Unk_7102476548() {
    _50 = -1;
    _54 = -1;
}

void Unk_7102476640::m4() {
    _3c &= ~0x777f;
    m11();
    m14();
    _80 = 0;
    _84 = 0;
}

void Unk_7102476640::m5() {
    m12();
    UiSubsys1Entry::m13();
}

void Unk_7102476640::m6() {
    m15();
}

void Unk_7102476640::m7() {
    m16();
    m17();
}

Unk_7102476640** UiSubsys1::sub_71009580A4(Unk_7102476640* key) {
    if (!key)
        return nullptr;
    for (auto& entry : _5d8) {
        if (entry == key)
            return &entry;
    }
    return nullptr;
}

bool UiSubsys1::sub_71009580E4(Unk_7102476640** entry) {
    if (!entry)
        return false;
    _5d8.erase(entry);
    return true;
}

// 0x7100958fcc
UiSubsys1Entry** UiSubsys1::sub_7100958FCC(UiSubsys1Entry* key) {
    if (!key)
        return nullptr;
    for (auto& entry : _620) {
        if (entry == key)
            return &entry;
    }
    return nullptr;
}

// 0x710095900c
bool UiSubsys1::sub_710095900C(UiSubsys1Entry** entry) {
    if (!entry)
        return false;
    _620.erase(entry);
    return true;
}

void Unk_7102476640::m11() {
    m25(false);
}

void Unk_7102476640::m14() {}

// NON_MATCHING: translation assignment pairs two stack stores that are separate in the native.
void Unk_7102476640::m16() {
    if (Manager::instance()->_64c38 != 5 || (Manager::instance()->_64c30_bytes[2] & 0x20))
        return;
    sead::Vector3f position(0.0f, 0.0f, 0.0f);
    if (_60.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_60, &accessor);
        position = accessor.getActorMtx().getTranslation();
        _74 = position;
    } else if (_50) {
        position = _50->getTranslate();
    }
    updateDistrictFromPos(&position);
}

void Unk_7102476640::m21() {
    if (_3c & 1)
        sub_710095156C(false);
}

// NON_MATCHING: direct search removes the native nullable-find guard.
void Unk_7102476640::m24(bool enabled) {
    m28(enabled);
    if ((_3c & 3) == 3) {
        auto& list = UiSubsys1::instance()->_5d8;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                break;
            }
        }
        UiSubsys1::instance()->sub_7100958134(this);
    }
}

// NON_MATCHING: iterator traversal keeps object-pointer adjustments outside the native node loop.
bool UiSubsys1::sub_7100958134(Unk_7102476640* entry) {
    if (!entry || _5d8.isFull())
        return false;
    auto* item = _5d8.emplaceBack(nullptr);
    if (!item)
        return false;
    *item = entry;
    for (auto it = _5d8.begin(); it != _5d8.end(); ++it) {
        auto next = it;
        ++next;
        while (next != _5d8.end()) {
            auto current = next;
            ++next;
            if (*current == *it)
                _5d8.erase(&*current);
        }
    }
    return true;
}

// NON_MATCHING: direct search removes nullable-find guards and merges the native insertion paths.
void Unk_7102476640::m25(bool enabled) {
    m27(enabled);
    UiSubsys1::instance()->_808.lock();
    if ((_3c & 0x30) == 0x30) {
        auto& list = UiSubsys1::instance()->_5a8;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                break;
            }
        }
        if (!UiSubsys1::instance()->_5a8.isFull()) {
            if (auto* entry = UiSubsys1::instance()->_5a8.emplaceBack(nullptr))
                *entry = this;
        }
    } else if ((_3c & 0x31) == 0x20) {
        auto& list = UiSubsys1::instance()->_5a8;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                break;
            }
        }
    }
    UiSubsys1::instance()->_808.unlock();
}

// NON_MATCHING: direct search removes nullable-find guards and merges the native insertion paths.
s32 Unk_7102476640::sub_7100958408(bool enabled) {
    m27(enabled);
    UiSubsys1::instance()->_808.lock();
    s32 result = 0;
    if ((_3c & 0x30) == 0x30) {
        auto& list = UiSubsys1::instance()->_5a8;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                break;
            }
        }
        if (!UiSubsys1::instance()->_5a8.isFull()) {
            if (auto* entry = UiSubsys1::instance()->_5a8.emplaceBack(nullptr))
                *entry = this;
        }
        result = 1;
    } else if ((_3c & 0x31) == 0x20) {
        auto& list = UiSubsys1::instance()->_5a8;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                result = -1;
                break;
            }
        }
    }
    UiSubsys1::instance()->_808.unlock();
    return result;
}

// NON_MATCHING: compiler merges the native false-result tail-call setup paths.
s32 Unk_7102476640::sub_7100957A64() {
    bool enabled = false;
    if (_50) {
        if (Manager::instance()->_64c30_bytes[2] & 0x40)
            return 0;
        if (UiSubsys1::instance()->_800 == 2) {
            enabled = true;
        } else {
            auto* entry = UiSubsys1::instance()->_478;
            if (entry && entry->_50 != -1 &&
                (entry->_44 == 0xff || (UiSubsys1::instance()->_120 & (1u << entry->_50)))) {
                enabled = _60.hasProc();
                if (!enabled && _58 != -1) {
                    entry = UiSubsys1::instance()->_478;
                    if (_58 == (entry ? entry->_50 : 0)) {
                        if (!_50)
                            return 0;
                        enabled = true;
                    }
                }
            }
        }
    }
    return sub_7100958408(enabled);
}

void Unk_7102476640::m12() {
    if (_50) {
        if (Manager::instance()->_64c30_bytes[2] & 0x40)
            return;
        if (UiSubsys1::instance()->_800 == 2) {
            m25(true);
            return;
        }
        auto* entry = UiSubsys1::instance()->_478;
        if (entry && entry->_50 != -1 &&
            (entry->_44 == 0xff || (UiSubsys1::instance()->_120 & (1u << entry->_50)))) {
            bool enabled = _60.hasProc();
            if (!enabled && _58 != -1) {
                entry = UiSubsys1::instance()->_478;
                if (_58 == (entry ? entry->_50 : 0)) {
                    if (!_50)
                        return;
                    enabled = true;
                }
            }
            sub_7100958408(enabled);
            return;
        }
    }
    m25(false);
}

void Unk_7102476640::m27(bool enabled) {
    _3c = (enabled != ((_3c & 0x10) != 0)) ? _3c | 0x20 : _3c & ~0x20;
    _3c = enabled ? _3c | 0x10 : _3c & ~0x10;
}

void Unk_7102476640::m28(bool enabled) {
    _3c = (enabled != ((_3c & 1) != 0)) ? _3c | 2 : _3c & ~2;
    _3c = enabled ? _3c | 1 : _3c & ~1;
    _3c |= (_3c & 2) << 13;
}

void Unk_7102476640::sub_7100958C7C() {
    _71 = _70;
    if (_50 && !_60.hasProc()) {
        auto* actor = _50->tryGetActor(false);
        const bool has_proc = _60.hasProc();
        if (actor) {
            if (has_proc)
                _60.reset();
            _60.acquire(actor, false);
        } else if (has_proc) {
            _60.reset();
        }
    }
    _70 = _60.hasProc();
}

bool UiSubsys1::sub_7100958D18() const {
    return _478 && _478->_50 != _478->_54;
}

bool Unk_7102476640::sub_7100958D38() const {
    return u32(_80) - 1 < 2;
}

void Unk_7102476640::sub_7100958D4C() {
    if (Manager::instance()->_64c38 == 5 && !(Manager::instance()->_64c30_bytes[2] & 0x20)) {
        _84 = _80;
        if (_60.hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            if (ksys::act::acquireActor(&_60, &accessor) && sub_710003B738(accessor)) {
                const u32 state = sub_710003B71C(accessor);
                _80 = state == 6 || state == 7 ? 1 : (state == 5 ? 2 : 0);
            }
        } else {
            _80 = 0;
        }
    }
}

// NON_MATCHING: static block offset of sUnk_71025d6d0c only (see UiSubsys1Entry::~UiSubsys1Entry).
Unk_7102476640::~Unk_7102476640() {
    if (_60.hasProc())
        _60.reset();
}

// NON_MATCHING: the 0x6e0 compare is scheduled after the vtable load in the original.
void Unk_7102476738::m19() {
    auto* subsys = UiSubsys1::instance();
    if (subsys->_6d4 <= _28.x && _28.x <= subsys->_6dc && subsys->_6d8 <= _28.z && _28.z <= subsys->_6e0)
        m24(true);
    else
        m24(false);
    if (sUnk_71025d6a98)
        m24(false);
}

s32 Unk_7102476738::m10() {
    return 5;
}

// NON_MATCHING: horizontal coordinate loads and subtraction scheduling differ.
void Unk_7102476830::m5() {
    m12();
    m13();
    if (!Manager::instance()->isPausedMaybe()) {
        auto* entry = UiSubsys1::instance()->_478;
        const f32 dx = _28.x - entry->_28.x;
        const f32 dz = _28.z - entry->_28.z;
        if (dx * dx + dz * dz < 400.0f) {
            const f32 height = entry->_28.y - _28.y;
            if (height > -25.0f && height < 30.0f && _50.updateAndCheckEnded())
                m25(false);
        } else {
            _50.init(3.0f);
        }
    }
    if (UiSubsys1::instance()->_698 != this)
        _68.init(0.0f);
    else
        _68.update();
}

// 0x7100959438
bool UiSubsys1::sub_7100959438(const UiSubsys1Entry* entry) const {
    return _698 == entry;
}

// NON_MATCHING: the 0x6e0 compare is scheduled after the vtable load in the original.
void Unk_7102476830::m19() {
    auto* subsys = UiSubsys1::instance();
    if (subsys->_6d4 <= _28.x && _28.x <= subsys->_6dc && subsys->_6d8 <= _28.z && _28.z <= subsys->_6e0)
        m24(true);
    else
        m24(false);
    if (sUnk_71025d6a98)
        m24(false);
}

s32 Unk_7102476830::m10() {
    return 4;
}

// NON_MATCHING: direct search removes the native nullable-find guard.
void Unk_7102476738::m24(bool enabled) {
    m28(enabled);
    if ((_3c & 3) == 3) {
        auto& list = UiSubsys1::instance()->_620;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                break;
            }
        }
        if (!UiSubsys1::instance()->_620.isFull()) {
            if (auto* entry = UiSubsys1::instance()->_620.emplaceBack(nullptr))
                *entry = this;
        }
    }
}

// NON_MATCHING: direct search removes the native nullable-find guard.
void Unk_7102476830::m24(bool enabled) {
    m28(enabled);
    if ((_3c & 3) == 3) {
        auto& list = UiSubsys1::instance()->_668;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                break;
            }
        }
        if (!UiSubsys1::instance()->_668.isFull()) {
            if (auto* entry = UiSubsys1::instance()->_668.emplaceBack(nullptr))
                *entry = this;
        }
    }
}

// NON_MATCHING: direct searches remove the native nullable-find guards.
void Unk_7102476738::m25(bool enabled) {
    m27(enabled);
    if ((_3c & 0x30) == 0x30) {
        auto* subsys = UiSubsys1::instance();
        auto& list = subsys->_6a0;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                subsys->sub_71009637D4();
                break;
            }
        }
        subsys = UiSubsys1::instance();
        if (!subsys->_6a0.isFull()) {
            if (auto* entry = subsys->_6a0.emplaceBack(nullptr)) {
                *entry = this;
                subsys->sub_71009637D4();
            }
        }
    } else if ((_3c & 0x30) == 0x20) {
        auto* subsys = UiSubsys1::instance();
        auto& list = subsys->_6a0;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                subsys->sub_71009637D4();
                break;
            }
        }
    }
}

Unk_7102476738::~Unk_7102476738() = default;

// NON_MATCHING: direct searches remove the native nullable-find guards.
void Unk_7102476830::m25(bool enabled) {
    m27(enabled);
    if ((_3c & 0x30) == 0x30) {
        _50.init(3.0f);
        auto* subsys = UiSubsys1::instance();
        auto& list = subsys->_6a0;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                subsys->sub_71009637D4();
                break;
            }
        }
        subsys = UiSubsys1::instance();
        if (!subsys->_6a0.isFull()) {
            if (auto* entry = subsys->_6a0.emplaceBack(nullptr)) {
                *entry = this;
                subsys->sub_71009637D4();
            }
        }
    } else if ((_3c & 0x30) == 0x20) {
        auto* subsys = UiSubsys1::instance();
        auto& list = subsys->_6a0;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                subsys->sub_71009637D4();
                break;
            }
        }
        _68.init(0.0f);
    }
}

// NON_MATCHING: static block offset of sUnk_71025d6d0c only (see UiSubsys1Entry::~UiSubsys1Entry).
Unk_7102476830::~Unk_7102476830() {
    _50.init(0.0f);
    _68.init(0.0f);
}
// NON_MATCHING: direct search removes the native nullable-find guard.
void Unk_7102476928::m25(bool enabled) {
    UiSubsys1Entry::m25(enabled);
    if ((_3c & 0x30) == 0x30) {
        auto* subsys = UiSubsys1::instance();
        auto& list = subsys->_6a0;
        for (auto& entry : list) {
            if (entry == this) {
                list.erase(&entry);
                subsys->sub_71009637D4();
                break;
            }
        }
        subsys = UiSubsys1::instance();
        if (!subsys->_6a0.isFull()) {
            if (auto* entry = subsys->_6a0.emplaceBack(nullptr)) {
                *entry = this;
                subsys->sub_71009637D4();
            }
        }
    }
}

Unk_7102476928::~Unk_7102476928() = default;

}  // namespace uking::ui
