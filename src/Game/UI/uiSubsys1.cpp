#include <container/seadBuffer.h>
#include <cstddef>
#include <limits>
#include <basis/seadNew.h>
#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <prim/seadBitFlag.h>
#include <prim/seadScopedLock.h>
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameRadarMgr.h"
#include "Game/gameSceneMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace uking::ui {

// The singleton's storage (0x71025d6aa8) and the disposer's static pointer (0x71025d6aa0).
UiSubsys1* UiSubsys1::sInstance = nullptr;
UiSubsys1::SingletonDisposer_* UiSubsys1::SingletonDisposer_::sStaticDisposer = nullptr;

// 0x710095a4bc: allocates the 0x3920-byte instance, constructs its disposer at +8 and then the
// object itself. Unlike SEAD_CREATE_SINGLETON_INSTANCE the original has no double-create assert.
UiSubsys1* UiSubsys1::createInstance(sead::Heap* heap) {
    if (!sInstance) {
        u8* buffer = new (heap, alignof(UiSubsys1)) u8[sizeof(UiSubsys1)];
        auto* disposer_buffer = buffer + offsetof(UiSubsys1, mSingletonDisposerBuf_);
        SingletonDisposer_::sStaticDisposer = new (disposer_buffer) SingletonDisposer_(heap);
        sInstance = new (buffer) UiSubsys1;
    }
    return sInstance;
}

// 0x710095a544: tears the disposer and the instance down. The disposer dtor does not clear the
// static pointer itself here because it is cleared before the call.
void UiSubsys1::destroyInstance() {
    SingletonDisposer_* disposer = SingletonDisposer_::sStaticDisposer;
    if (!disposer)
        return;
    SingletonDisposer_::sStaticDisposer = nullptr;
    disposer->~SingletonDisposer_();
    delete sInstance;
    sInstance = nullptr;
}

// 0x710095a3ec / 0x710095a450 (D1 / D0)
UiSubsys1::SingletonDisposer_::~SingletonDisposer_() {
    if (this == sStaticDisposer) {
        sStaticDisposer = nullptr;
        sInstance->~UiSubsys1();
        sInstance = nullptr;
    }
}

// The UI facade singleton (CSV: SheikSensorGaugeState). Storage 0x71025d6ac0 / disposer 0x71025d6ab8.
Unk_71025d6ac0* Unk_71025d6ac0::sInstance = nullptr;
Unk_71025d6ac0::SingletonDisposer_* Unk_71025d6ac0::SingletonDisposer_::sStaticDisposer = nullptr;

// 0x7100967fc8
void Unk_71025d6ac0::deleteInstance() {
    SingletonDisposer_* disposer = SingletonDisposer_::sStaticDisposer;
    if (!disposer)
        return;
    SingletonDisposer_::sStaticDisposer = nullptr;
    disposer->~SingletonDisposer_();
    delete sInstance;
    sInstance = nullptr;
}

// 0x7100967da8 / 0x7100967e0c (D1 / D0)
Unk_71025d6ac0::SingletonDisposer_::~SingletonDisposer_() {
    if (this == sStaticDisposer) {
        sStaticDisposer = nullptr;
        sInstance->~Unk_71025d6ac0();
        sInstance = nullptr;
    }
}

// 0x71025d6ab0: bypass for the sensor availability check.
KSYS_VISIBILITY_HIDDEN bool sUnk_71025d6ab0 = false;
// 0x71025d6a98 / 0x71025d6a9c: written by 0x7100960ad8; 6a98 hides the Unk_7102476738 / Unk_7102476830 markers
// (their m19), 6a9c is set while UiSubsys1::_3860 is non-zero.
KSYS_VISIBILITY_HIDDEN bool sUnk_71025d6a98 = false;
KSYS_VISIBILITY_HIDDEN bool sUnk_71025d6a9c = false;

bool sub_7100A9C110(s32 value);

// 0x710096023c
void UiSubsys1::sub_710096023C() {
    _6f0.setToEnd();
    _6ec = false;
}

// NON_MATCHING: raw marker-kind copying omits the native spill; empty-list loops merge.
void UiSubsys1::sub_71009637D4() {
    auto* entry = _6a0.front();
    for (s32 i = 0; i < _6d0; ++i) {
        if (entry) {
            ksys::gdt::setFlag_MapApp_MapIconNo((*entry)->_1c, i, false);
            ksys::gdt::setFlag_MapApp_MapIconPos((*entry)->_28, i, false);
            entry = _6a0.next(entry);
        } else {
            ksys::gdt::resetFlag_MapApp_MapIconNo(i, false);
            ksys::gdt::resetFlag_MapApp_MapIconPos(i, false);
        }
    }
}

// 0x7100968844: clears the map mode and its demo state; if the map mode was one of the demo
// modes (2, 3, 4), it also leaves the demo through sub_7100966EA8.
void UiSubsys1::sub_7100968844() {
    _128 = -1;
    if (getMapMode() == 2 || getMapMode() == 3 || getMapMode() == 4)
        sub_7100966EA8(false);
    _3860 = 0;
    _3830 = 0;
    sUnk_71025d6ab0 = false;
    _d80[4].mSelected._a0 = 4;
}

// 0x7100964518: turns the marker position `pos` into the widget position and hands pin `index` to
// sub_710096421C; `flag` selects the assignment path.
void UiSubsys1::sub_7100964518(s32 index, const sead::Vector2f& pos, bool flag) {
    sead::Vector2f out(0.0f, 0.0f);
    if (auto* widget = sUnk_71025d6c70._50)
        widget->sub_71009A9F4C(pos, &out);
    sead::Vector3f v(out.x, 0.0f, out.y);
    sub_7100AA0C04(&v);
    sub_710096421C(index, v, flag);
}

