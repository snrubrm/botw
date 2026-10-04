#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiScreen.h"
#include <nn/ui2d/Pane.h>

namespace eui {

// 0x7100bdcec0
BoxCursorNode::BoxCursorNode() = default;

// 0x7100bdceec
void BoxCursorNode::initialize(AnimButton* button, Screen* screen) {
    mButton = button;
    mScreen = screen;
    if (screen)
        screen->mBoxCursorNodes.pushBack(this);
}

// 0x7100bdcf30
void BoxCursorNode::eraseNodeFromRouteNodes(const BoxCursorNode* node) {
    for (BoxCursorNode*& route : mRoute.mBuffer) {
        if (route == node)
            route = nullptr;
    }
}

// 0x7100bdcf74
bool BoxCursorNode::isMovable(DrawTarget target) const {
    Screen* screen = mScreen;
    if (screen->isOpened() && (screen->mButtonGroup->_38 & 2)) {
        if (mButton->mFlags & 0x10)
            return int(screen->getDrawTarget()) == int(target);
    }
    return false;
}

// 0x7100bdcff0
bool BoxCursorNode::isDecidable(DrawTarget target, bool b) const {
    Screen* screen = mScreen;
    bool result = false;
    if (screen->isOpened() && (screen->mButtonGroup->_38 & 2) && (mButton->mFlags & 0x10) &&
        int(screen->getDrawTarget()) == int(target)) {
        if (!b || (mButton->mFlags & 0x80))
            result = !screen->mButtonGroup->IsExistExcludingDown();
    }
    return result;
}

// 0x7100bdd088
void BoxCursorNode::getPosition(sead::Vector2f* out) const {
    const auto& mtx = mButton->mBoxCursorPane->GetMtx();
    *out = {mtx.m[0][3], mtx.m[1][3]};
}

}  // namespace eui
