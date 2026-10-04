#pragma once

#include <container/seadListImpl.h>
#include <container/seadSafeArray.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/UI/euiControlBase.h"
#include "Game/UI/euiTypes.h"

namespace nn::ui2d {
class ControlSrc;
class Pane;
}  // namespace nn::ui2d

namespace eui {

// 0x7100bed030
void CalcPaneBoundBox(sead::BoundBox2f* box, const nn::ui2d::Pane& pane);

class AnimButton;
class BoxCursorControl;
class LayoutEx;
class Screen;
class ScreenMgr;

// A button that the box cursor can select (CSV eui::BoxCursorNode; created by Screen::createBoxCursorNode, vtable
// 0x24c7cd0). The node is linked into Screen::mBoxCursorNodes through `mNode`; `mRoute` holds the neighbours.
class BoxCursorNode {
public:
    SEAD_RTTI_BASE(BoxCursorNode)

    BoxCursorNode();
    virtual ~BoxCursorNode() = default;

    // Slots 4-6
    virtual void initialize(AnimButton* button, Screen* screen);
    virtual bool isMovable(DrawTarget target) const;
    virtual bool isDecidable(DrawTarget target, bool b) const;

    // inline-only in the original; name is a guess. Evidence: moveNode_ keeps its Direction argument in a register for
    // getNodeByDirection_ while the route lookup spills a copy to the stack (a by-value parameter of an inlined helper).
    BoxCursorNode* getRoute(Direction direction) { return mRoute[direction]; }

    // 0x7100bdcf30
    void eraseNodeFromRouteNodes(const BoxCursorNode* node);
    // 0x7100bdd088
    void getPosition(sead::Vector2f* out) const;

    /* 0x08 */ sead::ListNode mNode;
    /* 0x18 */ AnimButton* mButton = nullptr;
    /* 0x20 */ Screen* mScreen = nullptr;
    /* 0x28 */ sead::SafeArray<BoxCursorNode*, 4> mRoute{};
};
static_assert(sizeof(BoxCursorNode) == 0x48);

// The box cursor of a screen (CSV eui::BoxCursorControl; vtable 0x24c7c48): four corner panes and the active node.
class BoxCursorControl : public ControlBase {
public:
    NN_RUNTIME_TYPEINFO(ControlBase)
    const char* getClassName() const override { return "BoxCursorControl"; }

    BoxCursorControl();
    ~BoxCursorControl() override;

    void Update(f32 dt) override;

    // 0x7100bdbd04
    void initialize(const nn::ui2d::ControlSrc& src, LayoutEx* layout);
    // 0x7100bdc028
    void updateActiveNode(DrawTarget target);
    // 0x7100bdc070
    void setActiveNode_(const BoxCursorNode* node);
    // 0x7100bdc0f8
    void moveNode_(Direction direction);
    // 0x7100bdc1e8 (placeholder name): presses the active node's button if the node is decidable
    void sub_7100BDC1E8(bool b);
    // 0x7100bdc66c (placeholder name)
    Screen* getActiveNodeScreen() const;
    // 0x7100bdc274
    void clearActiveAndReservedActiveNode(const BoxCursorNode* node);
    // 0x7100bdc2c8 / 0x7100bdc700 (not decompiled)
    void selectActiveNode_();
    BoxCursorNode* getNodeByDirection_(Direction direction);

    /* 0x28 */ nn::ui2d::Pane* mTopLeft = nullptr;
    /* 0x30 */ nn::ui2d::Pane* mTopRight = nullptr;
    /* 0x38 */ nn::ui2d::Pane* mBottomLeft = nullptr;
    /* 0x40 */ nn::ui2d::Pane* mBottomRight = nullptr;
    /* 0x48 */ BoxCursorNode* mActiveNode = nullptr;
    /* 0x50 */ BoxCursorNode* mReservedActiveNode = nullptr;
    /* 0x58 */ sead::Vector2f mPos = sead::Vector2f::zero;
};
static_assert(sizeof(BoxCursorControl) == 0x60);

// Owned by the ScreenMgr (at 0xb18; CSV eui::BoxCursorMgr, vtable 0x24c7c80 with sead-style RTTI).
class BoxCursorMgr {
public:
    SEAD_RTTI_BASE(BoxCursorMgr)

    BoxCursorMgr();
    virtual ~BoxCursorMgr() = default;
    // 0x7100bdccfc: stores the mode (values 3-6 move the cursor in the direction `mode - 3`)
    SEAD_ENUM(Mode, _0, _1, _2, _3, _4, _5, _6)
    virtual void m4(s32 mode);
    virtual void m5(BoxCursorNode* node);
    virtual void m6(DrawTarget target);
    virtual void update();

    // inline-only in the original; name is a guess (the DrawTarget argument is spilled to the stack by the inlined
    // by-value parameter, see BoxCursorControl::Update)
    bool isTargetEnabled(DrawTarget target) const { return mEnabledTargets.isOnBit(target); }

    // 0x7100bdccc4 / 0x7100bdcdd0 / 0x7100bdcd80
    void setEnable(DrawTarget target, bool enable);
    void registerControl(DrawTarget target, BoxCursorControl* control);
    void eraseNodeLinks(const BoxCursorNode* node);

    /* 0x08 */ ScreenMgr* mScreenMgr = nullptr;
    /* 0x10 */ Mode mMode;
    /* 0x14 */ sead::BitFlag8 mEnabledTargets;
    /* 0x18 */ sead::SafeArray<BoxCursorControl*, 2> mControls{};
};
static_assert(sizeof(BoxCursorMgr) == 0x28);

}  // namespace eui