// 0x7100957500 (placeholder name): the marker position for the current manager state.
// NON_MATCHING: the state 4 loop in the original spills the kind and the literal to the stack before
// the compare and shares the found block with the state 7 loops; this is the natural form.
const sead::Vector3f* UiSubsys1::getMapMarkerPosition() const {
    auto* manager = Manager::instance();
    switch (manager->_64c38) {
    case 0:
        return _338 ? &_338->_28 : &sead::Vector3f::zero;
    case 1:
        return _320 ? &_320->_28 : &sead::Vector3f::zero;
    case 2:
        return _328 ? &_328->_28 : &sead::Vector3f::zero;
    case 3:
        return _330 ? &_330->_28 : &sead::Vector3f::zero;
    case 4:
        if (ksys::gdt::getFlag_FinalTrial_InBossBattleArea(false))
            return &sUnk_71025d6c70._a8;
        for (auto& entry : _2e0) {
            if (entry._1c == 4)
                return &entry._28;
        }
        return &sead::Vector3f::zero;
    case 7: {
        const s32 pin = manager->_64c40;
        for (auto& entry : _2f0) {
            if (entry._78 == pin)
                return &entry._28;
        }
        for (auto& entry : _300) {
            if (entry._78 == pin)
                return &entry._28;
        }
        return &sead::Vector3f::zero;
    }
    default:
        return &sead::Vector3f::zero;
    }
}

// 0x7100961cd4: the position to centre the map on for the current manager state.
// NON_MATCHING: the original copies the marker position through the stack at the join; ours keeps
// the X / Y components in registers (same instructions otherwise).
void UiSubsys1::sub_7100961CD4(sead::Vector3f* out) {
    sead::Vector3f pos(0, 0, 0);
    const u32 state = Manager::instance()->_64c38;
    switch (state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 7:
        pos = *getMapMarkerPosition();
        break;
    case 6: {
        sead::Vector3f dest[2];
        SceneMgr::instance()->getMapPosition("MasterSword", dest, "MainField", nullptr);
        pos = dest[0];
        break;
    }
    default:
        sub_7100A9B800(&pos);
        if (pos == sUnk_71025d6c70._78) {
            if (!_478)
                return;
            pos = _478->_28;
            if (pos == sUnk_71025d6c70._78)
                return;
        }
        break;
    }
    *out = pos;
}

// 0x710096310c: the marker nearest to `pos` (in the XZ plane, within `radius`); writes its index to `out_index`
bool UiSubsys1::sub_710096310C(s32* out_index, const sead::Vector3f* pos, f32 radius) {
    bool found = false;
    f32 nearest = std::numeric_limits<f32>::max();
    const f32 radius_sq = radius * radius;
    for (auto& marker_ref : _310) {
        auto* marker = &marker_ref;
        const sead::Vector2f marker_pos(marker->_28, marker->_30);
        const sead::Vector2f player_pos(pos->x, pos->z);
        const f32 dx = marker_pos.x - player_pos.x;
        const f32 dz = marker_pos.y - player_pos.y;
        const f32 dist_sq = dx * dx + dz * dz;
        if (dist_sq < radius_sq && dist_sq < nearest) {
            *out_index = marker->_44;
            nearest = dist_sq;
            found = true;
        }
    }
    return found;
}

// 0x7100963c8c
void UiSubsys1::sub_7100963C8C(const UiSubsys1PinArg* arg) {
    auto* unk = _378;
    if (!unk)
        return;
    unk->_54[arg->index] = arg->index;
    unk->_5c[arg->index] = arg->value;
    auto& entry = unk->_64[arg->index];
    entry.pos.set(arg->pos);
}

// 0x71009644e8
UiSubsys1Entry* UiSubsys1::sub_71009644E8(s32 index) {
    if (index < 0 || index >= _658.size())
        return nullptr;
    return _658[index];
}

// 0x7100963704
void UiSubsys1::set128(s32 value) {
    _128 = value;
}

// 0x7100968774: advances the selected map mode entry count until it reaches the mode's state count
// NON_MATCHING: the original materialises this + 0x3830 for the two stores; ours uses the immediate offset.
void UiSubsys1::sub_7100968774() {
    if (getMapMode() == 6) {
        ++_3830;
        return;
    }
    const u16 mode = getMapMode();
    if (_3830 == _d80[mode < 5 ? mode : 0].mSelected._98) {
        _3830 = 0;
        return;
    }
    ++_3830;
}

// 0x7100968b1c: the state of the selected entry of the current map mode group (0 when there is none)
// NON_MATCHING: clang sinks the u16 mask of the second mode lookup into the final block; the original
// truncates right after each lookup (same block order otherwise).
s32 UiSubsys1::sub_7100968B1C() {
    const s32 index = _3830;
    if (index == -1 || getMapMode() == 6)
        return 0;
    const u16 mode = getMapMode();
    if (u32(index) > 0xb)
        return 0;
    return _d80[mode < 5 ? mode : 0].mEntries[index]._8;
}

// 0x7100968af8: sets a bit of the 16-bit flag word at 0x3860
void UiSubsys1::sub_7100968AF8(s32 index) {
    _3860 |= 1 << u16(index);
    _3830 = 0;
}

// 0x71009512f8
UiSubsys1ListEntry* UiSubsys1::findListEntry(void* key) {
    if (!key)
        return nullptr;
    for (auto& entry : _280) {
        if (entry == key)
            return &entry;
    }
    return nullptr;
}

// 0x7100951338
bool UiSubsys1::freeListEntry(UiSubsys1ListEntry* entry) {
    if (!entry)
        return false;
    _280.erase(entry);
    return true;
}

