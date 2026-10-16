#include "Game/UI/uiUnk_7102506d38.h"
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiScreen.h"
#include "KingSystem/System/SeadController.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(Unk_7102506d38)

// 0x7101e79638: the per-mode button masks (box cursor modes 3 - 6)
static const u32 sUnk_7101E79638[4] = {0x00110000, 0x00220000, 0x00440000, 0x00880000};

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

// 0x710109e3f8
// NON_MATCHING: register allocation (box / controller land in the opposite saved registers) and the
// release-mode tail's compare interleaving differ; all calls, stores and flags match.
void Unk_7102506d38::sub_710109E3F8(ksys::SeadController* controller) {
    u32 flags = _30;
    _30 = flags & ~6;
    if (!controller)
        return;
    auto* box = eui::ScreenMgr::instance()->getBoxCursorMgr();
    if (!box)
        return;

    const u32 mode_flags = _2c;
    const u32 hold = controller->getHoldMask();
    if (hold & 0x8000) {
        if ((flags & 1) && !(mode_flags & 4)) {
            box->setEnable(eui::DrawTarget(0), false);
            box->setEnable(eui::DrawTarget(1), false);
            flags = _30;
            if (flags & 1)
                _30 = flags | 2;
            flags &= ~1;
            _30 = flags;
        }
    } else if (!(mode_flags & 4) &&
               ((mode_flags & 2) ||
                ((controller->getRepeatMask() | controller->getTrigMask()) & 0xff0000)) &&
               !(flags & 1)) {
        box->setEnable(eui::DrawTarget(0), true);
        box->setEnable(eui::DrawTarget(1), false);
        flags = _30;
        if (!(flags & 1))
            _30 = flags | 4;
        flags |= 1;
        _30 = flags;
    }

    if (!(_2c & 1) || !(_2c & 4) || (hold & 0x8000))
        box->m4(eui::BoxCursorMgr::Mode::_0);
    else
        box->sub_7100BDCD04(controller);

    if (_34 != 0) {
        _34 &= ~controller->getReleaseMask();
        const eui::BoxCursorMgr::Mode mode = box->mMode;
        u32 mask = 0;
        if (u32(int(mode) - 3) <= 3)
            mask = sUnk_7101E79638[int(mode) - 3];
        if ((_34 & mask) != 0)
            box->m4(eui::BoxCursorMgr::Mode::_0);
        if ((hold & _34) == 0)
            _34 = 0;
    }
}

void Unk_7102506d38::sub_710109E5C0(ksys::SeadController* controller) {
    if (_28)
        sub_710109E3F8(controller);
}

// 0x710109e5d0
void Unk_7102506d38::sub_710109E5D0(ksys::SeadController* controller) {
    if (!controller)
        return;
    auto* box = eui::ScreenMgr::instance()->getBoxCursorMgr();
    if (!box)
        return;
    _34 = controller->getHoldMask() & 0xff0000;
    if (_34 != 0)
        box->m4(eui::BoxCursorMgr::Mode::_0);
}

}  // namespace uking::ui
