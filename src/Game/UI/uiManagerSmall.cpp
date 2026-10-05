#include "Game/UI/uiManager.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

// UI heap storage; the name is a placeholder.
sead::Heap* sUnk_71025f59d0;

sead::Heap* getHeap() {
    return sUnk_71025f59d0;
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

// 0x7100a7f918
bool Manager::sub_7100A7F918() const {
    return _651f8 > 0;
}

// 0x7100a7fdb4
bool Manager::sub_7100A7FDB4() const {
    return _65387 != 0;
}

// 0x7100a76420 (CSV nullsub_6139)
void Manager::sub_7100A76420() {}

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