// 0x71009595fc
UiSubsys1Entry** UiSubsys1::sub_71009595FC(UiSubsys1Entry* key) {
    if (!key)
        return nullptr;
    for (auto& entry : _668) {
        if (entry == key)
            return &entry;
    }
    return nullptr;
}

// NON_MATCHING: the original keeps this + 0x3840 in a callee-saved register across the mode lookups;
// ours recomputes it for the UiTimer::init call (same instructions otherwise).
// 0x7100960a1c: resets the map timer from the duration of the selected mode.
void UiSubsys1::sub_7100960A1C() {
    _3830 = 0;
    f32 duration = 0.0f;
    if (getMapMode() != 6) {
        u16 mode = _3860;
        if (mode == 0)
            mode = 6;
        else
            mode = sead::BitFlagUtil::countContinuousOffBitFromRight(mode);
        const s64 index = _3830;
        if (u32(index) <= 0xb)
            duration = _d80[mode < 5 ? mode : 0].mEntries[index]._c;
    }
    _3840.init(duration);
}

// 0x7100968c2c
// NON_MATCHING: clang sinks the second mode lookup's u16 mask past the index range test; the original
// truncates right after each lookup (one instruction).
void UiSubsys1::sub_7100968C2C(s32 a) {
    UiTimer& timer = _3840;
    const bool restart = (a & 1) != 0;
    if (restart) {
        f32 duration = 0.0f;
        if (getMapMode() != 6) {
            const u16 mode = getMapMode();
            const s64 index = _3830;
            if (u32(index) <= 0xb)
                duration = _d80[mode < 5 ? mode : 0].mEntries[index]._c;
        }
        timer.init(duration);
    }
    _3858 = restart;
}

// 0x71009635dc: whether the map should be shown for the current mode and state.
bool UiSubsys1::sub_71009635DC() {
    if (getMapMode() != 1) {
        if (getMapMode() != 2)
            return false;
    }
    if (_d80[4].mSelected._a0 > 0)
        return false;
    const s64 index = _3830;
    if (index == -1)
        return true;
    if (getMapMode() == 6)
        return true;
    u16 mode = _3860;
    if (mode == 0)
        mode = 6;
    else
        mode = sead::BitFlagUtil::countContinuousOffBitFromRight(mode);
    if (u32(index) < 0xc)
        return _d80[mode < 5 ? mode : 0].mEntries[index]._8 < 3;
    return true;
}

// NON_MATCHING: same instructions, the scheduler hoists the two bounds loads above the flag stores and
// mirrors the fsel operands; the source order is the natural one
// 0x7100961088 (placeholder name): resets the map marker bounds from the map scale.
void UiSubsys1::sub_7100961088() {
    const f32 inv_scale = 1.0f / _850._28;
    const bool old = _8f0;
    _8f0 = true;
    _8f1 = old;

    const f32 half_x = (_8e8 - _8e0 - inv_scale * sUnk_71025d6c70.mLayoutSize.x) * 0.5f;
    const f32 half_y = sead::Mathf::abs(_8ec) - inv_scale * sUnk_71025d6c70.mLayoutSize.y * 0.5f;

    _8dc = sead::Mathf::maxNumber();
    _8d0 = -sead::Mathf::max(half_x, 0.0f);
    _8d4 = -sead::Mathf::max(half_y, 0.0f);
    _8d8 = sead::Mathf::max(half_x, 0.0f);
}

// 0x71009686f0 (placeholder name): whether the map scale matches the selected threshold.
bool UiSubsys1::sub_71009686F0() const {
    if (_128 == -1)
        return false;
    const s32 index = u32(_128) < 15 ? _128 : 0;
    const s32 value = _7c4[index];
    if (value == -1)
        return false;

    f32 threshold;
    if (u32(value) > 3)
        threshold = -1.0f;
    else
        threshold = sUnk_71025d6c70._1e8[value];

    return _850._28 == threshold;
}

// 0x7100963598
u32 UiSubsys1::sub_7100963598() {
    u32 value = _120;
    if (sub_71009635DC() && _128 != -1)
        value &= ~(1u << _128);
    return value;
}

// 0x7100963724
// 0x710096372c
// NON_MATCHING: the compiler folds the null entry and actor tests after their earlier dereferences.
void UiSubsys1::sub_710096372C(ksys::act::Actor* actor) {
    sead::ScopedLock<sead::CriticalSection> lock(&_808);
    for (auto** it = _598.dataBegin(); it != _598.dataEnd(); ++it) {
        auto* entry = *it;
        if (entry->_50 != actor->getMapObject())
            continue;
        if (entry) {
            const bool has_proc = entry->_60.hasProc();
            if (actor) {
                if (has_proc)
                    entry->_60.reset();
                entry->_60.acquire(actor, false);
            } else if (has_proc) {
                entry->_60.reset();
            }
        }
        break;
    }
}

void UiSubsys1::sub_7100963724() {
    sub_710095F584(true);
}

// 0x710095963c
bool UiSubsys1::sub_710095963C(UiSubsys1Entry** entry) {
    if (!entry)
        return false;
    _668.erase(entry);
    return true;
}

// 0x7100963c78
void UiSubsys1::sub_7100963C78(bool a1) {
    if (_378)
        _378->_50 = a1;
}

// 0x7100960df8
// 0x7100960758
void UiSubsys1::sub_7100960758(sead::BufferedSafeString* out) {
    const char* name;
    ksys::gdt::getFlag_ActorName_SeakSensor_Slot0(&name);
    out->copy(name);
}

bool UiSubsys1::sub_7100960DF8() {
    return _3860 != 0;
}

