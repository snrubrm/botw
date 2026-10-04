#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

namespace eui {

// 0x7100be97fc
void Screen::adjstBoxCursor(sead::BoundBox2<f32>*, const BoxCursorNode*) const {}

// 0x7100beaab4
void Screen::draw(const DrawInfoEx::RenderBufferInfo* info) {
    doDraw_(info);
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
s32 Screen::isEnableControl() const {
    return 0;
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
    mMgr->sub_7100BEC808(mId);
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
    return mLayout->mPane->FindPaneByName(name, true);
}

// 0x7100beb608
void Screen::moveBoxCursor_(BoxCursorNode* node) {
    if (BoxCursorMgr* mgr = mMgr->getBoxCursorMgr())
        mgr->m5(node);
}

}  // namespace eui
