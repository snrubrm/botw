#include <container/seadBuffer.h>
#include <limits>
#include <prim/seadBitFlag.h>
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameSceneMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "Game/gameUnkRttiPlaceholders.h"

namespace uking::ui {

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

// 0x71025d6ca4: the layout screen size (written by the initialiser at 0x710094f9e4)
static sead::Vector2f sUnk_71025d6ca4{1280.0f, 720.0f};

// 0x7100966008
// NON_MATCHING: the original addresses sUnk_71025d6ca4 through the TU's merged globals
const sead::Vector2f* sub_7100966008() {
    return &sUnk_71025d6ca4;
}

// 0x7100966018
// NON_MATCHING: the original addresses sUnk_71025d6ca4 through the TU's merged globals
void sub_7100966018(sead::Vector2f* out) {
    *out = sUnk_71025d6ca4 * 0.5f;
}

// 0x710096603c
// NON_MATCHING: the original addresses sUnk_71025d6ca4 through the TU's merged globals
void UiSubsys1::sub_710096603C(sead::Vector2f* out) const {
    const f32 scale = 1.0f / _850._28;
    *out = {scale * sUnk_71025d6ca4.x, scale * sUnk_71025d6ca4.y};
}

// 0x7100966064
// NON_MATCHING: the original addresses sUnk_71025d6ca4 through the TU's merged globals
void UiSubsys1::sub_7100966064(sead::Vector2f* out) const {
    const f32 scale = 1.0f / _850._38;
    *out = {scale * sUnk_71025d6ca4.x, scale * sUnk_71025d6ca4.y};
}

// 0x7100965ea8
s32 UiSubsys1::sub_7100965EA8() const {
    return _84c;
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
u8 UiSubsys1::get38c8() const {
    return _38c8;
}

// 0x7100966e9c
bool UiSubsys1::get38d8() const {
    return _38d8;
}

// 0x7100967478
u8 UiSubsys1::get38d9() const {
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
    return _3820;
}

// 0x7100968824 (CSV uiSubsys1::__auto1)
sead::Vector3f* UiSubsys1::getVec3834() {
    return &_3834;
}

// 0x7100968830 (CSV uiSubsys1::__auto19)
void UiSubsys1::resetVec3834() {
    _3834.set(0.0f, 0.0f, 1.0f);
}

// 0x7100968cf8 (CSV uiSubsys1::__auto40)
u8 UiSubsys1::get3858() const {
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

// NON_MATCHING: only the operand order of the final `and` differs (the original ands the (value - 6 < 5) flag first)
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
void UiSubsys1::set6e4(s32 value) {
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

// 0x71025d6e58: a .bss float buffer read by sub_7100965960 (no writer found in this TU)
static sead::Buffer<f32> sUnk_71025d6e58;

// 0x7100965960: entry of sUnk_71025d6e58 for an index 0-3, or -1 for any other index
// NON_MATCHING: the original reaches the buffer through merged TU globals (base 0x71025d6c70 + 0x1e8)
f32 sub_7100965960(s32 index) {
    if (index < 0 || index > 3)
        return -1.0f;
    return sUnk_71025d6e58[index];
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
    _3820 = value;
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

}  // namespace uking::ui


// NON_MATCHING: placeholder destructor; the original (0x710095606c) also destroys members or bases
// this class does not declare yet.
Unk_7102475e68::~Unk_7102475e68() = default;