// 0x7100960dac
bool UiSubsys1::sub_7100960DAC(s32 index) const {
    u16 lowest = _3860 != 0 ? sead::BitFlagUtil::countContinuousOffBitFromRight(_3860) : 6;
    return lowest == index;
}

// 0x7100962cc8
void UiSubsys1::sub_7100962CC8() {
    if (Manager::instance()->_64c38 >= 5)
        return;
    if (_320 && _320->_58)
        _320->updateDistrictFromPos(&_320->_58->_38);
    if (_328 && _328->_58)
        _328->updateDistrictFromPos(&_328->_58->_38);
    if (_330 && _330->_58)
        _330->updateDistrictFromPos(&_330->_58->_38);
    if (_338 && _338->_58)
        _338->updateDistrictFromPos(&_338->_58->_38);
}

// 0x7100968a44
bool UiSubsys1::sub_7100968A44(s32 type) const {
    switch (type) {
    case 0:
        if (!_3860)
            return false;
        {
            const u16 lowest = sead::BitFlagUtil::countContinuousOffBitFromRight(_3860);
            if (lowest == 2)
                return true;
        }
        if (!_3860)
            return false;
        {
            const u16 lowest = sead::BitFlagUtil::countContinuousOffBitFromRight(_3860);
            return lowest == 3;
        }
    case 1:
        if (!_3860)
            return false;
        {
            const u16 lowest = sead::BitFlagUtil::countContinuousOffBitFromRight(_3860);
            return lowest == 4;
        }
    default:
        return false;
    }
}

// Placeholder name; no known callers.
void UiSubsys1::sub_7100961008() {
    sUnk_71025d6a98 = false;
    sUnk_71025d6a9c = false;
}

// 0x710096101c
void UiSubsys1::sub_710096101C() {
    _38b9 = _38b8;
    _38b8 = sub_7100A9C110(0);
}

// 0x7100961058
void UiSubsys1::copy38b8To38b9() {
    _38b9 = _38b8;
}

// 0x710096106c
void UiSubsys1::set38b8() {
    _38b8 = 1;
}

// 0x710096107c
void UiSubsys1::clear38b8() {
    _38b8 = 0;
}

// 0x71009502f8 (CSV uiSubsys1::__auto17)
bool UiSubsys1::is848Zero() const {
    return _848 == 0;
}

// 0x7100960234 (CSV uiSubsys1::__auto16)
bool UiSubsys1::returnTrue() const {
    return true;
}

// 0x7100961cc4 (CSV uiSubsys1::is848EqualTo1)
bool UiSubsys1::is848EqualTo1() const {
    return _848 == 1;
}

// 0x7100965e68
bool UiSubsys1::is898Zero() const {
    return _850._48 == 0;
}

// 0x7100965e78
bool UiSubsys1::is898EqualTo3() const {
    return _850._48 == 3;
}

// 0x7100965e88
bool UiSubsys1::is898Below3() const {
    return _850._48 < 3;
}

// 0x7100965e98
bool UiSubsys1::is898Positive() const {
    return _850._48 > 0;
}

// 0x7100966008
const sead::Vector2f* sub_7100966008() {
    return &sUnk_71025d6c70.mLayoutSize;
}

// 0x7100966018
void sub_7100966018(sead::Vector2f* out) {
    *out = sUnk_71025d6c70.mLayoutSize * 0.5f;
}

// 0x710096603c
void UiSubsys1::sub_710096603C(sead::Vector2f* out) const {
    const f32 scale = 1.0f / _850._28;
    *out = {scale * sUnk_71025d6c70.mLayoutSize.x, scale * sUnk_71025d6c70.mLayoutSize.y};
}

// 0x7100966064
void UiSubsys1::sub_7100966064(sead::Vector2f* out) const {
    const f32 scale = 1.0f / _850._38;
    *out = {scale * sUnk_71025d6c70.mLayoutSize.x, scale * sUnk_71025d6c70.mLayoutSize.y};
}

// 0x7100965ea8
s32 UiSubsys1::sub_7100965EA8() const {
    return _84c;
}

// 0x7100965fcc
bool UiSubsys1::sub_7100965FCC() const {
    if (_8f0)
        return false;
    return _8f1;
}

// 0x7100965fec
f32 UiSubsys1::sub_7100965FEC() const {
    static const sead::SafeArray<f32, 4> sValues{{6.0f, 7.5f, 8.5f, 9.5f}};
    return sValues[_850._48];
}

// 0x7100962d8c (CSV uiSubsys1::__auto9)
bool UiSubsys1::get38b8() const {
    return _38b8;
}

// 0x710096370c (CSV uiSubsys1::__auto20)
bool UiSubsys1::is128EqualTo6() const {
    return _128 == 6;
}

// 0x7100965d08 (CSV uiSubsys1::set848)
void UiSubsys1::set848(s32 value) {
    _848 = value;
}

// 0x7100966314 (CSV uiSubsys1::__auto8)
void UiSubsys1::set38c8() {
    _38c8 = 1;
}

// 0x7100966324 (CSV uiSubsys1::__auto11)
void UiSubsys1::clear38c8() {
    _38c8 = 0;
}

// 0x7100966cf0 (CSV uiSubsys1::__auto15)
void UiSubsys1::set3884(bool value) {
    _3884 = value;
}

// 0x7100966e94 (CSV uiSubsys1::__auto28)
s32 UiSubsys1::get38a8() const {
    return _38a8;
}

// 0x710096746c (CSV uiSubsys1::__auto5)
bool UiSubsys1::get38ac() const {
    return _38ac;
}

