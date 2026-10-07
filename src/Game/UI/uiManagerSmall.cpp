#include "Game/UI/uiManager.h"
#include "Game/UI/uiUnkSingletons.h"
#include "KingSystem/Utils/Thread/TaskThread.h"
#include "Game/UI/euiUIController.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

// UI heap storage; the name is a placeholder.
sead::Heap* sUnk_71025f59d0;

sead::Heap* getHeap() {
    return sUnk_71025f59d0;
}

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

// 0x7100a7f918
bool Manager::sub_7100A7F918() const {
    return _651f8 > 0;
}

// 0x71009686a0
void Unk_71025d6ac0::sub_71009686A0(s32 value) {
    _74 = value;
    _80 = 0;
}

// 0x71009686bc
void Unk_71025d6ac0::sub_71009686BC(s32 value) {
    _80 = 0;
    _84 = value * 2;
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

}  // namespace uking::ui
