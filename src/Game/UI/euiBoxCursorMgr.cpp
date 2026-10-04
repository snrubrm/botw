#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100bdca98
BoxCursorMgr::BoxCursorMgr() : mMode(0), mEnabledTargets(0) {}

// 0x7100bdccfc
void BoxCursorMgr::m4(s32 mode) {
    mMode = mode;
}

// 0x7100bdcb1c
void BoxCursorMgr::update() {
    m6(DrawTarget(0));
    m6(DrawTarget(1));
}

// 0x7100bdccc4
void BoxCursorMgr::setEnable(DrawTarget target, bool enable) {
    mEnabledTargets.changeBit(target, enable);
}

// 0x7100bdcdd0
void BoxCursorMgr::registerControl(DrawTarget target, BoxCursorControl* control) {
    mControls[target] = control;
}

// 0x7100bdcd80
void BoxCursorMgr::eraseNodeLinks(const BoxCursorNode* node) {
    mScreenMgr->eraseBoxCursorNodeFromRouteNodes(node);
    if (mControls[0])
        mControls[0]->clearActiveAndReservedActiveNode(node);
    if (mControls[1])
        mControls[1]->clearActiveAndReservedActiveNode(node);
}

}  // namespace eui
