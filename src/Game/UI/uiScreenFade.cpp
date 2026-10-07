#include <devenv/seadEnvUtil.h>
#include <prim/seadSafeString.h>
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageMgr.h"
#include "Game/UI/euiMessageSet.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTagProcessor.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::ui {

namespace {
// Placeholder name (vtable 0x2507f38; internal to this translation unit, the original refers to the vtable directly):
// the tag processor of the Fade screen. Its constructor is inlined into Fade::m93; it re-declares m29, whose code is
// the same as TagProcessor::m29.
class Unk_7102507f38 : public TagProcessor {
public:
    Unk_7102507f38(eui::MessageMgr* message_mgr, eui::FontMgr* font_mgr)
        : TagProcessor(message_mgr, font_mgr) {}
    ~Unk_7102507f38() override = default;
    f32 m29() const override;
};
}  // namespace

// 0x71010a0a90
Fade::Fade() : Screen() {}

Fade::~Fade() = default;

// 0x71010a1ce0
bool Fade::isEnableControl() const {
    return true;
}

// 0x71010a0b3c
void Fade::open(s32 option) {
    Screen::open(option);
}

// 0x71010a0b40
void Fade::close(s32 option) {
    ksys::ui::callCloseFadeStatusScreen();
    Screen::close(option);
}

// 0x71010a1ce8
const char* Fade::getLayoutName_() const {
    return "Fade_00";
}

// 0x71010a1b64 (CSV Fade::m27)
eui::TagProcessor* Fade::doCreateTagProcessor_(sead::Heap* heap) {
    auto* processor = ScreenBase::doCreateTagProcessor_(heap);
    processor->setRubyEnabled(true);
    return processor;
}

// 0x71010a1b80
bool Fade::isOpenEnd_() {
    if (_a24)
        return true;
    if (eui::Screen::isOpenEnd_()) {
        _a24 = true;
        return false;
    }
    return false;
}

// 0x71010a0e20
void Fade::m74(f32 progress) {
    if (_a20 == -1 || _270 == 0)
        m76();

    const f32 duration = std::min(progress, _270);
    const f32 open_size = getOpenFrameSize();
    if (open_size == 0)
        return;

    const f32 ratio = duration / _270;
    f32 frame;
    switch (_a20) {
    case 0:
        frame = open_size - open_size * ratio;
        break;
    case 1:
        frame = open_size * ratio;
        break;
    default:
        frame = 0;
        break;
    }
    open(1);
    sub_7100BE9DD4(frame);
}

// 0x71010a01a8
void ScreenFadeDemo::sub_71010A01A8(s32 where) {
    if (where)
        _300->StopAtMax();
    else
        _300->StopAtMin();
}

// 0x71010a01c4
bool ScreenFadeDemo::sub_71010A01C4() {
    return _300->mFrame == f32(_300->GetFrameSize());
}

// 0x71010a060c (the same code as Fade::isOpenEnd_, with the flag at 0x358)
bool ScreenFadeDemo::isOpenEnd_() {
    if (_358)
        return true;
    if (eui::Screen::isOpenEnd_()) {
        _358 = true;
        return false;
    }
    return false;
}

// 0x71010a0534
void ScreenFadeDemo::m98() {
    _358 = false;
    ksys::snd::SoundMgr::instance()->sub_71011FC0C0(sub_71010A0DE0(false, mLayout->_91 == 2, _350), 1);
    UI::instance()->sub_71010A7994(true);
}

// 0x71010a059c
void ScreenFadeDemo::m100() {
    ksys::snd::SoundMgr::instance()->sub_71011FC17C(sub_71010A0DE0(false, mLayout->_91 == 0, _350), 1);
    UI::instance()->sub_71010A7994(false);
}

// 0x71010a05fc
void ScreenFadeDemo::m101() {
    ksys::snd::SoundMgr::instance()->sub_71011FC288();
}

// 0x71010a02f0 (the same code as Fade::m74, with the state at 0x354)
void ScreenFadeDemo::m74(f32 progress) {
    if (_354 == -1 || _270 == 0)
        m76();

    const f32 duration = std::min(progress, _270);
    const f32 open_size = getOpenFrameSize();
    if (open_size == 0)
        return;

    const f32 ratio = duration / _270;
    f32 frame;
    switch (_354) {
    case 0:
        frame = open_size - open_size * ratio;
        break;
    case 1:
        frame = open_size * ratio;
        break;
    default:
        frame = 0;
        break;
    }
    open(1);
    sub_7100BE9DD4(frame);
}

// 0x71010a1f58
f32 Unk_7102507f38::m29() const {
    return UI::instance()->sub_71010A71A8();
}

