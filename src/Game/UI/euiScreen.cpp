#include <controller/seadControllerMgr.h>
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiArcResourceMgr.h"
#include "Game/UI/euiMultiArcResourceAccessor.h"
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiConstantBuffer.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

#include <common/aglDrawContext.h>
#include "Game/UI/euiUIController.h"
#include "Game/UI/euiTagProcessor.h"

namespace eui {

// NON_MATCHING: only the order of the zero stores differs (the original stores 0xb8 first and 0xb0 late; we
// pair them).
// 0x7100be8f80
Screen::Screen() {
    mBoxCursorNodes.initOffset(offsetof(BoxCursorNode, mNode));
}

// 0x7100beaf8c
void Screen::x_2() {
    _105 = 1;
}

// 0x7100beacd8
TagProcessor* Screen::doCreateTagProcessor_(sead::Heap* heap) {
    return new (heap, 8) TagProcessor(mMgr->getMessageMgr(), mMgr->getFontMgr());
}

// NON_MATCHING: native iterator copies and redundant end-node checks remain in different form.
// 0x7100bea3d0
void Screen::updateAnimator_() {
    const f32 step = getAnimationStep_();
    for (ListNode* node = mAnimators.next; node != &mAnimators;) {
        Animator* animator = reinterpret_cast<Animator*>(reinterpret_cast<char*>(node) -
                                                        offsetof(Animator, _40));
        ListNode* next = node->next;
        animator->Animate();
        if (animator->mRate != 0 && animator->mEnabled) {
            animator->UpdateFrame(step);
        } else if (animator->mFlags & 2) {
            removeAnimator(animator);
            animator->mFlags &= 0xf0;
        } else {
            animator->nn::ui2d::AnimTransform::SetEnabled(false);
            animator->mRate = 0;
            animator->mLayout->m20(animator);
            const u8 flags = animator->mFlags;
            animator->mFlags = flags & 0xf0;
            if (flags & 1)
                animator->mFlags |= 2;
            else
                removeAnimator(animator);
        }
        node = next;
    }
}

// 0x7100bea36c
void Screen::updateControl_() {
    const f32 step = getAnimationStep_();
    for (ListNode* node = mControls.next; node != &mControls; node = node->next)
        ControlBase::fromNode(node)->Update(step);
}

// NON_MATCHING: the original tests the controller count with a signed compare (`cmp w8, #2; b.lt`) where the
// inlined PtrArray::at gives an unsigned one (`b.lo`); everything else is identical.
// 0x7100bea518
void Screen::registerController_() {
    auto* mgr = sead::ControllerMgr::instance();
    if (!isEnableControl())
        return;

    if (!_104) {
        mUIController->registerWith(sead::ControllerMgr::instance()->getController(0), true);
    } else {
        sead::Controller* controller = mgr->getController(1);
        if (!controller)
            return;
        mUIController->registerWith(controller, true);
    }
}

// 0x7100beab00
LayoutEx* Screen::doCreateLayout_(sead::Heap* heap) {
    return new (heap, 8) LayoutEx(this);
}

// 0x7100beab38
DrawInfoEx* Screen::doCreateDrawInfoEx_(sead::Heap* heap) {
    return new (heap, 16) DrawInfoEx;
}

// NON_MATCHING: only the register assignment of the first two loads differs (mMgr / mDrawInfo)
// 0x7100beabbc
void Screen::doSetupDrawInfo_() {
    mDrawInfo->mGraphicsResource = mMgr->getGraphicsResource();
    SetupDrawInfoOrtho(mDrawInfo, mLayout->GetLayoutSize());
    mMgr->getConstantBuffer()->applyToDrawInfo(mDrawInfo);
}

// 0x7100beac04
UIController* Screen::doCreateUIController_(sead::Heap* heap) {
    return new (heap, 8) UIController;
}

// 0x7100bea5b4
void Screen::unregisterController_() {
    if (isEnableControl()) {
        mUIController->unregister();
        mUIController->setIdle();
    }
}

// 0x71009cf574
void Screen::countEffectLinkPane_(nn::ui2d::Pane* pane, u32* count) {
    if (pane->FindExtUserDataByName("EffectLinkOn"))
        ++*count;
}

// 0x7100be97fc
void Screen::adjstBoxCursor(sead::BoundBox2<f32>*, const BoxCursorNode*) const {}

// 0x7100beac34
nn::ui2d::ResourceAccessor* Screen::doCreateResourceAccessor_(sead::Heap* heap) {
    auto* arc_resource_mgr = mMgr->getArcResourceMgr();
    auto* accessor =
        new (heap, 8) MultiArcResourceAccessor(arc_resource_mgr, mMgr->getFontMgr());
    if (auto* archive = arc_resource_mgr->findArcResource(getArchiveName_())) {
        accessor->attachArchive(archive->mData, archive->mTextureResource);
        return accessor;
    }
    return nullptr;
}

// 0x7100beaab4
void Screen::draw(const DrawInfoEx::RenderBufferInfo* info) {
    doDraw_(info);
}

// 0x7100beae20
void Screen::doDraw_(const DrawInfoEx::RenderBufferInfo* info) {
    if (!_100 || _102 || !mState || _ff == 2)
        return;
    mDrawInfo->_f8 = info;
    mLayout->Draw(*mDrawInfo, *info->mDrawContext->getCommandBuffer());
    mDrawInfo->freeDynamicTexture();
    mDrawInfo->_f8 = nullptr;
}

// 0x7100beaad8
const char* Screen::getMessageName_() const {
    return getLayoutName_();
}

// 0x7100beaaf0
bool Screen::isPlayPartsInOut_() const {
    return false;
}

// 0x7100beaaf8
bool Screen::isDisallowHitLowerScreenOnButtonHit_() const {
    return true;
}

// 0x7100bead18
void Screen::doLoadResource_(sead::Heap*) {}

// 0x7100beae0c
bool Screen::isForceGlbMtxDirty_() const {
    return false;
}

// 0x7100beaebc
void* Screen::getElinkSystem_() const {
    return nullptr;
}

// 0x7100beaecc
s32 Screen::getSlink2LocalPropertyNum_() const {
    return 0;
}

// 0x7100beaed4
void Screen::setSlink2PropertyDefinition_(xlink2::UserInstanceSLink*) {}

// 0x7100beabb8
void Screen::doAfterBuildLayout_(sead::Heap*) {}

// 0x7100beadf8
void Screen::doInitialize_(sead::Heap*) {}

// 0x7100be9df0
void Screen::doUpdate_() {}

// 0x7100beadfc
void Screen::doOpenStart_() {}

// 0x7100beae00
void Screen::doOpenEnd_() {}

// 0x7100beae04
void Screen::doCloseStart_() {}

// 0x7100beae08
void Screen::doCloseEnd_() {}

// 0x7100beae9c
void Screen::doButtonOnStart_(AnimButton*) {}

// 0x7100beaea0
void Screen::doButtonOnEnd_(AnimButton*) {}

// 0x7100beaea4
void Screen::doButtonOffStart_(AnimButton*) {}

// 0x7100beaea8
void Screen::doButtonOffEnd_(AnimButton*) {}

// 0x7100beaeac
void Screen::doButtonDownStart_(AnimButton*) {}

// 0x7100beaeb0
void Screen::doButtonDownEnd_(AnimButton*) {}

// 0x7100beaeb4
void Screen::doButtonCancelStart_(AnimButton*) {}

// 0x7100beaeb8
void Screen::doButtonCancelEnd_(AnimButton*) {}

// 0x7100beaac8
bool Screen::isEnableControl() const {
    return 0;
}

// 0x7100beafb0
LayoutEx* Screen::sub_7100BEAFB0(const char* name) {
    return mLayout->findPartsLayout(name);
}

// 0x7100beb12c
ControlBase* Screen::findControlWithParentLayout_(const char* name, const LayoutEx* layout) {
    const sead::SafeString search(name);
    for (ListNode* node = mControls.next; node != &mControls; node = node->next) {
        ControlBase* control = ControlBase::fromNode(node);
        if (search == sead::SafeString(control->mName) && control->mLayout->_88 == layout)
            return control;
    }
    return nullptr;
}

// 0x7100beb3dc
ControlBase* Screen::findControlWithLayout_(const char* name, const LayoutEx* layout) {
    const sead::SafeString search(name);
    for (ListNode* node = mControls.next; node != &mControls; node = node->next) {
        ControlBase* control = ControlBase::fromNode(node);
        if (search == sead::SafeString(control->mName) && control->mLayout == layout)
            return control;
    }
    return nullptr;
}

// 0x7100be9830
void Screen::addAnimator(Animator* animator) {
    mAnimators.linkPrev(&animator->_40);
}

// 0x7100be9850
void Screen::removeAnimator(Animator* animator) {
    if (&animator->_40 != &mAnimators)
        animator->_40.unlink();
}

// 0x7100be934c
bool Screen::isClosed() const {
    if (mState != 0)
        return false;
    return _fd < 1;
}

// 0x7100be9768
bool Screen::isOpened() const {
    if (mState != 2)
        return false;
    return _fd >= 0;
}

// 0x7100be978c
bool Screen::isOpening() const {
    if (mState == 1)
        return true;
    if (_fd < 1)
        return false;
    return mState == 0 || mState == 3;
}

// 0x7100be97c4
bool Screen::isClosedOrClosing() const {
    if (mState == 3)
        return true;
    if (_fd >= 0)
        return false;
    return mState == 1 || mState == 2;
}

// 0x7100be971c
void Screen::open(s32 option) {
    if (_fd <= option)
        _fd = option;
    mMgr->activateScreen(mId);
}

// 0x7100be973c
void Screen::close(s32 option) {
    if (_fd >= option)
        _fd = option;
    if (mState == 0)
        mMgr->inactivateScreen(mId);
}

// 0x7100be9880
void Screen::setOwnInitializeHeap(bool own) {
    _107 = own ? (_107 | 1) : (_107 & ~1);
}

// 0x7100be97f4
s32 Screen::getViewerType() const {
    return 0;
}

// 0x7100be99d4
DrawTarget Screen::getDrawTarget() const {
    return mMgr->getTargetMgr()->getDrawTarget(mDrawTarget);
}

// 0x7100be9da4
f32 Screen::getOpenFrameSize() const {
    Animator* animator = mLayout->mOpenAnimator;
    if (!animator)
        return 0;
    return animator->GetFrameSize();
}

// 0x7100bea710
void Screen::openStart_(s32 option) {
    if (_107 & 0x10)
        sub_7100BEE334(mLayout->GetPane(), mLayout);
    switch (option) {
    case 2:
        mLayout->startAnimCloseImpl_(isPlayPartsInOut_(), true);
        [[fallthrough]];
    case 1:
        mLayout->sub_7100BDDE7C(isPlayPartsInOut_(), 0, true);
        break;
    case 3:
        mLayout->sub_7100BDDE7C(isPlayPartsInOut_(), 1, true);
        break;
    case 4:
        mLayout->sub_7100BDDE7C(true, 2, true);
        break;
    }
    if (_e8)
        _e8->m3();
    if (_f0) {
        _f0->m2();
        if (option == 1 || option == 2)
            invokeSoundLink2Event_("open");
    }
    mState = 1;
    _ff = 0;
    _106 = 0;
    doOpenStart_();
}

// 0x7100bea8c0
void Screen::closeStart_(s32 option) {
    if (_e8)
        _e8->m4();
    _ff = 0;
    switch (option) {
    case -4:
        mLayout->startAnimCloseImpl_(isPlayPartsInOut_(), true);
        break;
    case -3:
        mLayout->startAnimCloseImpl_(isPlayPartsInOut_(), false);
        return;
    case -2:
        _ff = 1;
        mLayout->startAnimCloseImpl_(isPlayPartsInOut_(), false);
        break;
    case -1:
        mLayout->startAnimCloseImpl_(isPlayPartsInOut_(), false);
        if (_f0)
            invokeSoundLink2Event_("close");
        break;
    }
    mState = 3;
    unregisterController_();
    doCloseStart_();
}

// 0x7100beaa34
void Screen::closeEnd_() {
    if (_f0)
        _f0->m3();
    if (_ff == 0)
        mState = 0;
    else if (_ff == 1)
        _ff = 2;
    _fd = 0;
    doCloseEnd_();
    if (_107 & 0x10)
        sub_7100BEE4D4(mLayout->GetPane(), mLayout);
}

// 0x7100beaed8 (CSV Screen::x_1)
void Screen::setDrawTargetMaybe(u8 target) {
    mDrawTarget = target;
    mLayout->setDrawTargetAnim(mMgr->getTargetMgr()->getDrawTarget(target));
    if (_f0)
        _f0->setDrawTarget(getDrawTarget());
    if (mMgr->getScreenTarget(mId) >= 0)
        mMgr->activateScreen(mId);
}

// 0x7100be9dd4
void Screen::sub_7100BE9DD4(f32 frame) {
    if (Animator* animator = mLayout->mOpenAnimator)
        animator->Stop(frame);
}

// 0x7100beaad0
const char* Screen::getLayoutName_() const {
    return nullptr;
}

// 0x7100beaae4
const char* Screen::getArchiveName_() const {
    return getLayoutName_();
}

// 0x7100beaac0
const char* Screen::replacePartsLayoutName(const char* name, PartsEx*, LayoutEx*) {
    return name;
}

// 0x7100beae14
f32 Screen::getAnimationStep_() const {
    return mMgr->getAnimationStep();
}

// 0x7100beaec4
void* Screen::getSlink2ResourceList_(xlink2::UserInstanceSLink*) const {
    return nullptr;
}

// 0x7100bea854
bool Screen::isOpenEnd_() {
    return mLayout->isAnimOpenEnd(isPlayPartsInOut_());
}

// 0x7100beaa04
bool Screen::isCloseEnd_() {
    return mLayout->isAnimCloseEnd(isPlayPartsInOut_());
}

// 0x7100bea884
void Screen::openEnd_() {
    registerController_();
    mState = 2;
    doOpenEnd_();
}

// 0x7100beab88
ButtonGroup* Screen::doCreateButtonGroup_(sead::Heap* heap) {
    return new (heap) ButtonGroup;
}

// 0x7100beaf98
nn::ui2d::Pane* Screen::findPane_(const char* name) {
    return mLayout->GetPane()->FindPaneByName(name, true);
}

// 0x7100beb608
void Screen::moveBoxCursor_(BoxCursorNode* node) {
    if (BoxCursorMgr* mgr = mMgr->getBoxCursorMgr())
        mgr->m5(node);
}

// 0x7100be9800
BoxCursorNode* Screen::createBoxCursorNode(sead::Heap* heap) {
    return new (heap) BoxCursorNode;
}

// 0x7100be989c
void Screen::eraseBoxCursorNodeFromRouteNodes(const BoxCursorNode* node) {
    for (BoxCursorNode& route_node : mBoxCursorNodes)
        route_node.eraseNodeFromRouteNodes(node);
}

// 0x7100be9f60
u8 Screen::sub_7100BE9F60() const {
    return mMgr->getTargetFlag(mDrawTarget);
}

// 0x7100beb570
BoxCursorNode* Screen::findBoxCursorNodeByTag(s32 tag) {
    for (BoxCursorNode& node : mBoxCursorNodes) {
        if (node.mButton->mTag == tag)
            return &node;
    }
    return nullptr;
}

// 0x7100be9a04
BoxCursorNode* Screen::findBoxCursorNodeByButton(const AnimButton* button) {
    for (BoxCursorNode& node : mBoxCursorNodes) {
        if (node.mButton == button)
            return &node;
    }
    return nullptr;
}

// 0x7100beb518
void Screen::setReservedBoxCursorNode(BoxCursorNode* node) {
    _d8 = node;
}

// 0x7100beb520
void Screen::setReservedBoxCursorNodeByTag(s32 tag) {
    _d8 = findBoxCursorNodeByTag(tag);
}

// 0x7100beb5bc
void Screen::setReservedBoxCursorNodeByButton(const AnimButton* button) {
    _d8 = findBoxCursorNodeByButton(button);
}

// 0x7100be9908
bool Screen::moveBoxCursorByButton(const AnimButton* button) {
    BoxCursorMgr* mgr = mMgr->getBoxCursorMgr();
    if (!mgr)
        return false;
    if (!mgr->isTargetEnabled(getDrawTarget()))
        return false;
    if (BoxCursorNode* node = findBoxCursorNodeByButton(button)) {
        mgr->m5(node);
        return true;
    }
    return false;
}

// 0x7100beb624
void Screen::moveBoxCursorByTag_(s32 tag) {
    if (BoxCursorNode* node = findBoxCursorNodeByTag(tag)) {
        if (BoxCursorMgr* mgr = mMgr->getBoxCursorMgr())
            mgr->m5(node);
    }
}

// 0x7100beb690
void Screen::moveBoxCursorByButton_(const AnimButton* button) {
    if (BoxCursorNode* node = findBoxCursorNodeByButton(button)) {
        if (BoxCursorMgr* mgr = mMgr->getBoxCursorMgr())
            mgr->m5(node);
    }
}

}  // namespace eui