// 0x7100966ea8 (placeholder name): closes the Sheikah sensor UI.
void UiSubsys1::sub_7100966EA8(bool a1) {
    _38a8 = 0;
    if (_38ac)
        _38d8 = true;

    if (auto* main_screen = sead::DynamicCast<ScreenMainScreen>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::MainScreen)))
        main_screen->sub_7100A1E958(0);

    if (auto* radar = RadarMgr::instance()) {
        radar->__auto0("");
        ksys::gdt::setFlag_App_SeakSensor_SearchMode(0);
        if (a1) {
            createAndLoadScreenIfNeededImpl(ScreenId::AppSystemWindowNoBtn, nullptr);
            if (auto* screen = sead::DynamicCast<ScreenAppSystemWindowNoBtn>(
                    eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindowNoBtn)))
                screen->sub_71009FB958();
        }
    }
}

// 0x710096705c: opens the Sheikah sensor UI for its saved search target.
// NON_MATCHING: RTTI cache setup and saved-register allocation differ.
void UiSubsys1::sub_710096705C(bool show_window) {
    _38a8 = 1;
    if (_38ac)
        _38d8 = true;

    if (auto* main_screen = sead::DynamicCast<ScreenMainScreen>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::MainScreen)))
        main_screen->sub_7100A1E958(1);

    if (auto* radar = RadarMgr::instance()) {
        sead::FixedSafeString<64> name;
        const char* target;
        ksys::gdt::getFlag_ActorName_SeakSensor_Slot0(&target);
        name = target;
        if (!name.isEmpty()) {
            radar->__auto0(name);
            ksys::gdt::setFlag_App_SeakSensor_SearchMode(1);
            if (show_window) {
                createAndLoadScreenIfNeededImpl(ScreenId::AppSystemWindowNoBtn, nullptr);
                if (auto* screen = sead::DynamicCast<ScreenAppSystemWindowNoBtn>(
                        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindowNoBtn)))
                    screen->sub_71009FB958();
            }
        }
    }
}

// 0x7100964bac (placeholder name): empty in the original; the marker factories that call it build their
// entries themselves.
void UiSubsys1::sub_7100964BAC(sead::Heap*) {}

// 0x71009675d0 (placeholder name): empty in the original; see sub_7100964BAC.
void UiSubsys1::sub_71009675D0(sead::Heap*, Unk_7102477fc0*) {}

// 0x71009674e8
bool UiSubsys1::sub_71009674E8() const {
    return Unk_71025d6ac0::instance()->_29;
}

// 0x7100967534 (CSV uiSubsys1::__auto4)
void UiSubsys1::set38e4(s32 value) {
    _38e4 = value;
}

// 0x710096758c (CSV uiSubsys1::__auto6)
s32 UiSubsys1::get38f8() const {
    return _38f8;
}

// 0x710096759c (CSV uiSubsys1::__auto24)
s32 UiSubsys1::get3900() const {
    return _3900;
}

// 0x71009675b0 (CSV uiSubsys1::__auto23)
void UiSubsys1::set3904(bool value) {
    _3904 = value;
}

// 0x71009675e4 (CSV uiSubsys1::__auto36)
bool UiSubsys1::return0A() const {
    return false;
}

// 0x7100967504
bool UiSubsys1::isValid38e0() const {
    return _38e0 != -1;
}

// 0x7100967524
bool UiSubsys1::is38e4Equal(s32 value) const {
    return _38e4 == value;
}

// 0x7100967570
void UiSubsys1::set38ec(s32 a, s32 b) {
    _38ec = a;
    _38f0 = b;
}

// 0x71009675a4
u8 UiSubsys1::get3904() const {
    return _3904;
}

// 0x71009675c0
u8 UiSubsys1::get3905() const {
    return _3905;
}

// 0x71009675d4
bool UiSubsys1::return0C() const {
    return false;
}

// 0x71009675dc
bool UiSubsys1::return0D() const {
    return false;
}

// NON_MATCHING: the original evaluates the state test branch-free (csel chain, orr with the entry test); ours branches.
// 0x7100964174
bool UiSubsys1::sub_7100964174() const {
    const bool has_entry = _650 != nullptr;
    if (_38e0 != 0) {
        if (_38e0 == 1) {
            const u32 state = _38e8;
            return has_entry || (state < 6 || (u32(state - 6) > 4 && u32(state - 11) < 3));
        }
        return false;
    }
    return has_entry;
}

// NON_MATCHING: same logic; the original keeps the bit tests as cset flags and orders the branches differently.
// 0x7100968d10
void UiSubsys1::sub_7100968D10(bool set) {
    u32 flags = _3864;
    const u32 was_set = flags & 1;
    if (set) {
        flags |= 1;
        _3864 = flags;
    }
    u32 change;
    if ((flags & 1) && was_set == 0) {
        change = 2;
    } else {
        if (flags & 1)
            return;
        if (was_set == 0)
            return;
        change = 4;
    }
    _3864 = flags | change;
}

// NON_MATCHING: same logic; the original orders the loads / arithmetic differently (fmov of the vector after the bound maths).
// 0x7100966350
void UiSubsys1::sub_7100966350(const sead::Vector2f& value) {
    sead::Vector2f result = value;
    if (instance()->_848 != 0) {
        const f32 width = _8c8.x - _8c0.x;
        const f32 half_width = width * 0.5f;
        const f32 half_height = (_8c8.y - _8c0.y) * 0.5f;
        result.x = sead::Mathf::clamp(result.x, width * -0.5f, half_width);
        result.y = sead::Mathf::clamp(result.y, -half_height, half_height);
    }
    _3870 = result;
}

