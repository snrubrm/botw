#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiButton.h"
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiTagProcessor.h"
#include <controller/seadController.h>
#include "KingSystem/System/SeadController.h"

namespace eui {

// 0x7100be9a4c (CSV eui::Screen::x)
void Screen::m13() {}

// 0x7100be9a50 (CSV eui::Screen::x_0; vtable slot 0x71024c8ee0)
void Screen::m14() {}

}  // namespace eui

namespace uking::ui {

// 0x71010aa3b0
Screen::Screen() : mTransceiver(this, sUnk_710261ee98), _1e0(*this) {
    _291 = 0;
    _292 = 0xfe7f;
    _298.clear();
}

// 0x71010aa54c
// NON_MATCHING: the inlined Unk_7102474a28 teardown takes the adapter address after getDispatcher().
Screen::~Screen() {
    for (auto it = mChildList.begin(); it != mChildList.end();) {
        auto child = it++;
        mChildList.erase(child);
        delete &*child;
    }
    mChildren.freeBuffer();
    mChildGroupSizes.freeBuffer();
}

// 0x71010a9f04
void ScreenBase::updateButton_() {
    if (!isEnableControl())
        return;

    if (!_104) {
        mButtonGroup->m2(nullptr, false, false, false);
        return;
    }

    constexpr u32 cTouch = 1 << sead::Controller::cPadIdx_Touch;
    if (mUIController->isPointerOn() && sub_7100BE9F60()) {
        const nn::font::Rectangle rect = mLayout->GetLayoutRect();
        const auto* controller = mUIController;
        const sead::Vector2f pos{controller->getPointer().x * (rect.right - rect.left) * 0.5f,
                                 controller->getPointer().y * (rect.bottom - rect.top) * -0.5f};
        mButtonGroup->m2(&pos, controller->isTrig(cTouch), controller->isRelease(cTouch),
                         controller->isRepeat(cTouch));
        return;
    }

    mButtonGroup->m2(nullptr, false, mUIController->isRelease(cTouch), false);
}

eui::TagProcessor* ScreenBase::doCreateTagProcessor_(sead::Heap* heap) {
    return new (heap, 8) TagProcessor(mMgr->getMessageMgr(), mMgr->getFontMgr());
}

// 0x71009cf8a4
void Screen::m80(bool visible) {
    mLayout->GetPane()->SetVisible(visible);
}


// 0x71010ab24c (CSV Screen::updateButton)
void Screen::updateButton_() {
    if (_292 & 4)
        ScreenBase::updateButton_();
}

// 0x71010ab25c (CSV Screen::updateControl)
void Screen::updateControl_() {
    if (_292 & 8)
        eui::Screen::updateControl_();
}

// 0x71010ab26c (CSV Screen::updateAnimator)
void Screen::updateAnimator_() {
    if (_292 & 0x10)
        eui::Screen::updateAnimator_();
}

// 0x71010aaa70 (CSV Screen::m73)
void Screen::m73(f32 value) {
    _270 = value;
    m110();
    open(4);
}

// 0x71010aad0c (CSV Screen::m78)
void Screen::m78(f32 frame) {
    if (_288) {
        const u16 frame_size = _288->GetFrameSize();
        if (frame > 0.0f && f32(frame_size) >= frame)
            _288->Stop(frame);
    }
}

// 0x71010aacac (CSV Screen::m76)
void Screen::m76() {
    _270 = 0;
    close(-4);
}

// 0x71010aad78 (CSV Screen::m79)
void Screen::m79() {
    _288 = nullptr;
}

// 0x71010aad80 (CSV Screen::m89)
void Screen::m89() {
    _292 |= 0x20;
    _290 = 0;
    mMgr->inactivateScreen(mId);
}

// 0x71010aada0 (CSV Screen::m117)
void Screen::m117() {
    m82();
    for (auto& child : mChildren)
        child.m43();
}

// 0x71010aadf0 (CSV Screen::m118)
void Screen::m118() {
    m83();
    for (auto& child : mChildren)
        child.m44();
}

// 0x71010aae40 (CSV Screen::m119)
void Screen::m119() {
    m84();
    for (auto& child : mChildren)
        child.m45();
}

// 0x71010aae90 (CSV Screen::m120)
void Screen::m120() {
    m85();
    for (auto& child : mChildren)
        child.m46();
}

// 0x71010aaf54 (CSV Screen::m122)
void Screen::m122() {
    m87();
    for (auto& child : mChildren)
        child.m48();
}

// 0x71010aafa4 (CSV Screen::m123)
void Screen::m123() {
    m88();
    for (auto& child : mChildren)
        child.m49();
}

// 0x71010aaff4 (CSV Screen::m124)
void Screen::m124() {
    m89();
    for (auto& child : mChildren)
        child.m50();
}

// 0x71010ab044 (CSV Screen::m125)
void Screen::m125() {
    m90();
    for (auto& child : mChildren)
        child.m51();
}

// 0x71010ab094 (CSV Screen::m126)
void Screen::m126() {
    m91();
    for (auto& child : mChildren)
        child.m52();
}

// 0x71010aaee0 (CSV Screen::m121)
void Screen::m121() {
    if (!ksys::ui::sub_7100EDC564(mId))
        close(-4);
    m86();
    for (auto& child : mChildren)
        child.m47();
}

// 0x71010ab12c (CSV Screen::close)
// NON_MATCHING: the original reads the state byte at 0xfe as a signed value and compares it with 3 through a stack
// round trip (a SEAD_ENUM-like conversion); every other function reads it as an unsigned byte
void Screen::close(s32 option) {
    const bool v = ksys::ui::sub_7100EDC548(mId);
    if (option != -3 && v) {
        if (mState != 0) {
            if (mState != 3)
                _290 = 1;
        } else if (!_290) {
            _292 |= 0x20;
        }
    }
    eui::Screen::close(option);
}

// 0x71010ab1ac (CSV Screen::update)
void Screen::update() {
    _291 = 0;
    if (_292 & 1) {
        eui::Screen::update();
        m95();
        for (auto& child : mChildren)
            child.m56();
        if (_290 && isClosed())
            m124();
    }
}

// 0x71010ab27c (CSV Screen::doAfterBuildLayout)
void Screen::doAfterBuildLayout_(sead::Heap* heap) {
    m92(heap);
    for (auto& child : mChildren)
        child.m53(heap);
}

// 0x71010ab2dc (CSV Screen::doInitialize)
void Screen::doInitialize_(sead::Heap* heap) {
    ScreenBase::doInitialize_(heap);
    _294 = mDrawTarget;
    _295 = _104;
    m113();
    m114(heap);
    m116();
    sub_71010AB490(mLayout);
    if (auto* layout = mLayout) {
        if (layout->GetAnimResourceData("TimeLineDemoIn_00")) {
            const s32 count = sub_71010AC7C8(layout, "TimeLineDemoIn_00");
            if (count >= 1) {
                _278.allocBuffer(count, heap);
                sub_71010AC920(&_278, layout, "TimeLineDemoIn_00");
            }
        }
        layout->tryCreateAnimatorAuto("TimeLineDemo_00", false);
    }
    for (auto& child : mChildren)
        child.m54(heap);
    m93(heap);
    sub_71010A9B44(ksys::ui::sub_7100EDC5D4());
    m112(heap);
    _292 |= 0x1f;
    if (ksys::ui::sub_7100EDC548(mId))
        _292 &= ~0x20;
    else
        _292 |= 0x20;
    _290 = 0;
}

// 0x71010ab66c
// NON_MATCHING: the original walks the pointer buffer (begin / end computed after GetFrameSize, size reloaded) with
// a null check per entry; ours indexes it
void Screen::doUpdate_WorldMgrStuff() {
    if (_298.size() == 0)
        return;
    auto* world = ksys::world::Manager::instance();
    if (!world)
        return;
    const f32 frame = world->getEnvMgrUnchecked()->getExposure();
    if (frame == _2f8)
        return;
    const f32 max = _298.size() > 0 ? _298[0]->GetFrameSize() : 0.0f;
    if (frame < 0.0f) {
        for (s32 i = 0; i < _298.size(); ++i) {
            if (auto* animator = _298[i])
                animator->Stop(0.0f);
        }
    } else if (frame > max) {
        for (s32 i = 0; i < _298.size(); ++i) {
            if (auto* animator = _298[i])
                animator->Stop(max);
        }
    } else {
        for (s32 i = 0; i < _298.size(); ++i) {
            if (auto* animator = _298[i])
                animator->Stop(frame);
        }
    }
    _2f8 = frame;
}

// 0x71010ab5f8 (CSV Screen::doUpdate)
void Screen::doUpdate_() {
    if (_292 & 2) {
        doUpdate_WorldMgrStuff();
        m115();
        m94();
        for (auto& child : mChildren)
            child.m55();
    }
}

// 0x71010ab7a0 (CSV Screen::doOpenStart)
void Screen::doOpenStart_() {
    _291 |= 1;
    mButtonGroup->sub_7100BD83D8();
    if (isEnableControl())
        ksys::ui::sub_7100EDC5F0();
    m98();
    for (auto& child : mChildren)
        child.m57();
}

// 0x71010ab820 (CSV Screen::doOpenEnd)
void Screen::doOpenEnd_() {
    _291 |= 2;
    m99();
    for (auto& child : mChildren)
        child.m58();
}

// 0x71010ab87c (CSV Screen::doCloseStart)
void Screen::doCloseStart_() {
    _291 |= 4;
    if (isEnableControl())
        ksys::ui::sub_7100EDC5F0();
    m100();
    for (auto& child : mChildren)
        child.m59();
}

// 0x71010ab8f0 (CSV Screen::doCloseEnd)
void Screen::doCloseEnd_() {
    _291 |= 8;
    m101();
    for (auto& child : mChildren)
        child.m60();
    if (ksys::ui::sub_7100EDC548(mId))
        mMgr->activateScreen(mId);
}

// NON_MATCHING: the original evaluates `held == button`, `held != 0` and the cursor flag without branches (cmp / ccmp / ccmp);
// ours branches on the button check.
// 0x71010ab97c
void Screen::sub_71010AB97C(eui::AnimButton* button) {
    if (button && mMgr->getBoxCursorMgr()) {
        eui::ButtonGroup* group = mButtonGroup;
        const bool enabled = mMgr->getBoxCursorMgr()->isTargetEnabled(eui::DrawTarget(1));
        if (group->_28 == button && group->_28 && !enabled) {
            if (eui::BoxCursorNode* node = findBoxCursorNodeByTag(button->mTag))
                moveBoxCursor_(node);
        }
    }
    m102(button);
    for (auto& child : mChildren)
        child.m61(button);
}

// 0x71010aba48 (CSV Screen::doButtonOnEnd)
void Screen::doButtonOnEnd_(eui::AnimButton* button) {
    m103(button);
    for (auto& child : mChildren)
        child.m62(button);
}

// 0x71010abb08 (CSV Screen::doButtonOffStart)
void Screen::doButtonOffStart_(eui::AnimButton* button) {
    m104(button);
    for (auto& child : mChildren)
        child.m63(button);
}

// 0x71010abbc8 (CSV Screen::doButtonOffEnd)
void Screen::doButtonOffEnd_(eui::AnimButton* button) {
    m105(button);
    for (auto& child : mChildren)
        child.m64(button);
}

// 0x71010abc88 (CSV Screen::doButtonDownStart)
void Screen::doButtonDownStart_(eui::AnimButton* button) {
    m106(button);
    for (auto& child : mChildren)
        child.m65(button);
}

// 0x71010abd48 (CSV Screen::doButtonDownEnd)
void Screen::doButtonDownEnd_(eui::AnimButton* button) {
    m107(button);
    for (auto& child : mChildren)
        child.m66(button);
}

// 0x71010abe08 (CSV Screen::doButtonCancelStart)
void Screen::doButtonCancelStart_(eui::AnimButton* button) {
    m108(button);
    for (auto& child : mChildren)
        child.m67(button);
}

// 0x71010abec8 (CSV Screen::doButtonCancelEnd)
void Screen::doButtonCancelEnd_(eui::AnimButton* button) {
    m109(button);
    for (auto& child : mChildren)
        child.m68(button);
}

// 0x71010abaa8
void Screen::sub_71010ABAA8(eui::AnimButton* button) {
    m103(button);
    for (auto& child : mChildren)
        child.m62(button);
}

// 0x71010abb68
void Screen::sub_71010ABB68(eui::AnimButton* button) {
    m104(button);
    for (auto& child : mChildren)
        child.m63(button);
}

// 0x71010abc28
void Screen::sub_71010ABC28(eui::AnimButton* button) {
    m105(button);
    for (auto& child : mChildren)
        child.m64(button);
}

// 0x71010abce8
void Screen::sub_71010ABCE8(eui::AnimButton* button) {
    m106(button);
    for (auto& child : mChildren)
        child.m65(button);
}

// 0x71010abda8
void Screen::sub_71010ABDA8(eui::AnimButton* button) {
    m107(button);
    for (auto& child : mChildren)
        child.m66(button);
}

// 0x71010ab490
void Screen::sub_71010AB490(eui::LayoutEx* layout) {
    if (!layout)
        return;
    if (layout->GetAnimResourceData("SunLight")) {
        if (auto* animator = layout->tryCreateAnimatorAuto("SunLight", false)) {
            if (_298.isFull())
                return;
            animator->StopAtMin();
            _298.pushBack(animator);
        }
    }
    for (auto& part : layout->mPartsLayoutList)
        sub_71010AB490(nn::font::DynamicCast<eui::LayoutEx>(part.layout));
}

// 0x71010ac7c8
s32 Screen::sub_71010AC7C8(eui::LayoutEx* layout, const sead::SafeString& name) {
    s32 count = layout->GetAnimResourceData(name.cstr()) && layout->tryCreateAnimatorAuto(name.cstr(), false);
    for (auto& part : layout->mPartsLayoutList) {
        if (auto* child = nn::font::DynamicCast<eui::LayoutEx>(part.layout))
            count += sub_71010AC7C8(child, name);
    }
    return count;
}

// 0x71010ac920
void Screen::sub_71010AC920(sead::PtrArray<eui::Animator>* animators, eui::LayoutEx* layout,
                            const sead::SafeString& name) {
    if (!animators || animators->capacity() < 1)
        return;
    if (layout->GetAnimResourceData(name.cstr())) {
        if (auto* animator = layout->sub_7100BDDDF8(name.cstr()))
            animators->pushBack(animator);
    }
    for (auto& part : layout->mPartsLayoutList) {
        if (auto* child = nn::font::DynamicCast<eui::LayoutEx>(part.layout))
            sub_71010AC920(animators, child, name);
    }
}

// 0x71010abe68
void Screen::sub_71010ABE68(eui::AnimButton* button) {
    m108(button);
    for (auto& child : mChildren)
        child.m67(button);
}

// 0x71010abf28
void Screen::sub_71010ABF28(eui::AnimButton* button) {
    m109(button);
    for (auto& child : mChildren)
        child.m68(button);
}

// 0x71010ab0e4 (CSV Screen::open)
void Screen::open(s32 option) {
    _290 = 0;
    if (ksys::ui::sub_7100EDC548(mId))
        _292 &= ~0x20;
    eui::Screen::open(option);
}

// 0x7100a828f4 (primary slot111)
int Screen::handleMessage(const ksys::Message&) {
    return 0;
}

// 0x7100a828fc (CSV Screen::m112_null)
void Screen::m112(sead::Heap*) {}

// 0x7100a82900 (CSV Screen::m113_null)
void Screen::m113() {}

// 0x7100a82904 (CSV Screen::m114_null)
void Screen::m114(sead::Heap*) {}

// 0x7100a82908 (CSV Screen::m115_null)
void Screen::m115() {}

// 0x7100a8290c (CSV Screen::m116_null)
void Screen::m116() {}

// 0x71010aa7a0 (CSV Screen::x_0)
ScreenChild* Screen::getChild(s32 group, s32 index) {
    if (!mChildGroupSizes.isIndexValid(group))
        return nullptr;
    if (mChildGroupSizes(group) <= index)
        return nullptr;

    s32 offset = 0;
    for (s32 i = 0; i < group; ++i)
        offset += mChildGroupSizes[i];
    return mChildren.at(offset + index);
}

// 0x71010aa868
s32 Screen::sub_71010AA868(s32 group) const {
    if (!mChildGroupSizes.isBufferReady() || !mChildGroupSizes.isIndexValid(group))
        return 0;
    return mChildGroupSizes(group);
}

// 0x71010aa894
void Screen::sub_71010AA894() {
    const s32 mode = eui::ScreenMgr::instance()->getBoxCursorMgr()->mMode;
    if (static_cast<u32>(mode - 1) <= 1 && mActiveCursorNode)
        mActiveCursorNode->mButton->ForceOff();
}

// 0x71010aa8d0
void Screen::sub_71010AA8D0() {
    if (_292 & 0x100)
        return;
    _292 |= 0x100;
    if (mButtonGroup->_38 & 2)
        _292 |= 0x80;
    else
        _292 &= ~0x80;
    mButtonGroup->_38 &= ~2;
}

// 0x71010aa910
void Screen::sub_71010AA910() {
    if (!(_292 & 0x100))
        return;
    const u32 flags = mButtonGroup->_38;
    mButtonGroup->_38 = (_292 & 0x80) ? (flags | 2) : (flags & ~2);
    _292 &= ~0x180;
}

// 0x71010aa9d0
ksys::SeadController* Screen::sub_71010AA9D0() {
    if (!mUIController)
        return nullptr;
    return sead::DynamicCast<ksys::SeadController>(mUIController->getController());
}

}  // namespace uking::ui
