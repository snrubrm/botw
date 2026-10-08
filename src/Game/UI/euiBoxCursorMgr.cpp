#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100bdca98
BoxCursorMgr::BoxCursorMgr() : mMode(0), mEnabledTargets(0) {}

// 0x7100bdccfc
void BoxCursorMgr::m4(Mode mode) {
    mMode = mode;
}

// 0x7100bdcb1c
void BoxCursorMgr::update() {
    m6(DrawTarget(0));
    m6(DrawTarget(1));
}

// 0x7100bdcac0
void BoxCursorMgr::m5(BoxCursorNode* node) {
    Screen* screen = node->mScreen;
    if (!screen)
        return;
    BoxCursorControl* control = mControls[screen->getDrawTarget()];
    if (control) {
        control->mReservedActiveNode = node;
        screen->mActiveCursorNode = node;
    }
}

// 0x7100bdcb58
void BoxCursorMgr::m6(DrawTarget target) {
    BoxCursorControl* control = mControls[target];
    if (!control)
        return;
    Screen* screen = control->mLayout->mScreen;
    const bool enabled = isTargetEnabled(target);
    const bool closed = screen->isClosed();
    if (enabled) {
        if (closed) {
            control->updateActiveNode(target);
            if (!control->mActiveNode)
                return;
            screen->open(1);
        }
        const s32 mode = mMode;
        if (mode == 1 || mode == 2)
            control->sub_7100BDC1E8(mode == 2);
    } else if (!closed) {
        control->setActiveNode_(nullptr);
        screen->close(-1);
    }
}

// 0x7100bdcc60
Screen* BoxCursorMgr::getActiveNodeScreen(DrawTarget target) const {
    if (BoxCursorControl* control = mControls[target])
        return control->getActiveNodeScreen();
    return nullptr;
}

// 0x7100bdcc90
bool BoxCursorMgr::sub_7100BDCC90(DrawTarget target, const sead::SafeString& name) const {
    if (BoxCursorControl* control = mControls[target])
        return control->sub_7100BDC684(name);
    return false;
}

// 0x7100bdcd04
void BoxCursorMgr::sub_7100BDCD04(const sead::Controller* controller) {
    const u32 trig = controller->getTrigMask();
    Mode mode;
    if (trig & 1) {
        mode = 1;
    } else {
        const u32 repeat = controller->getRepeatMask();
        const u32 buttons = trig | repeat;
        mode = (repeat & 1)           ? 2 :
               (buttons & 0x110000) ? 3 :
               (buttons & 0x220000) ? 4 :
               (buttons & 0x440000) ? 5 :
               (buttons & 0x880000) ? 6 :
                                      0;
    }
    m4(mode);
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
