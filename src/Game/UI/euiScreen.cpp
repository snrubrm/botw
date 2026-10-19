#include <controller/seadController.h>
#include <controller/seadControllerMgr.h>
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiArcResourceMgr.h"
#include "Game/UI/euiMultiArcResourceAccessor.h"
#include "Game/UI/euiNwAllocator.h"
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiConstantBuffer.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiPartsEx.h"
#include "Game/UI/euiScreen.h"

#include <common/aglDrawContext.h>
#include "Game/UI/euiUIController.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/euiControlCreator.h"
#include "Game/UI/euiTextSearcher.h"
#include "Game/UI/euiMessageMgr.h"
#include <gfx/nin/seadGraphicsNvn.h>
#include <nn/ui2d/BuildTypes.h>

namespace eui {

// 0x7100bead1c
// NON_MATCHING: the original inlines the creator destructor; an inline ControlCreator destructor drops the
// out-of-line D1 at 0x7100bd8c20 (clang aliases it to the SDK base D2).
void Screen::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    ControlCreator creator(mButtonGroup, &mControls, &_50);
    auto* messages = mMgr->getMessageMgr()->getLayoutMessageSet(getMessageName_());
    TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
}

// 0x7100be8f80
Screen::Screen() {
    mBoxCursorNodes.initOffset(offsetof(BoxCursorNode, mNode));
    _a0.initOffset(0);
}

// 0x7100be9050
Screen::~Screen() {
    if (mId != -1)
        mMgr->resetScreenId(mId);

    if (auto* box_cursor_mgr = mMgr->getBoxCursorMgr()) {
        for (auto& node : mBoxCursorNodes)
            box_cursor_mgr->eraseNodeLinks(&node);
    }

    for (ListNode* node = mControls.next; node != &mControls; node = node->next)
        ControlBase::fromNode(node)->~ControlBase();
    for (ListNode* node = _50.next; node != &_50; node = node->next)
        ControlBase::fromNode(node)->~ControlBase();

    if (_e8)
        _e8->m2();
    if (_f0)
        _f0->m1();

    if (mLayout && (_107 & 0x12) == 0x10 && !isClosed())
        sub_7100BEE4D4(mLayout->GetPane(), mLayout);

    for (auto& item : _a0) {
        if (item._10)
            item._10->m2();
        item._10 = nullptr;
    }

    if (!mLayout)
        return;
    nn::ui2d::ResourceAccessor* accessor = mLayout->mResourceAccessor;
    if ((_107 & 0xa) == 2) {
        NwAllocator::initialize(mInitializeHeap);
        mLayout->Finalize(sead::GraphicsNvn::instance()->getNnDevice());
        delete mLayout;
        NwAllocator::finalize();
        mLayout = nullptr;
    }
    if (accessor) {
        accessor->UnregisterTextureViewFromDescriptorPool(UnregisterSlotForTexture, nullptr);
        NwAllocator::initialize(mInitializeHeap);
        if (nn::font::DynamicCast<MultiArcResourceAccessor>(accessor))
            accessor->Finalize(sead::GraphicsNvn::instance()->getNnDevice());
        NwAllocator::finalize();
    }
}

// 0x7100beaf8c
void Screen::x_2() {
    _105 = 1;
}

// 0x7100beacd8
TagProcessor* Screen::doCreateTagProcessor_(sead::Heap* heap) {
    return new (heap, 8) TagProcessor(mMgr->getMessageMgr(), mMgr->getFontMgr());
}

// 0x7100be9390
void Screen::initialize(ScreenMgr* mgr, sead::Heap* heap, const char* name, s32 id,
                        s8 target, bool touch_device) {
    mMgr = mgr;
    mInitializeHeap = heap;
    mId = id;
    mDrawTarget = target;
    _c8 = sead::SafeString(name);
    _100 = 1;
    _104 = touch_device;
    mDrawInfo = doCreateDrawInfoEx_(heap);
    mButtonGroup = doCreateButtonGroup_(heap);
    mButtonGroup->SetTouchDevice(touch_device);
    NwAllocator::initialize(heap);
    mLayout = doCreateLayout_(heap);
    if (isEnableControl())
        mUIController = doCreateUIController_(heap);
    auto* accessor = doCreateResourceAccessor_(heap);
    mTagProcessor = doCreateTagProcessor_(heap);

    sead::Graphics::instance()->lockDrawContext();
    {
        sead::FixedSafeString<72> layout_name;
        layout_name.format("%s.bflyt", getLayoutName_());
        doBuildLayout_(layout_name, accessor);
        accessor->RegisterTextureViewToDescriptorPool(RegisterSlotForTexture, nullptr);
        doAfterBuildLayout_(heap);
    }
    sead::Graphics::instance()->unlockDrawContext();

    u32 count = 0;
    sub_7100BE9688(mLayout->GetPane(), mLayout, &count);
    createSoundLink2User_(heap);
    const f32 step = getAnimationStep_();
    for (ListNode* node = _50.next; node != &_50; node = node->next)
        ControlBase::fromNode(node)->Update(step);
    doSetupDrawInfo_();
    doLoadResource_(heap);
    sead::Graphics::instance()->lockDrawContext();
    doInitialize_(heap);
    sead::Graphics::instance()->unlockDrawContext();
    createEffectLinkUser_(heap, count);
    accessor->RegisterTextureViewToDescriptorPool(RegisterSlotForTexture, nullptr);
    NwAllocator::finalize();
}

