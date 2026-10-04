#include "Game/UI/uiManager.h"

namespace uking::ui {

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
