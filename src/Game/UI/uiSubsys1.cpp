#include <limits>
#include <prim/seadBitFlag.h>
#include "Game/UI/uiUnkSingletons.h"

namespace uking::ui {

bool sub_7100A9C110(s32 value);

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

// 0x7100963704
void UiSubsys1::set128(s32 value) {
    _128 = value;
}

// 0x7100968af8: sets a bit of the 16-bit flag word at 0x3860
void UiSubsys1::sub_7100968AF8(s32 index) {
    _3860 |= 1 << u16(index);
    _3830 = 0;
}

// NON_MATCHING: same loop; the original walks the list with the constant node offset 8, OffsetList reads its runtime offset
// 0x71009512f8
UiSubsys1ListEntry* UiSubsys1::findListEntry(void* key) {
    if (!key)
        return nullptr;
    for (auto& entry : _280) {
        if (entry._0 == key)
            return &entry;
    }
    return nullptr;
}

// NON_MATCHING: same effect; the original erases the node with the constant offset 8
// 0x7100951338
bool UiSubsys1::freeListEntry(UiSubsys1ListEntry* entry) {
    if (!entry)
        return false;
    _280.erase(entry);
    entry->_0 = _298;
    _298 = entry;
    return true;
}

// 0x7100963c78
void UiSubsys1::sub_7100963C78(bool a1) {
    if (_378)
        _378->_50 = a1;
}

// 0x7100960df8
bool UiSubsys1::sub_7100960DF8() {
    return _3860 != 0;
}

// 0x7100960dac
bool UiSubsys1::sub_7100960DAC(s32 index) const {
    u16 lowest = _3860 != 0 ? sead::BitFlagUtil::countContinuousOffBitFromRight(_3860) : 6;
    return lowest == index;
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

// 0x7100962d8c (CSV uiSubsys1::__auto9)
u8 UiSubsys1::get38b8() const {
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
u8 UiSubsys1::get38ac() const {
    return _38ac;
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

}  // namespace uking::ui