// NON_MATCHING: same as sub_7100966350.
// 0x7100966d0c
void UiSubsys1::sub_7100966D0C(const sead::Vector2f& value) {
    sead::Vector2f result = value;
    if (instance()->_848 != 0) {
        const f32 width = _8c8.x - _8c0.x;
        const f32 half_width = width * 0.5f;
        const f32 half_height = (_8c8.y - _8c0.y) * 0.5f;
        result.x = sead::Mathf::clamp(result.x, width * -0.5f, half_width);
        result.y = sead::Mathf::clamp(result.y, -half_height, half_height);
    }
    _3868 = result;
}

// 0x710096349c
s32 UiSubsys1::sub_710096349C(Pin pin) const {
    s32 base;
    s32 first;
    if (pin >= 0x1b && pin < 0x21) {
        first = 0;
        base = 0x1b;
    } else if (pin >= 0x21 && pin < 0x24) {
        first = 11;
        base = 0x21;
    } else if (pin >= 0x25 && pin <= 0x29) {
        first = 6;
        base = 0x25;
    } else {
        return -1;
    }
    return pin + (first - base);
}

// 0x7100968d5c
bool UiSubsys1::has3864Bit0() const {
    return _3864 & 1;
}

// 0x7100968d68
void UiSubsys1::clear3864() {
    _3864 = 0;
}

// 0x7100968d70
bool Unk_71025d6ac0::get88() const {
    return _88;
}

// 0x7100968d78
// 0x71009680dc: the original calls this out of line from ui::Manager (0x7100a79a04), so it is not in
// the manager's translation unit.
void Unk_71025d6ac0::sub_71009680DC() {
    ksys::xlink::Manager::instance()->setGlobalProperty(26, 10000.0f);
    ksys::xlink::Manager::instance()->setGlobalProperty(27, 0.0f);
}

void Unk_71025d6ac0::clear88() {
    _88 = false;
}

// 0x7100966ce4
sead::Vector2f* UiSubsys1::getVec3868() {
    return &_3868;
}

// 0x7100966d90
sead::Vector2f* UiSubsys1::getVec3870() {
    return &_3870;
}

// 0x7100966db0
sead::Vector2f* UiSubsys1::getVec3878() {
    return &_3878;
}

// 0x7100966684
void UiSubsys1::sub_7100966684(const sead::Vector3f* pos) {
    sead::Vector2f offset(pos->x * _850._60.x, -(pos->z * _850._60.y));
    sub_71009666C0(&offset);
}

// 0x7100965e58
Unk_7102475368* UiSubsys1::sub_7100965E58() {
    return &_850;
}

f32 UiSubsys1::sub_7100965EE0(f32 angle) const {
    return sub_7100AA0B6C(_850._2c + angle);
}

// NON_MATCHING: the clamps are conditional selects in ours; the original keeps the clamp's branches (its
// sead::Mathf::clamp is the branchy form) and negates half_width as (h + h) * -0.5.
// The receiver is UiSubsys1::instance() (its sInstance GOT slot is 0x71025dbe20; the caller passes the
// same object it cached at ScreenAppMapWidget+0x8d8), so the CSV owner is correct.
// 0x7100965eec
void UiSubsys1::sub_7100965EEC(f32 scale, sead::Vector2f* out) {
    f32 x = -_3868.x;
    f32 y = -_3868.y;

    if (UiSubsys1::instance()->_848 != 0) {
        const f32 inv_scale = 1.0f / scale;
        const f32 layout_x = inv_scale * sUnk_71025d6c70.mLayoutSize.x;
        const f32 layout_y = inv_scale * sUnk_71025d6c70.mLayoutSize.y;

        const f32 half_width = sead::Mathf::clampMin(((_8e8 - _8e0) - layout_x) * 0.5f, 0.0f);
        const f32 half_height =
            sead::Mathf::clampMin(sead::Mathf::abs(_8ec) - layout_y * 0.5f, 0.0f);

        x = sead::Mathf::clamp(x, -half_width, half_width);
        y = sead::Mathf::clamp(y, -half_height, sead::Mathf::maxNumber());
    }

    out->set(x, y);
}

// NON_MATCHING: the two clamps are conditional selects in ours (same as sub_7100965EEC).
// 0x71009663d4: sub_7100965EEC on the map's own scale (_850._38), stored in _850._40.
void UiSubsys1::sub_71009663D4() {
    f32 x = -_3868.x;
    f32 y = -_3868.y;

    if (UiSubsys1::instance()->_848 != 0) {
        const f32 inv_scale = 1.0f / _850._38;
        const f32 layout_x = inv_scale * sUnk_71025d6c70.mLayoutSize.x;
        const f32 layout_y = inv_scale * sUnk_71025d6c70.mLayoutSize.y;

        const f32 half_width = sead::Mathf::clampMin(((_8e8 - _8e0) - layout_x) * 0.5f, 0.0f);
        const f32 half_height =
            sead::Mathf::clampMin(sead::Mathf::abs(_8ec) - layout_y * 0.5f, 0.0f);

        x = sead::Mathf::clamp(x, -half_width, half_width);
        y = sead::Mathf::clamp(y, -half_height, sead::Mathf::maxNumber());
    }

    _850._40.x = x;
    _850._40.y = y;
}

// NON_MATCHING: float register allocation and the order of the fnmul / fmul pair (target: s2 = 1 / _850._60.x, y computed before x)
// 0x7100965d10
void UiSubsys1::sub_7100965D10(sead::Vector2f* out) const {
    const f32 inv_scale = 1.0f / _850._60.x;
    const sead::Vector2f pos = _850._20;
    out->set(-(pos.x * inv_scale), pos.y * inv_scale);
    sub_7100AA0BB0(out, _850._2c);
    const f32 inv_zoom = 1.0f / _850._28;
    out->x = inv_zoom * out->x;
    out->y = inv_zoom * out->y;
}

