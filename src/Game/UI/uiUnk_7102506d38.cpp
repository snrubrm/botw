#include "Game/UI/uiUnk_7102506d38.h"
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiScreen.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(Unk_7102506d38)

// D1 0x710109e2c4, D0 0x710109e2c8
Unk_7102506d38::~Unk_7102506d38() = default;

// 0x710109e2cc
void Unk_7102506d38::sub_710109E2CC() {
    if (auto* cursor = eui::ScreenMgr::instance()->getBoxCursorMgr()) {
        cursor->setEnable(eui::DrawTarget(0), true);
        cursor->setEnable(eui::DrawTarget(1), false);
        if (!(_30 & 1))
            _30 |= 4;
        _30 |= 1;
    }
    _30 &= ~6;
    _2c |= 7;
}

// 0x710109e350
void Unk_7102506d38::sub_710109E350(bool enable) {
    if (auto* cursor = eui::ScreenMgr::instance()->getBoxCursorMgr()) {
        cursor->setEnable(eui::DrawTarget(0), enable);
        cursor->setEnable(eui::DrawTarget(1), false);
        // NON_MATCHING: same instructions; the final `orr` of the original has its operands swapped (`orr w8, w8, w9`).
        const bool is_on = _30 & 1;
        if (!enable && is_on)
            _30 |= 2;
        else if (enable && !is_on)
            _30 |= 4;
        if (enable)
            _30 |= 1;
        else
            _30 &= ~1;
    }
}

void Unk_7102506d38::sub_710109E5C0(ksys::SeadController* controller) {
    if (_28)
        sub_710109E3F8(controller);
}

}  // namespace uking::ui
