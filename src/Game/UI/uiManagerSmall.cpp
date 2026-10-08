#include "Game/UI/uiManager.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/Utils/Thread/TaskThread.h"
#include "Game/UI/euiUIController.h"
#include "Game/gameGraphics.h"
#include "Game/UI/uiUtils.h"
#include <devenv/seadEnvUtil.h>
#include <heap/seadExpHeap.h>

namespace uking::ui {

// 0x7100a7fe9c
void Manager::sub_7100A7FE9C() {
    _65387 = 0;
}

// 0x7100a7f0d0
// NON_MATCHING: the original omits the unused this argument of checkLoadResource.
void Manager::sub_7100A7F0D0() {
    mLocationResource.unload();
    if (checkLoadResource(&mLocationResource, "Map/MainField/Location.mubin"))
        parseLocations();
}

// UI heap storage; the name is a placeholder.
sead::Heap* sUnk_71025f59d0;

sead::Heap* getHeap() {
    return sUnk_71025f59d0;
}

// 0x7100a6d344
// NON_MATCHING: the original keeps the two region compares branchy (b.eq-big after the first,
// b.ne-small after the second); ours if-converts the second test to a csel. Tried the || form below,
// if/else-if/else and the nested !=/== form, all with the RegionID::US/EU names - the second test
// always becomes a csel. All loads/stores/calls match.
void createUiHeap(sead::Heap* parent) {
    size_t size;
    if (sead::EnvUtil::getRegion() == sead::RegionID::US ||
        sead::EnvUtil::getRegion() == sead::RegionID::EU) {
        size = 0x1c00000;
    } else {
        size = 0x1b00000;
    }
    sUnk_71025f59d0 = sead::ExpHeap::create(size, "UiHeap", parent, 8,
                                            sead::Heap::cHeapDirection_Forward, true);
    UI::instance()->_38 = sUnk_71025f59d0;
}

SEAD_SINGLETON_DISPOSER_IMPL(UiLowPrioThreadMgr)
SEAD_SINGLETON_DISPOSER_IMPL(Manager)

// 0x7100a6d978
void UiLowPrioThreadMgr::pause() {
    if (_28)
        _28->pause();
}

// 0x7100a6d988
void UiLowPrioThreadMgr::resume() {
    if (_28)
        _28->resume();
}

// 0x7100a6d998
void UiLowPrioThreadMgr::clearQueue() {
    if (_28)
        _28->clearQueue();
}

// 0x7100945320 / 0x7100945344: the two gauge ranges (value, maximum, default limit); names are guesses
void sub_7100945320(f32 value, f32 max) {
    Manager* manager = Manager::instance();
    manager->_50 = value;
    manager->_54 = max;
    manager->_58 = 3000.0f;
}

void sub_7100945344(f32 value, f32 max) {
    Manager* manager = Manager::instance();
    manager->_5c = value;
    manager->_60 = max;
    manager->_64 = 2000.0f;
}

// 0x7100a702e8 (CSV uiManager::x_1)
void Manager::sub_7100A702E8(eui::UIController* controller) {
    if (!controller)
        return;
    for (const auto& repeat : _649f8)
        controller->setPadRepeat(repeat.mask, repeat.delay_frame, repeat.pulse_frame);
}

// 0x7100a7f8e8
void Manager::sub_7100A7F8E8(const Unk_UiPinInfo* info) {
    if (info)
        _651e0 = info->_20;
}

// 0x7100a7f900
void Manager::sub_7100A7F900(Unk_UiPinInfo* info) const {
    if (info)
        info->_20 = _651e0;
}

// 0x7100a7f81c
bool Manager::sub_7100A7F81C() {
    auto lock = sead::makeScopedLock(_650f8);
    if (_650f0 > 0)
        return false;
    _650f0 = 1;
    Graphics::instance()->sub_7100F35DE8();
    return true;
}

// 0x7100a7f890
void Manager::sub_7100A7F890() {
    if (_651c4)
        _651ac.reset();
    _651c4 = true;
}

// 0x7100a7f8d4
void Manager::sub_7100A7F8D4() {
    _651c8.init(15.0f);
}

// 0x7100a7f918
bool Manager::sub_7100A7F918() const {
    return _651f8 > 0;
}

f32 Unk_71025d6ac0::sub_7100968558() const {
    return 0.01f;
}

bool Unk_71025d6ac0::sub_71009686E8() const {
    return false;
}

// 0x71009686a0
bool Unk_71025d6ac0::sub_71009685AC(s32 value) const {
    return _74 == value;
}

void Unk_71025d6ac0::sub_71009686A0(s32 value) {
    _74 = value;
    _80 = 0;
}

// 0x71009686bc
void Unk_71025d6ac0::sub_71009686BC(s32 value) {
    _80 = 0;
    _84 = value * 2;
}

void Unk_71025d6ac0::sub_71009686AC() {
    _74 = 1;
    _80 = 0;
}

void Unk_71025d6ac0::sub_71009686C8() {
    ++_80;
}

bool Unk_71025d6ac0::sub_71009686D8() const {
    return _80 == _84;
}

// 0x7100a7fd64
// NON_MATCHING: the original reloads the count after the pointer store (it assumes the store may alias the count: no
// type-based aliasing between them), ours (also as sead::PtrArray::pushBack) increments it from the value already loaded.
void Manager::sub_7100A7FD64(nn::ui2d::Pane* pane) {
    if (pane && _652f0 < _652f4)
        _652f8[_652f0++] = pane;
}

// 0x7100a7fdb4
bool Manager::sub_7100A7FDB4() const {
    return _65387 != 0;
}

// 0x7100a76420 (CSV nullsub_6139)
void Manager::sub_7100A76420() {}

// 0x7100a79968
void Manager::sub_7100A79968() {
    switch (_64c2c) {
    case 2:
        sub_7100A79A04();
        _64c2c = 3;
        break;
    case 4:
        if (!sub_7100A79B38())
            return;
        _64c2c = 5;
        break;
    }
    if (!isPausedMaybe())
        _cc = -1;
}

// 0x7100a7a6e4
void Manager::sub_7100A7A6E4(s32 a1) {
    _64b0c |= 1 << a1;
}

// 0x7100a7a704
void Manager::sub_7100A7A704(s32 a1) {
    if (a1 == 6)
        return;
    _64b10 |= 1 << a1;
}

// 0x7100a7c8d4
void Manager::sub_7100A7C8D4() {
    sub_7100AA8698();
    _64c28 = 1;
    _64c2c = 1;
}

// 0x7100a7c9ac
void Manager::sub_7100A7C9AC() {
    _64c2c = 8;
}

// 0x7100a7fba4
void Manager::sub_7100A7FBA4() {
    _65218 = _64c38 == 7;
}

// 0x7100a7fdac
bool Manager::sub_7100A7FDAC() {
    return false;
}

// 0x7100a7a4c0
void Manager::sub_7100A7A4C0() {
    sub_7100A7A4C4();
}

}  // namespace uking::ui
