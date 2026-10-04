#include "Game/UI/uiScreens.h"
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiLayoutEx.h"

namespace eui {

// 0x7100be9a4c (CSV eui::Screen::x)
void Screen::m13() {}

}  // namespace eui

namespace uking::ui {

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

// 0x71010ab0e4 (CSV Screen::open)
void Screen::open(s32 option) {
    _290 = 0;
    if (ksys::ui::sub_7100EDC548(mId))
        _292 &= ~0x20;
    eui::Screen::open(option);
}

// 0x7100a828f4 (CSV Screen::m111)
s32 Screen::m111() {
    return 0;
}

// 0x7100a828fc (CSV Screen::m112_null)
void Screen::m112(sead::Heap*) {}

// 0x7100a82900 (CSV Screen::m113_null)
void Screen::m113() {}

// 0x7100a82904 (CSV Screen::m114_null)
void Screen::m114() {}

// 0x7100a82908 (CSV Screen::m115_null)
void Screen::m115() {}

// 0x7100a8290c (CSV Screen::m116_null)
void Screen::m116() {}

}  // namespace uking::ui