// 0x71010a0ef0 (CSV Fade::m93InitMaybe)
// NON_MATCHING: only the registers of the ruby test differ (the original keeps the tag processor in x9 and the flag in w8)
void Fade::m93(sead::Heap* heap) {
    _390 = new (heap, 8) Unk_7102507f38(mMgr->getMessageMgr(), mMgr->getFontMgr());
    const sead::RegionLanguageID language = sead::EnvUtil::getRegionLanguage();
    _390->setRubyEnabled(language != sead::RegionLanguageID::KRko &&
                         language != sead::RegionLanguageID::CNzh &&
                         language != sead::RegionLanguageID::TWzh);
    eui::sub_7100933580(findPane_("T_Tips_00"))->SetTagProcessor(_390);

    _300 = mLayout->createAnimatorAuto("Color", true);

    _308.allocBuffer(4, heap);
    _308.setAnimator(2, mLayout->createAnimatorAuto("InShort", false));
    eui::Animator* open_animator = mLayout->mOpenAnimator;
    open_animator->nn::ui2d::AnimTransform::SetEnabled(false);
    open_animator->mRate = 0;
    _308.setAnimator(1, mLayout->mOpenAnimator);
    _308.setAnimator(0, mLayout->createAnimatorAuto("InLong", false));
    const char* const in_demo = "InDemo";
    _308.setAnimator(3, mLayout->createAnimatorAuto(in_demo, false));

    _328.allocBuffer(4, heap);
    _328.setAnimator(2, mLayout->createAnimatorAuto("OutShort", false));
    eui::Animator* close_animator = mLayout->mCloseAnimator;
    close_animator->nn::ui2d::AnimTransform::SetEnabled(false);
    close_animator->mRate = 0;
    _328.setAnimator(1, mLayout->mCloseAnimator);
    _328.setAnimator(0, mLayout->createAnimatorAuto("OutLong", false));
    _328.setAnimator(3, mLayout->createAnimatorAuto(in_demo, false));

    _358 = mLayout->createAnimatorAuto("LogoIn", false);
    _360 = mLayout->createAnimatorAuto("LogoOut", false);
    _368 = mLayout->createAnimatorAuto("TipsIn", false);
    _370 = mLayout->createAnimatorAuto("TitleLogoIn", true);
    _378 = mLayout->createAnimatorAuto("TipsOut", false);
    _380 = mLayout->createAnimatorAuto("TitleLogoOut", false);
    _388 = sub_7100BEAFB0("Pa_LoadBar_00")->createAnimatorAuto("Gauge", true);
    x_2();

    {
        const char* guide_names[] = {"GuideIn", "GuideOut"};
        _348 = mLayout->createAnimatorSet(guide_names, 2, true);
        _348->select(0)->Stop(0.0f);
    }
    {
        const char* tips_names[] = {"NowTipsOut", "NewTipsIn"};
        _350 = mLayout->createAnimatorSet(tips_names, 2, true);
        _350->select(0)->Stop(0.0f);
    }

    _398 = mLayout->tryCreateAnimatorAuto("HardMode", true);
    if (_398)
        _398->Stop(0.0f);
    _3a0 = sub_7100BEAFB0("Pa_LoadBar_00")->tryCreateAnimatorAuto("HardMode", true);
    if (_3a0)
        _3a0->Stop(0.0f);

    if (auto* message_set = eui::MessageMgr::instance()->getMessageSet("LayoutMsg/SystemWindow_01")) {
        const eui::MessageString message = message_set->tryFindMessage("T_DummyText_00");
        if (message.getString())
            mLayout->setMessageStringForEachId("T_DummyText_00", message, true, nullptr);
    }

    mLayout->setMessageStringForEachId(
        "T_TipsTitle_00", eui::MessageString(0, sead::WSafeString::cEmptyString.cstr()), true,
        nullptr);
    mLayout->setMessageStringForEachId(
        "T_Tips_00", eui::MessageString(0, sead::WSafeString::cEmptyString.cstr()), true, nullptr);
    sub_7100BEAFB0("Pa_GuideA_00")->sub_7100BDDE7C(false, 1, true);
}

// 0x71010a0ee8
void Fade::sub_71010A0EE8(f32 progress) {
    _3b0 = progress;
}

// 0x71010a0bbc
void Fade::x(s32 forward) {
    if (forward)
        _300->PlayFromCurrent(eui::Animator::PlayType(0), 1.0f);
    else
        _300->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
}

// 0x71010a0b6c
void Fade::stopColorAnimatorAt(s32 where) {
    if (where)
        _300->StopAtMax();
    else
        _300->StopAtMin();
}

// 0x71010a0be8
void Fade::x_2() {
    if (!isClosed() && (_3a8 || !isOpened()))
        return;

    if (_3a8) {
        _308.select(1)->StopAtMin();
        eui::Animator* animator = _328.select(1);
        animator->nn::ui2d::AnimTransform::SetEnabled(false);
        animator->mRate = 0;
        mLayout->setOpenAnimator(_358);
        mLayout->setCloseAnimator(_360);
        mLayout->mOpenAnimator->Disable();
        mLayout->mCloseAnimator->Disable();
    } else {
        _358->StopAtMin();
        eui::Animator* animator = _360;
        animator->nn::ui2d::AnimTransform::SetEnabled(false);
        animator->mRate = 0;
        mLayout->setOpenAnimator(_308.select(_3ac));
        mLayout->mOpenAnimator->Disable();
        if (_3ac == 3) {
            mLayout->setCloseAnimator(nullptr);
        } else {
            mLayout->setCloseAnimator(_328.select(_3ac));
            mLayout->mCloseAnimator->Disable();
        }
        if (isOpened())
            mLayout->mOpenAnimator->StopAtMax();
    }
}

// 0x71010a0be0
void Fade::x_1(s32 type) {
    _3ac = type;
    x_2();
}

// 0x71010a0d34
void Fade::setStartedMaybe(bool started) {
    _3a8 = started;
    x_2();
}

// 0x71010a0d40
void Fade::clearSomeTipsField() {
    mTips.clear();
}

}  // namespace uking::ui

namespace uking::ui {

void ScreenFadeDemo::sub_71010A01F8(s32 value) {
    _350 = value;
    sub_71010A0200();
}

}  // namespace uking::ui