// 0x71009659a4
void UiSubsys1::sub_71009659A4(const sead::Vector2f* view) {
    sead::Vector2f offset;
    if (_850._60.x == 0 && _850._60.y == 0)
        offset.set(0, 0);
    else
        offset.set(-(_850._60.x * view->x), -(_850._60.y * view->y));
    _850._30 = offset;
    _850._40 = offset;
}

// 0x7100966d9c
void UiSubsys1::set880(const sead::Vector2f& value) {
    _850._30.x = value.x;
    _850._30.y = value.y;
}

// 0x7100966dbc
void UiSubsys1::set3878(const sead::Vector2f& value) {
    _3878.x = value.x;
    _3878.y = value.y;
}

// 0x7100966cd4
bool UiSubsys1::isLessOrEqual3880(f32 value) const {
    return _3880 <= value;
}

// 0x7100966dd0
bool UiSubsys1::is3888Equal(s32 value) const {
    return _3888 == value;
}

// 0x7100966d00
bool UiSubsys1::get3884() const {
    return _3884;
}

// 0x7100966330
bool UiSubsys1::get38c8() const {
    return _38c8;
}

// 0x7100966e9c
bool UiSubsys1::get38d8() const {
    return _38d8;
}

// 0x7100967478
bool UiSubsys1::get38d9() const {
    return _38d9;
}

// 0x710096633c
void UiSubsys1::copy38c8To38c9() {
    _38c9 = _38c8;
}

// 0x7100967484
void UiSubsys1::copy38d8To38d9() {
    _38d9 = _38d8;
}

// 0x7100966e14
void UiSubsys1::update388c() {
    _388c.update();
}

// 0x7100966e64
bool UiSubsys1::sub_7100966E64() const {
    if (_38b8)
        return false;
    return _38b9 != 0;
}

// 0x7100966de8
s32 UiSubsys1::sub_7100966DE8(s32 value) const {
    if (value >= 0 && value <= 5)
        return 5;
    if (value >= 6 && value <= 10)
        return 4;
    if (value >= 11 && value <= 13)
        return 5;
    return -1;
}

// 0x7100967498
bool UiSubsys1::sub_7100967498() const {
    if (!_38ac)
        return false;
    return _38ad == 0;
}

// 0x71009674c0
bool UiSubsys1::sub_71009674C0() const {
    if (_38ac)
        return false;
    return _38ad != 0;
}

// 0x7100966300
void UiSubsys1::start388c() {
    _388c.init(0.2f);
}

// 0x7100966e20
bool UiSubsys1::checkEnded388c() {
    return _388c.checkEnded();
}

// 0x7100967d98 (CSV uiSubsys1::__auto30)
bool UiSubsys1::return0B() const {
    return false;
}

// 0x7100967da0 (CSV uiSubsys1::return0)
bool UiSubsys1::return0() const {
    return false;
}

// 0x7100968764 (CSV uiSubsys1::__auto38)
s32 UiSubsys1::get3820() const {
    return _d80[4].mSelected._a0;
}

// 0x7100968824 (CSV uiSubsys1::__auto1)
ksys::Timer* UiSubsys1::getVec3834() {
    return &_3834;
}

// 0x7100968830 (CSV uiSubsys1::__auto19)
void UiSubsys1::resetVec3834() {
    _3834.reset(0.0f, 1.0f);
}

// 0x7100968cf8 (CSV uiSubsys1::__auto40)
bool UiSubsys1::get3858() const {
    return _3858;
}

// 0x7100966e3c (CSV uiSubsys1::__auto29)
bool UiSubsys1::is38b8And38b9Clear() const {
    return _38b8 && !_38b9;
}

// 0x71009648a8
void* UiSubsys1::sub_71009648A8() {
    for (auto& entry : _658) {
        if (!(entry._3c & 0x10))
            return &entry;
    }
    return nullptr;
}

// 0x7100964b24
// NON_MATCHING: identical except that the original loads the flag word of each entry with a 32-bit `ldr` where ours (the
// entry's `_3c` is a byte, as in sub_71009645A0 which matches with `ldrb`) loads a byte
s32 UiSubsys1::sub_7100964B24() {
    s32 flagged = 0;
    for (s32 i = 0; i < _610.size(); ++i)
        flagged += (_610(i)->_3c & 0x10) ? 1 : 0;
    return _610.size() - flagged;
}

// 0x7100964a0c
// NON_MATCHING: same checks and the same range / null logic, but the original has a single `mov w0, wzr` exit block
// (the three failure branches share it) where every source form gives separate exit blocks.
bool UiSubsys1::sub_7100964A0C(s32 index) {
    bool result = false;
    if (index >= 0 && index < _658.size()) {
        if (auto* entry = _658.at(index))
            result = entry->_3c & 0x10;
    }
    return result;
}

// 0x7100963538
bool UiSubsys1::sub_7100963538(s32 value) const {
    if (value >= 0 && value <= 5)
        return true;
    if (value >= 6 && value <= 10)
        return false;
    return value >= 11 && value <= 13;
}

// NON_MATCHING: only the operand order of the final `and` differs (the original ands the
// (value - 6 < 5) flag first).
// 0x7100963560
bool UiSubsys1::sub_7100963560(s32 value) const {
    return u32(value - 6) < 5 && u32(value) > 5;
}

// 0x710096357c
sead::Vector2f* UiSubsys1::sub_710096357C() const {
    return _478 ? &_478->_34 : nullptr;
}

// 0x7100963590
s32 UiSubsys1::returnFF() const {
    return 0xff;
}

// 0x710096371c
u8 UiSubsys1::get12c() const {
    return _12c;
}

// 0x71009638e8
void UiSubsys1::set6e4(s64 value) {
    _6e4 = value;
}