// 0x7100be9a54
// NON_MATCHING: state-byte loads and callback branches are scheduled differently.
void Screen::update() {
    const s32 open_request = _fd;
    const u8 paused = _103;
    if (open_request > 0) {
        _fd = 0;
        if (open_request == 2 || mState == 3 || mState == 0) {
            openStart_(open_request);
            if (open_request == 4)
                openEnd_();
        } else if (open_request == 3 && mState == 1) {
            mLayout->sub_7100BDDE7C(isPlayPartsInOut_(), 1, true);
        }
    }
    if (mState == 1 && isOpenEnd_())
        openEnd_();
    if (!paused) {
        doUpdate_();
        updateButton_();
    }
    if (mButtonGroup->_28 && isDisallowHitLowerScreenOnButtonHit_())
        mMgr->mTargetFlags[mMgr->mTargetMgr->getDrawTarget(mDrawTarget)] = false;
    if (!paused)
        updateControl_();
    const s32 close_request = _fd;
    if (close_request < 0) {
        _fd = 0;
        if (mState == 1 || mState == 2)
            closeStart_(close_request);
        else if (close_request == -4 && mState == 3)
            mLayout->startAnimCloseImpl_(isPlayPartsInOut_(), true);
    }
    if (mState == 3 && isCloseEnd_() && _ff != 2) {
        if (_ff == 0 && _fd <= 0)
            mMgr->inactivateScreen(mId);
        closeEnd_();
    }
    if (_e8)
        _e8->m0();
    if (!paused)
        updateAnimator_();
    if (_105 && (_107 & 0x10)) {
        sub_7100BEE240(mLayout->GetPane());
        _105 = 0;
    }
    if (!_101) {
        mDrawInfo->_eb[6] |= 2;
        mDrawInfo->_eb[6] |= 4;
    }
    // The virtual force-dirty query may change these fields; calculation uses the saved objects.
    auto* layout = mLayout;
    auto* draw_info = mDrawInfo;
    const bool force_dirty = isForceGlbMtxDirty_();
    layout->CalculateImpl(*draw_info, force_dirty);
    if (!_101) {
        mDrawInfo->_eb[6] &= ~2;
        mDrawInfo->_eb[6] &= ~4;
        _101 = 1;
    }
    if (_e8)
        _e8->m1();
    if (_f0)
        _f0->m0();
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
// Passes the touch position (in layout coordinates; on a touch device scaled from the 854x480 touch
// screen to the 1280x720 layout) and the touch states to the button group.
void Screen::updateButton_() {
    if (!isEnableControl())
        return;

    constexpr u32 cTouch = 1 << sead::Controller::cPadIdx_Touch;
    if (mUIController->isPointerOn() && mMgr->getTargetFlag(mDrawTarget)) {
        const nn::font::Rectangle rect = mLayout->GetLayoutRect();
        const auto* controller = mUIController;
        const sead::Vector2f& pointer = controller->getPointer();
        f32 x;
        f32 y;
        if (_104) {
            x = pointer.x / 854.0f * 1280.0f + (rect.right - rect.left) * -0.5f;
            y = pointer.y / 480.0f * -720.0f;
        } else {
            x = pointer.x + (rect.right - rect.left) * -0.5f;
            y = -pointer.y;
        }
        const sead::Vector2f pos{x, y + (rect.bottom - rect.top) * -0.5f};
        mButtonGroup->m2(&pos, controller->isTrig(cTouch), controller->isRelease(cTouch),
                         controller->isRepeat(cTouch));
        return;
    }

    mButtonGroup->m2(nullptr, false, mUIController->isRelease(cTouch), false);
}

void Screen::updateControl_() {
    const f32 step = getAnimationStep_();
    for (ListNode* node = mControls.next; node != &mControls; node = node->next)
        ControlBase::fromNode(node)->Update(step);
}

// 0x7100bea704
void Screen::sub_7100BEA704(Screen* screen, xlink2::UserInstanceSLink* link) {
    screen->setSlink2PropertyDefinition_(link);
}

// 0x7100be9688
void Screen::sub_7100BE9688(nn::ui2d::Pane* pane, LayoutEx* layout, u32* count) {
    if (auto* parts = sub_7100BDD310(pane))
        layout = static_cast<LayoutEx*>(parts->mPartsLayoutLink.layout);
    setupPaneAfterBuild_(pane, layout, count);
    for (auto& child : pane->GetChildList())
        sub_7100BE9688(&child, layout, count);
}

// 0x7100bea690
void Screen::sub_7100BEA690(nn::ui2d::Pane* pane, LayoutEx* layout) {
    if (auto* parts = sub_7100BDD310(pane))
        layout = static_cast<LayoutEx*>(parts->mPartsLayoutLink.layout);
    AdjustPaneSizeToTextSize(pane, layout);
    for (auto& child : pane->GetChildList())
        sub_7100BEA690(&child, layout);
}

// 0x7100beb6f8
void Screen::sub_7100BEB6F8(LayoutEx* layout) {
    sub_7100BEA690(layout->mPane, layout);
}

// 0x7100bea600
void Screen::setupPaneAfterBuild_(nn::ui2d::Pane* pane, LayoutEx* layout, u32* count) {
    sub_7100BEFA30(pane, layout);
    sub_7100BEFE9C(pane, layout, mButtonGroup);
    sub_7100BF01DC(pane, layout, mButtonGroup);
    if (auto* text_box = sub_7100933580(pane))
        text_box->m48(&mControls, layout);
    countEffectLinkPane_(pane, count);
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

// 0x7100be9fa8
// NON_MATCHING: branch layout and inlined RTTI traversal differ.
void Screen::buttonStateChangeCallback(AnimButton* button, ButtonBase::State old_state,
                                       ButtonBase::State new_state) {
    switch (old_state) {
    case ButtonBase::kStartOn:
        doButtonOnEnd_(button);
        break;
    case ButtonBase::kStartOff:
        doButtonOffEnd_(button);
        break;
    case ButtonBase::kStartDown:
        doButtonDownEnd_(button);
        break;
    case ButtonBase::kCancel:
        doButtonCancelEnd_(button);
        break;
    default:
        break;
    }

    switch (new_state) {
    case ButtonBase::kStartOn:
        doButtonOnStart_(button);
        if (_f0) {
            if (!_106)
                _106 = true;
            else if (!button->IsDowning())
                invokeSoundLink2ButtonEvent_(button, "_on");
        }
        break;
    case ButtonBase::kStartOff:
        doButtonOffStart_(button);
        break;
    case ButtonBase::kCancel:
        doButtonCancelStart_(button);
        break;
    case ButtonBase::kStartDown: {
        doButtonDownStart_(button);
        if (!_f0)
            break;
        _f0->setButtonProperty(button->_39);
        if (button->IsPlayDisableAnim()) {
            invokeSoundLink2ButtonEvent_(button, "_noeffect");
            break;
        }

        bool handled = false;
        if (nn::font::DynamicCast<CheckKeepButton>(button)) {
            invokeSoundLink2ButtonEvent_(button, "_check");
            handled = true;
        } else if (auto* check = nn::font::DynamicCast<CheckButton>(button)) {
            if (check->mToggleable) {
                invokeSoundLink2ButtonEvent_(button, check->mChecked ? "_check" : "_uncheck");
                handled = true;
            }
        }

        if (auto* unite = nn::font::DynamicCast<UniteButton>(button)) {
            if (unite->mType == UniteButton::Type::CheckButton) {
                invokeSoundLink2ButtonEvent_(button, unite->mChecked ? "_check" : "_uncheck");
                break;
            }
            if (unite->mType == UniteButton::Type::CheckKeepButton && !unite->mChecked) {
                invokeSoundLink2ButtonEvent_(button, "_check");
                break;
            }
        }
        if (!handled)
            invokeSoundLink2ButtonEvent_(button, "_decide");
        break;
    }
    default:
        break;
    }
}

// 0x7100beaac8
bool Screen::isEnableControl() const {
    return 0;
}

// 0x7100beafb0
LayoutEx* Screen::sub_7100BEAFB0(const char* name) {
    return mLayout->findPartsLayout(name);
}

// 0x7100beb26c
ControlBase* Screen::findControlWithParts_(const char* name, const char* parts_name) {
    const sead::SafeString search(name);
    for (ListNode* node = mControls.next; node != &mControls; node = node->next) {
        ControlBase* control = ControlBase::fromNode(node);
        LayoutEx* layout = control->mLayout;
        if (search == sead::SafeString(control->mName) && layout &&
            IsNameEqual(parts_name, layout->mPane->GetName()))
            return control;
    }
    return nullptr;
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
bool Screen::sub_7100BE9F60() const {
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

void Screen::sub_7100BEB70C() { _106 = 0; }

// 0x7100a52150 (CSV placeholder): find the LetterAnimControl with the given pane name.
LetterAnimControl* Screen::sub_7100A52150(const char* name) {
    const sead::SafeString query(name);
    for (ListNode* node = mControls.next; node != &mControls; node = node->next) {
        ControlBase* control = ControlBase::fromNode(node);
        auto* letter = nn::font::DynamicCast<LetterAnimControl>(control);
        if (letter != nullptr && query.isEqual(letter->mName))
            return letter;
    }
    return nullptr;
}

}  // namespace eui
