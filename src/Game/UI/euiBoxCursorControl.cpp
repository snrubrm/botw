#include <nn/ui2d/Pane.h>
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100bdbc08
BoxCursorControl::BoxCursorControl() = default;

// 0x7100bdbc54 (D1), 0x7100bdbca8 (D0)
BoxCursorControl::~BoxCursorControl() {
    Screen* screen = mLayout->mScreen;
    screen->mMgr->getBoxCursorMgr()->registerControl(screen->getDrawTarget(), nullptr);
}

// 0x7100bdbd04
void BoxCursorControl::initialize(const nn::ui2d::ControlSrc& src, LayoutEx* layout) {
    mLayout = layout;
    const char* mTopLeft_name = src.FindFunctionalPaneName("TopLeft");
    mTopLeft = layout->mPane->FindPaneByName(mTopLeft_name, true);
    const char* mTopRight_name = src.FindFunctionalPaneName("TopRight");
    mTopRight = layout->mPane->FindPaneByName(mTopRight_name, true);
    const char* mBottomLeft_name = src.FindFunctionalPaneName("BottomLeft");
    mBottomLeft = layout->mPane->FindPaneByName(mBottomLeft_name, true);
    const char* mBottomRight_name = src.FindFunctionalPaneName("BottomRight");
    mBottomRight = layout->mPane->FindPaneByName(mBottomRight_name, true);
    Screen* screen = mLayout->mScreen;
    screen->mMgr->getBoxCursorMgr()->registerControl(screen->getDrawTarget(), this);
    mLayout->mScreen->_107 |= 4;
}

// NON_MATCHING: regalloc only (the original loads the box as ldp min.x/min.y -> w8/w11 and ldp max.x/max.y -> w10/w9)
// 0x7100bdbe1c
void BoxCursorControl::Update(f32 dt) {
    Screen* screen = mLayout->mScreen;
    const DrawTarget target = screen->getDrawTarget();
    BoxCursorMgr* mgr = screen->mMgr->getBoxCursorMgr();
    if (!mgr->isTargetEnabled(target))
        return;

    if (!mActiveNode || !mActiveNode->isMovable(target))
        selectActiveNode_();

    if (!mActiveNode) {
        mActiveNode = nullptr;
        screen->close(-1);
        return;
    }

    if (mReservedActiveNode) {
        if (mReservedActiveNode->isMovable(target)) {
            BoxCursorNode* old_node = mActiveNode;
            BoxCursorNode* node = mReservedActiveNode;
            mActiveNode = node;
            if (old_node && old_node != node)
                old_node->mButton->InactivateByBoxCursor();
            if (node) {
                node->getPosition(&mPos);
                node->mScreen->mActiveCursorNode = node;
                if (old_node != node)
                    node->mButton->ActivateByBoxCursor();
            }
        }
        mReservedActiveNode = nullptr;
    }

    const BoxCursorMgr::Mode mode = mgr->mMode;
    if (mode >= 3)
        moveNode_(Direction(int(mode) - 3));

    sead::BoundBox2f box;
    CalcPaneBoundBox(&box, *mActiveNode->mButton->mBoxCursorPane);
    mActiveNode->mScreen->adjstBoxCursor(&box, mActiveNode);

    const sead::Vector2f min = box.getMin();
    const sead::Vector2f max = box.getMax();
    mTopLeft->SetPosition({min.x, max.y, 0});
    mTopRight->SetPosition({max.x, max.y, 0});
    mBottomLeft->SetPosition({min.x, min.y, 0});
    mBottomRight->SetPosition({max.x, min.y, 0});
    mActiveNode->getPosition(&mPos);
}

// 0x7100bdc1e8
void BoxCursorControl::sub_7100BDC1E8(bool b) {
    BoxCursorNode* node = mActiveNode;
    if (node && node->isDecidable(mLayout->mScreen->getDrawTarget(), b)) {
        AnimButton* button = mActiveNode->mButton;
        button->Down();
        button->mFlags = b ? (button->mFlags | 0x4000) : (button->mFlags & ~0x4000);
    }
}

// 0x7100bdc66c
Screen* BoxCursorControl::getActiveNodeScreen() const {
    return mActiveNode ? mActiveNode->mScreen : nullptr;
}

// 0x7100bdc274
void BoxCursorControl::clearActiveAndReservedActiveNode(const BoxCursorNode* node) {
    if (mActiveNode == node) {
        mActiveNode = nullptr;
        if (node)
            node->mButton->InactivateByBoxCursor();
    }
    if (mReservedActiveNode == node)
        mReservedActiveNode = nullptr;
}

// 0x7100bdc028
void BoxCursorControl::updateActiveNode(DrawTarget target) {
    if (mActiveNode && mActiveNode->isMovable(target))
        return;
    selectActiveNode_();
}

// 0x7100bdc070
void BoxCursorControl::setActiveNode_(const BoxCursorNode* node) {
    BoxCursorNode* old_node = mActiveNode;
    mActiveNode = const_cast<BoxCursorNode*>(node);
    if (old_node && old_node != node)
        old_node->mButton->InactivateByBoxCursor();
    if (node) {
        node->getPosition(&mPos);
        node->mScreen->mActiveCursorNode = const_cast<BoxCursorNode*>(node);
        if (old_node != node)
            node->mButton->ActivateByBoxCursor();
    }
}

// 0x7100bdc0f8
void BoxCursorControl::moveNode_(Direction direction) {
    BoxCursorNode* next = mActiveNode->getRoute(direction);
    if (next) {
        if (next == mActiveNode)
            return;
        if (!next->isMovable(mLayout->mScreen->getDrawTarget()))
            return;
    } else {
        next = getNodeByDirection_(direction);
        if (!next)
            return;
    }
    next->mScreen->_106 = 1;
    BoxCursorNode* old_node = mActiveNode;
    mActiveNode = next;
    if (old_node && old_node != next)
        old_node->mButton->InactivateByBoxCursor();
    next->getPosition(&mPos);
    next->mScreen->mActiveCursorNode = next;
    if (old_node != next)
        next->mButton->ActivateByBoxCursor();
}

}  // namespace eui