// 0x71009638f0
void UiSubsys1::sub_71009638F0(ksys::qst::Quest* quest) {
    _3a0 = quest;
    sub_71009638F8();
}

// 0x7100963c70
void UiSubsys1::sub_7100963C70() {
    _3a0 = nullptr;
    sub_71009638F8();
}

// 0x71009641d4
bool UiSubsys1::is38e0Equal(s32 value) const {
    return _38e0 == value;
}

// 0x71009641e4
s32 UiSubsys1::sub_71009641E4() const {
    const u32 value = _38e8;
    if (value < 6)
        return 0;
    if (value - 6 < 5)
        return 1;
    if (value - 11 < 3)
        return 0;
    return 2;
}

// 0x71009645a0: remembers the first entry of the table at 0x610 that has bit 4 of its byte at 0x3c clear
void UiSubsys1::sub_71009645A0() {
    for (auto& entry : _610) {
        if (!(entry._3c & 0x10)) {
            _650 = &entry;
            return;
        }
    }
}

// 0x7100964a40
void UiSubsys1::sub_7100964A40(const sead::Vector3f& pos) {
    _4c8 = true;
    _4bc.set(pos);
}

// 0x7100964ba4
s32 UiSubsys1::get614() const {
    return _610.capacity();
}

// 0x7100965960: entry of the threshold table for an index 0-3, or -1 for any other index
f32 sub_7100965960(s32 index) {
    if (index < 0 || index > 3)
        return -1.0f;
    return sUnk_71025d6c70._1e8[index];
}

// 0x7100965938
s32 UiSubsys1::sub_7100965938() const {
    if (_128 == -1)
        return -1;
    return _7c4[_128];
}

// 0x7100965994
void UiSubsys1::set898(s32 value) {
    _850._48 = value;
}

// 0x710096599c
bool UiSubsys1::returnTrue2() const {
    return true;
}

// 0x7100965e60
bool UiSubsys1::returnFalse() const {
    return false;
}

// 0x7100965cf0
s32 UiSubsys1::get7c4(s32 index) const {
    return _7c4[index];
}

// 0x7100966de0
void UiSubsys1::set3888(s32 value) {
    _3888 = value;
}

// 0x7100966e8c
s32 UiSubsys1::get38a4() const {
    return _38a4;
}

// 0x71009674fc
bool Unk_71025d6ac0::get29() const {
    return _29;
}

// 0x7100967514
s32 UiSubsys1::get38e0() const {
    return _38e0;
}

// 0x710096751c
void UiSubsys1::set38e0(s32 value) {
    _38e0 = value;
}

// 0x710096753c
s32 UiSubsys1::get38e8() const {
    return _38e8;
}

// 0x7100967544
void UiSubsys1::set38e8(s32 value) {
    _38e8 = value;
}

// 0x710096757c
s32 UiSubsys1::get38f4() const {
    return _38f4;
}

// 0x7100967584
void UiSubsys1::set38f4(s32 value) {
    _38f4 = value;
}

// 0x7100967594
s32 UiSubsys1::get38fc() const {
    return _38fc;
}

// 0x710096876c
void UiSubsys1::set3820(s32 value) {
    _d80[4].mSelected._a0 = value;
}

// Small helpers of the UiSubsys1 TU (placeholder names; free functions in the original).
// 0x7100965ec0
bool sub_7100965EC0() {
    return !ksys::gdt::getFlag_MiniMapDirection(false);
}

// 0x7100966168
s32 sub_7100966168(s32 value) {
    return 3 - value;
}

// 0x7100966174: value modulo 120
s32 sub_7100966174(s32 value) {
    return value % 120;
}

// 0x710096619c: value / 120
s32 sub_710096619C(s32 value) {
    return value / 120;
}

// 0x7100966118: the marker threshold for the bit index of `level` (1..8, four threshold entries).
f32 sub_7100966118(s32 level) {
    if (u32(level - 1) > 7)
        return -1.0f;
    s32 i = 0;
    while ((level & 1) == 0) {
        level >>= 1;
        ++i;
    }
    if (u32(i) > 3)
        return -1.0f;
    return sUnk_71025d6c70._1e8[i];
}

// 0x71009661bc
s32 sub_71009661BC(s32 value) {
    switch (value) {
    case 0:
        return 2;
    case 1:
        return 3;
    case 2:
        return 1;
    default:
        return -1;
    }
}

// 0x7100966e2c
void UiSubsys1::sub_7100966E2C() {
    _388c.reset();
}

// 0x7100968d04
bool UiSubsys1::sub_7100968D04() {
    return _3840.updateAndCheckEnded();
}

// 0x7100962634
void UiSubsys1::updateCompletionCount() {
    sub_7100962638();
}

}  // namespace uking::ui

namespace uking::ui {

bool UiSubsys1::sub_7100968BD8() {
    if (sUnk_71025d6ab0)
        return true;
    if (ksys::gdt::getFlag_IsGet_Obj_SheikSensor())
        return false;
    return sead::BitFlagUtil::countOnBit(u16(_120)) == 2;
}

// 0x710095f944: clears the map mode objects' state, runs the full UI state reset, then clears the
// selected-entry name and state of each map mode group.
void UiSubsys1::sub_710095F944() {
    for (auto& group : _30) {
        group._8 = -1;
        group._c = 0;
    }
    sub_710095F9D4();
    for (s32 i = 0; i < 5; ++i) {
        _d80[i].mSelected.mName.clear();
        _d80[i].mSelected._98 = -1;
    }
}

}  // namespace uking::ui


// NON_MATCHING: placeholder destructor; the original (0x710095606c) also destroys members or bases
// this class does not declare yet.
Unk_7102475e68::~Unk_7102475e68() = default;
