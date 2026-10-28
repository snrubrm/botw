#include "KingSystem/GameData/gdtSpecialFlags.h"
#include <cstring>
#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiScreenChildStates.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "Game/UI/uiManager.h"
#include "Game/Scene/gameScene.h"
#include "Game/gameSaveSystem.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageDispatcher.h"

#include "Game/UI/euiScreenSoundLinkUser.h"
#include "Game/UI/euiTextSearcher.h"
#include "Game/UI/euiMessageMgr.h"
#include <gfx/nin/seadGraphicsNvn.h>
#include <nn/ui2d/BuildTypes.h>

// Trivial state-callback slots (154 and up) of the leaf screens that declare their own virtuals.
namespace uking::ui {

// ScreenAppMap
// 0x71009dc5a8
void ScreenAppHome::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_7102480ab0 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x7100a11dbc
void ScreenMainScreen3D::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_710248d2a8 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x7100a1fad4
void ScreenMainShortCut::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_710248ea90 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x7100a2424c
void ScreenMessageGet::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_710248f740 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x7100a2cd50
void ScreenPauseMenuInfo::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_71024923e0 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x7100a35098
void ScreenPauseMenu::sub_7100A35098() {
    invokeSoundLink2Event_("mc_Decide");
}

// 0x7100a350e0
void ScreenPauseMenu::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_71024934f8 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x7100a4bdec
void ScreenShopBtnList20::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_7102496f20 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x7100a51a98
void ScreenShopInfo::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_7102498248 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x7100a536b4
void ScreenSkip::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_7102498858 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x7100a54040
void ScreenSousaGuide::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_7102498e18 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x71009f9f30
void ScreenAppPictureBook::sub_71009F9F30(const sead::SafeString& name) {
    if (!ksys::gdt::getFlag_IsGet_Obj_SheikSensorLv2())
        return;
    const char* previous;
    ksys::gdt::getFlag_ActorName_SeakSensor_Slot0(&previous);
    ksys::gdt::setFlag_ActorName_SeakSensor_Slot0(name);
    if (name == previous && UiSubsys1::instance()->get38a8() == 1)
        return;
    _3ab8 = true;
}

// 0x71009e0c28
bool ScreenAppMapDungeon::sub_71009E0C28() {
    if (mSensorChild) {
        const s32 state = mSensorChild->_104;
        if (state == 7 || (u32(state - 1) <= 4 && !((state - 1) & 1)))
            return false;
    }
    if (sead::DynamicCast<ScreenAppSystemWindow>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow)))
        return false;
    return _36e4;
}

// 0x71009e0d14
bool ScreenAppMapDungeon::sub_71009E0D14() {
    if (mSensorChild) {
        const s32 state = mSensorChild->_104;
        if (state == 7 || (u32(state - 1) <= 4 && !((state - 1) & 1)))
            return false;
    }
    return !sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
}

// 0x71009e2584
void ScreenAppMapDungeon::sub_71009E2584() {
    _11518 = nn::font::DynamicCast<ScreenAppMapUnk3c90>(nn::font::DynamicCast<ScreenChildEx>(getChild(1, 0)));
    mSensorChild = nn::font::DynamicCast<Unk_710247c010>(nn::font::DynamicCast<ScreenChildEx>(getChild(0, 0)));
}

// 0x71009eaa24
void ScreenAppMap::sub_71009EAA24() {
    UiSubsys1::instance()->start388c();
    UiSubsys1::instance()->set38c8();
    _3bf8 = sub_7100BEAFB0("Pa_Cursor_00");
    if (_3bf8)
        _3bf8->sub_7100BDDE7C(true, 0, true);
    sub_71009F0668();
    _3c00->StopAtMin();
    _3c10->StopAtMin();
    _3c08->StopAtMin();
    _3c18->mFlags |= 0x10;
    _3c18->StopAtMin();
    _3c20->StopAtMin();
    _3c28->StopAtMin();
    _3c30 = sub_7100A48104(sead::SafeString("Pa_Cursor_00"), nullptr);
}

// 0x71009eb8b4
void ScreenAppMap::subRun() {
    sub_71009EB960();
    if (_3c98) {
        const s32 state = _3c98->_104;
        if (u32(state - 2) <= 4 && ((state - 2) & 1) == 0) {
            if (auto* child = static_cast<AppMapIconPart*>(getChildExMaybe(1, 0))) {
                if (child->sub_7100994E88()) {
                    auto* hovered = static_cast<AppMapIconPart*>(getChildExMaybe(1, 0));
                    sub_71009EBA68(hovered ? hovered->getHoveredIconData() : nullptr);
                }
            }
        }
    }
    if (sub_71009E9F48())
        return;
    getStateMachine().changeState(&sUnk_71025df180);
}

// 0x71009eb960
void ScreenAppMap::sub_71009EB960() {
    auto* window = sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
    if (!window)
        return;
    const s32 state = window->_3610;
    if (u32(state - 3) <= 1) {
        if (auto* child = static_cast<AppMapIconPart*>(getChildExMaybe(1, 0)))
            sub_7100990690(child);
    } else if (state == 5) {
        sub_71009F20F4();
    } else if (state == 6) {
        sub_71009F20F4();
    } else if (state == 7) {
        sub_71009F2204();
    }
}

// 0x71009eba68
// NON_MATCHING: the original compares the entry's 4-byte id through stack temporaries (the field's type needs the
// volatile int conversion), and the shared StopAtMin / StopAtMax blocks are laid out the other way round.
void ScreenAppMap::sub_71009EBA68(UiSubsys1Entry* icon) {
    if (!icon)
        return;
    if (icon->_1c == 2) {
        if (sead::DynamicCast<Unk_71024755d8>(icon)) {
            if (!(icon->_3c & 0x200000))
                _3c20->StopAtMin();
            else
                _3c20->StopAtMax();
        } else {
            _3c20->StopAtMin();
        }
    } else if (icon->_1c == 0x2b) {
        if (sead::DynamicCast<Unk_71024756f0>(icon)) {
            if (!(icon->_3c & 0x200000))
                _3c20->StopAtMin();
            else
                _3c20->StopAtMax();
        } else {
            _3c20->StopAtMin();
        }
    } else {
        _3c20->StopAtMin();
    }
    sub_71009F0508(icon);
    UiSubsys1::instance()->sub_7100966E2C();
    UiSubsys1::instance()->set38e4(2);
}

// 0x71009eab28
void ScreenAppMap::sub_71009EAB28() {
    _3c90 = nn::font::DynamicCast<ScreenAppMapUnk3c90>(nn::font::DynamicCast<ScreenChildEx>(getChild(4, 0)));
    _3c98 = nn::font::DynamicCast<Unk_710247c010>(nn::font::DynamicCast<ScreenChildEx>(getChild(5, 0)));
}

// 0x71009ea064
void ScreenAppMap::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_7102481828 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x7100a18350
void ScreenMainScreen::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_710248e4e0 creator(mButtonGroup, &mControls, &_50);
    auto* messages = eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_());
    eui::TextSearcher searcher(messages, mTagProcessor);
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, sead::GraphicsNvn::instance()->getNnDevice(), accessor, &creator, &searcher,
                           nn::ui2d::Layout::BuildOption{}, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x71009ea178 (CSV ScreenAppMap::m92)
void ScreenAppMap::m92(sead::Heap*) {
    if (auto* subsys = UiSubsys1::instance())
        subsys->sub_710095B1BC();
}

// 0x71009ec18c (CSV ScreenAppMap::m100)
void ScreenAppMap::m100() {
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::MessageTipsPauseMenu))
        screen->close(-1);
}

// 0x71009ebbfc (CSV ScreenAppMap::demoEnter)
void ScreenAppMap::demoEnter() {
    _3c00->StopAtMin();
    _3c08->StopAtMin();
    _3ad1 = 0;
    _3610->_b33a = 0;
    UiSubsys1::instance()->clear38c8();
    _3610->_b350 = 0;
}

// 0x71009ebc68
void ScreenAppMap::demoRun() {
    sub_71009EBD6C();
    _3c64 = 0;
    const s32 hour = wm::getHour();
    if (hour != _3c58) {
        _3c58 = hour;
        _3c64 = 1;
    }
    _3c65 = 0;
    const s32 minute = wm::getMinute();
    if (minute != _3c5c) {
        _3c5c = minute;
        _3c65 = 1;
    }
    sub_71009F1CA4(_3c78);
    _3c66 = 0;
    const f32 temperature = sead::Mathf::floor(wm::getWorldTemperatureForUI());
    if (temperature != _3c60) {
        _3c60 = temperature;
        _3c66 = 1;
    }
    sub_71009F1B9C();
    sub_71009EBEC8();
    const f32 displayed_temperature = UiSubsys1::instance()->_850.get38();
    ksys::gdt::Manager::instance()->setF32(displayed_temperature, sUnk_71025df330.mWorldTemperatureFlag);
}

// 0x71009ebd6c
void ScreenAppMap::sub_71009EBD6C() {
    if (!_3610)
        return;
    UiSubsys1::instance()->getVec3834()->update();
    if (_3cb1 && _3610->mNormalMap.sub_71009A829C())
        _3cb1 = 0;
    _3b18._10.sub_7100A816D8();
    if (UiSubsys1::instance()->sub_7100968900(1))
        sub_71009EF7EC();
    if (!_3ad2) {
        _3ad2 = Unk_71025d69f0::instance()->sub_710094F6F8() & 1;
        if (!_3ad2)
            return;
    }
    if (UiSubsys1::instance()->get3858()) {
        if (UiSubsys1::instance()->return0B())
            UiSubsys1::instance()->sub_71009679AC();
        if (!UiSubsys1::instance()->sub_7100968D04())
            return;
        if (UiSubsys1::instance()->return0B())
            UiSubsys1::instance()->sub_71009677CC();
        UiSubsys1::instance()->sub_7100968774();
        sub_71009EFAD4(UiSubsys1::instance()->sub_7100968B1C());
        return;
    }
    if (UiSubsys1::instance()->sub_7100968B1C() == 11)
        _3c90->sub_71009C1888(1);
    if (sub_71009EF8DC())
        UiSubsys1::instance()->sub_7100968C2C(1);
}

// 0x71009ebec8
void ScreenAppMap::sub_71009EBEC8() {
    if (UiSubsys1::instance()->sub_7100967498()) {
        if (_3c90)
            _3c90->m5(true);
    } else if (UiSubsys1::instance()->sub_71009674C0()) {
        if (_3c90)
            _3c90->m6(true);
        if (_3c98)
            _3c98->m6(true);
    }
    if (!UiSubsys1::instance()->get38ac())
        return;
    if (UiSubsys1::instance()->get38d8() && !UiSubsys1::instance()->get38d9()) {
        if (_3c90) {
            ksys::snd::ExpressionSoundCtrl::instance()->sub_710104F4BC();
            const s32 type = UiSubsys1::instance()->get38a8();
            _3c90->sub_71009C1198(type);
        }
    } else if (!UiSubsys1::instance()->get38d8() && UiSubsys1::instance()->get38d9()) {
        if (_3c90) {
            ksys::xlink::Manager::instance()->setGlobalProperty(26, 10000.0f);
            ksys::xlink::Manager::instance()->setGlobalProperty(27, 0.0f);
            ksys::snd::ExpressionSoundCtrl::instance()->sub_710104F4C0();
            _3c90->sub_71009C1198(2);
        }
    }
    UiSubsys1::instance()->copy38d8To38d9();
}

// 0x71009ec01c (CSV ScreenAppMap::demoLeave)
void ScreenAppMap::demoLeave() {    UiSubsys1::instance()->sub_7100968844();
    _3ad1 = 1;
}

// 0x71009eaf40 (CSV ScreenAppMap::m83)
void ScreenAppMap::m83() {
    sub_71009EACC0(0);
    getStateMachine().changeState(&sUnk_71025df180);
    if (_3628[2]) {
        if (wm::isFindDungeonActivated())
            _3628[2]->StopAtMin();
        else
            _3628[2]->StopAtMax();
    }
    if (_3c88) {
        if (wm::sub_7100A9D800())
            _3c88->StopAtMax();
        else
            _3c88->StopAtMin();
    }
}

// 0x71009eb49c (CSV ScreenAppMap::mainEnter)
void ScreenAppMap::mainEnter() {
    _3ad1 = 1;
    _3610->_b33a = 1;
}

// 0x71009eb4b8 (CSV ScreenAppMap::mainRun)
void ScreenAppMap::mainRun() {
    if (UiSubsys1::instance()->is848EqualTo1())
        sub_71009EB52C();
    else if (UiSubsys1::instance()->is848Zero())
        sub_71009EB72C();
    if (sub_71009E9F48())
        getStateMachine().changeState(&sUnk_71025df1e0);
}

// 0x71009eb814 (CSV ScreenAppMap::subEnter)
void ScreenAppMap::subEnter() {
    _3c00->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
    if (_3c98) {
        const s32 state = _3c98->_104;
        if (state == 7 || (u32(state - 1) <= 4 && ((state - 1) & 1) == 0))
            _3c08->PlayFromCurrent(eui::Animator::PlayType(0), -1.0f);
    }
    _3ad1 = 1;
    UiSubsys1::instance()->clear3885();
    _3610->_b350 = 0;
}

// 0x71009eb810 (CSV ScreenAppMap::mainLeave)
void ScreenAppMap::mainLeave() {}

// 0x71009ebbe0 (CSV ScreenAppMap::subLeave)
void ScreenAppMap::subLeave() {
    UiSubsys1::instance()->set3885();
}

// 0x71009f28b0
s32 ScreenAppMap::m157() {
    return 0;
}

// 0x71009f28b8
s32 ScreenAppMap::m161() {
    return 0;
}

// 0x71009f28c0 (CSV ScreenAppMap::demoReenter)
s32 ScreenAppMap::demoReenter() {
    return 0;
}

// 0x71009d832c
// NON_MATCHING: clang hoists the animator frame load above the photo count test (the original loads it in each branch)
void ScreenAppCamera::m154() {
    if (_36f0 < 48) {
        if (_3628->mFrame == _3628->GetFrameSize())
            _3628->StopAtMin();
    } else if (_3628->mFrame == 0.0f) {
        _3628->StopAtMax();
    }
    _401a = false;
    sead::FormatFixedSafeString<8> number("%02d", _36f0);
    setWidgetString(mLayout, "T_Num_00", number);
    _4118 = 0;
    x();
    const auto* state = getStateMachine().getPrevState();
    // called through a pointer in the original (not devirtualised)
    if (state->getId() == (&sUnk_71025dcd60)->getId() ||
        // called through a pointer in the original (not devirtualised)
        state->getId() == (&sUnk_71025dcd00)->getId()) {
        Manager::instance()->sub_7100A7CACC();
        if (_4019) {
            Unk_71025d1740::instance()->sub_7100901A90(true);
            _4019 = false;
        }
    }
}

// ScreenAppPictureBook
// 0x71009faa9c
void ScreenAppPictureBook::m156() {
    if (_3658)
        _3658->sub_710093F594(false);
}

// 0x71009faccc
void ScreenAppPictureBook::m160() {
    if (_3660)
        _3660->sub_710093F594(false);
}

// 0x71009fa3fc: waits until every texture controller is loaded
void ScreenAppPictureBook::m89() {
    bool ready = true;
    for (auto it = sUnk_71025eb5c0.begin(), end = sUnk_71025eb5c0.end(); it != end; ++it) {
        if (it->sub_71009CBEAC()) {
            it->sub_71009CC3A0();
            ready = false;
        }
        ready &= it->sub_71009CBFA4();
    }
    if (ready)
        _292 |= 0x20;
}

// 0x71009fa478
void ScreenAppPictureBook::m128() {
    for (auto& controller : sUnk_71025eb5c0)
        controller.sub_71009CC970();
}

// 0x71009d98b8
// NON_MATCHING: the original passes memset's return value as sub_71009DB9C8's first argument
// (`ldr x1` reloads the buffer, x0 is the memset result); writing the natural two-statement form
// our clang reloads the member into x0 and copies it, and the inline-memset form keeps the pointer
// in a callee-saved register. The other difference is the register pair of the two `_6f8` / `_700`
// stores.
void ScreenAppCamera::m162() {
    if (getViewerType() == 0) {
        if (_4020) {
            memset(_4020, 0, 0x1e000);
            _4028 = s32(sub_71009DB9C8(_4020, _4020, &_36f8, 0x10000));
        }
        if (_401a) {
            if (_4030) {
                memset(_4030, 0, 0x1e000);
                _4038 = s32(sub_71009DB9C8(_4030, _4030, &_3b88, 0x5000));
            }
        }
    }
    if (_3638)
        _3638->StopAtMax();
    eui::Screen::x_2();
    Unk_710247dc90::Request request;
    request.texture = &_36f8;
    request.texture2 = &_3b88;
    request.name = _4198;
    request.flag = _401a;
    sub_71009C6BF4(_3610, request);
    _3610->_6f8 = _4040;
    _3610->_700 = _4060;
    _4368.sub_71009348D0(true);
    _3620->PlayAuto(1.0f);
}

// 0x71009fa4b8
void ScreenAppPictureBook::m129() {
    if (!_3628 || !_3658 || !_3660)
        return;
    const f32 rate = _3628->mRate;
    const bool at_start = rate < 0.0f ? true : _3628->mFrame == 0.0f;
    const bool at_end = rate > 0.0f ? true : _3628->mFrame == f32(_3628->GetFrameSize());
    if (at_start) {
        for (auto& list : _3658->mGroupLists) {
            for (auto& group : list.mUnits) {
                if (!group.mEntry || !group.mRecord || group.mRecord->_c < 0)
                    continue;
                for (auto& unit : group.mUnits) {
                    if (unit._30 & 4)
                        unit.m13();
                }
            }
        }
    }
    if (at_end) {
        for (auto& list : _3660->mGroupLists) {
            for (auto& group : list.mUnits) {
                if (!group.mEntry || !group.mRecord || group.mRecord->_c < 0)
                    continue;
                for (auto& unit : group.mUnits) {
                    if (unit._30 & 4)
                        unit.m13();
                }
            }
        }
    }
}

// 0x71009fa2f8
void ScreenAppPictureBook::m100() {
    if (_3658)
        _3658->sub_710093F594(false);
    if (_3660)
        _3660->sub_710093F594(false);
}

// ScreenAppCamera
// 0x71009db72c (CSV ScreenAppCamera::m99)
void ScreenAppCamera::m99() {
    getStateMachine().changeState(&sUnk_71025dcca0);
    ksys::gdt::setFlag_IsOpenAppCamera(true, false);
}

namespace {
// The zoom step per frame of the camera (hold up / down); the original table is at 0x7101e78e7c.
const f32 sZoomSpeeds[2] = {0.01f, -0.01f};
}  // namespace

// 0x71009d9028: runs the camera zoom: steps it with the controller's up / down holds, clamps it to 0 - 1, applies
// it to the zoom animator and the game data flag, and drives the "mc_zoomLoop" / "mc_zoomEnd" sounds
// NON_MATCHING: zoom_moving lands in w8 instead of w9 (the event pointer then takes x9 instead of x8) and the
// second cset's `and` is emitted before the last cset and the `orr` instead of after them
void ScreenAppCamera::sub_71009D9028() {
    bool zoom_moving;
    bool zoom_ended;
    if (isHoldMaybe(0x30000)) {
        const f32 prev_zoom = _3640;
        f32 speed = 0.01f;
        if ((_292 & 0x40) && sub_71010AA9D0() && mUIController && mUIController->isHold(0x20000))
            speed = sZoomSpeeds[1];
        _3644 = sead::Mathf::clamp(speed + _3644, -0.06f, 0.06f);
        _3640 = sead::Mathf::clamp(_3644 + _3640, 0.0f, 1.0f);
        ksys::gdt::setFlag_CameraZoom(_3640, false);
        if (_3630)
            _3630->Stop(_3640 * 100.0f);
        if (prev_zoom != _3640) {
            zoom_moving = _3640 != 0.0f && _3640 != 1.0f;
            zoom_ended = _3640 == 0.0f || _3640 == 1.0f;
        } else {
            zoom_ended = false;
            zoom_moving = false;
        }
    } else {
        zoom_ended = false;
        zoom_moving = false;
        _3644 = 0.0f;
    }

    if (zoom_moving) {
        if (!_3648.isActive())
            _3648 = static_cast<eui::SoundLink2User*>(_f0)->searchAndEmit("mc_zoomLoop");
    } else if (_3648.isActive()) {
        _3648.fade(-1);
    }
    if (zoom_ended)
        invokeSoundLink2Event_("mc_zoomEnd");
}

// 0x71009d92e8: fades the camera sound and enters the camera mode
void ScreenAppCamera::m158() {
    _3648.fade();
    _3618->PlayAuto(1.0f);
    Manager::instance()->sub_7100A7CA68();
    _4019 = Unk_71025d1740::instance()->sub_7100901A90(false);
    _4018 = true;
}

// 0x71009d9400
void ScreenAppCamera::m159() {
    if (_4018) {
        if (!_4019)
            _4019 = Unk_71025d1740::instance()->sub_7100901A90(false);
        if (_4019) {
            _3618->PlayFromCurrent(eui::Animator::PlayType(0), 1.0f);
            sub_71009D94E8();
            _4018 = false;
        } else {
            _3618->StopAtMin();
        }
    }
    if (_3618->mRate == 0)
        ++_36ec;
    if (_36ec == 3) {
        mActiveCursorNode = nullptr;
        getStateMachine().changeState(&sUnk_71025dcd60);
    }
}

namespace {
// 0x71025d6dc0 (partially modelled): the ScreenAppCamera run's record table; only the sead::Buffer at +0x170 is
// used here, the rest of the original block is camera setup data.
struct CameraRunRecord {
    s32 id;
    s32 value;
    sead::SafeString text;
};
static_assert(sizeof(CameraRunRecord) == 0x18);
struct CameraRunStatics {
    u8 _0[0x170];
    sead::Buffer<CameraRunRecord> mRecords;
};
CameraRunStatics sUnk_71025d6dc0;
}  // namespace

// 0x71009d80b8
void ScreenAppCamera::sub_71009D80B8(s32 mode, s32 a2) {
    _4368._128 = 1;
    switch (mode) {
    case 0:
        _4368.sub_7100934308(sUnk_71025d6dc0.mRecords[0].id, sUnk_71025d6dc0.mRecords[0].text,
                             sUnk_71025d6dc0.mRecords[0].value);
        _4368.sub_7100934308(sUnk_71025d6dc0.mRecords[1].id, sUnk_71025d6dc0.mRecords[1].text,
                             sUnk_71025d6dc0.mRecords[1].value);
        _4368.sub_7100934308(sUnk_71025d6dc0.mRecords[2].id, sUnk_71025d6dc0.mRecords[2].text,
                             sUnk_71025d6dc0.mRecords[2].value);
        _4368.sub_7100934308(sUnk_71025d6dc0.mRecords[3].id, sUnk_71025d6dc0.mRecords[3].text,
                             sUnk_71025d6dc0.mRecords[3].value);
        _4368.sub_7100934308(sUnk_71025d6dc0.mRecords[4].id, sUnk_71025d6dc0.mRecords[4].text,
                             sUnk_71025d6dc0.mRecords[4].value);
        break;
    case 1:
        _4368.sub_7100934308(sUnk_71025d6dc0.mRecords[0].id, sUnk_71025d6dc0.mRecords[0].text,
                             sUnk_71025d6dc0.mRecords[0].value);
        _4368.sub_7100934308(sUnk_71025d6dc0.mRecords[1].id, sUnk_71025d6dc0.mRecords[1].text,
                             sUnk_71025d6dc0.mRecords[1].value);
        _4368.sub_7100934308(sUnk_71025d6dc0.mRecords[2].id, sUnk_71025d6dc0.mRecords[2].text,
                             sUnk_71025d6dc0.mRecords[2].value);
        _4368.sub_7100934308(sUnk_71025d6dc0.mRecords[3].id, sUnk_71025d6dc0.mRecords[3].text,
                             sUnk_71025d6dc0.mRecords[3].value);
        _4368.sub_7100934308(sUnk_71025d6dc0.mRecords[5].id, sUnk_71025d6dc0.mRecords[5].text,
                             sUnk_71025d6dc0.mRecords[5].value);
        break;
    }
    _4368.sub_7100934478(a2 & 1);
}

// 0x71009d9ad8
void ScreenAppCamera::sub_71009D9AD8() {
    if (_3618)
        _3618->StopAtMin();
    if (_3620)
        _3620->StopAtMin();
    if (_3628)
        _3628->StopAtMin();
    if (_3630)
        _3630->StopAtMin();
    if (_3638)
        _3638->StopAtMin();
    if (_3690)
        _3690->StopAtMin();
    if (_44c8)
        _44c8->StopAtMin();
    if (_44d0)
        _44d0->StopAtMin();
    if (auto* animator = mLayout->_70)
        animator->StopAtMin();
    if (auto* animator = mLayout->mCloseAnimator)
        animator->StopAtMin();
    if (auto* animator = mLayout->mOpenAnimator) {
        animator->StopAtMin();
        animator->Animate();
    }
    for (auto& animator : _278) {
        animator.StopAtMin();
        animator.Animate();
    }
}

// 0x71009db8e4
void ScreenAppCamera::m110() {
    sub_71009D9AD8();
}

// 0x71009da700 (placeholder name): the number of panes below `pane` whose names start with `prefix` (all of them for
// an empty prefix)
s32 sub_71009DA700(nn::ui2d::Pane* pane, const sead::SafeString& prefix) {
    if (!pane)
        return 0;
    s32 count = 0;
    for (auto& child : pane->GetChildList()) {
        if (sead::SafeString(child.GetName()).startsWith(prefix))
            ++count;
        count += sub_71009DA700(&child, prefix);
    }
    return count;
}

// 0x71009da7e8
s32 sub_71009DA7E8(sead::ObjArray<CollectedPane>* out, nn::ui2d::Pane* pane, const sead::SafeString& prefix) {
    s32 count = 0;
    if (!out || !pane)
        return count;
    for (auto& child : pane->GetChildList()) {
        if (sead::SafeString(child.GetName()).startsWith(prefix)) {
            ++count;
            out->emplaceBack(&child);
        }
        count += sub_71009DA7E8(out, &child, prefix);
    }
    return count;
}

// 0x71009db754
// NON_MATCHING: the child state test (1 / 3 / 5 / 7) is a bit-mask lookup in ours; the original tests 7, then
// (state - 1) <= 4 with an even (state - 1)
void ScreenAppCamera::m100() {
    ksys::gdt::setFlag_IsOpenAppCamera(false);
    _3688->startAnimCloseImpl_(false, true);
    _4080 = false;
    _36e8 = 0;
    if (_3610) {
        switch (_3610->_104) {
        case 1:
        case 3:
        case 5:
        case 7:
            _3610->m6(true);
            break;
        default:
            break;
        }
    }
    // called through a pointer in the original (not devirtualised)
    if (getStateMachine().getState()->getId() == (&sUnk_71025dcd60)->getId() ||
        // called through a pointer in the original (not devirtualised)
        getStateMachine().getState()->getId() == (&sUnk_71025dcd00)->getId()) {
        Manager::instance()->sub_7100A7CACC();
        if (_4019) {
            _4019 = false;
            Unk_71025d1740::instance()->sub_7100901A90(true);
        }
    }
    getStateMachine().changeState(&sUnk_710261ee98);
}

// 0x71009da8ec
void ScreenAppCamera::m94() {
    Manager::instance()->sub_7100A7F8E8(_44c0->_70);
    if (u32(mState - 1) <= 1)
        _4368.sub_7100933BDC();
    if (!sub_7100AA8DD4() && !(Manager::instance()->_64c30_bytes[2] & 0x20))
        sub_71009DA9E4();
    getStateMachine().run();
    if (ksys::MessageDispatcher::instance()->isProcessingOnCurrentThread()) {
        _1e0.sendMessageOnProcessingThread(_3658, static_cast<ksys::MessageType>(0x8800001), &_3640,
                                           false);
    } else {
        _1e0.sendMessage(_3658, static_cast<ksys::MessageType>(0x8800001), &_3640, false);
    }
    if (!isOpening())
        _44d8 = 0;
}

// 0x71009d7b80
void ScreenAppCamera::invoked1() {
    if (!_4028)
        return;
    const bool has_name = _4179 && _417c;
    const sead::SafeString& name = has_name ? _4198 : sead::SafeString::cEmptyString;
    SaveSystem::instance()->saveAlbumPicture(_4020, name, _4028);
    if (has_name) {
        _3688->startAnimCloseImpl_(false, true);
        _4102 = 0;
        _408a = 0;
        _41f0 = 1;
    }
    sub_71009D3AA0(_36f0++);
}

// 0x71009d7c40
void ScreenAppCamera::invoked2() {
    if (!_4038)
        return;
    SaveSystem::instance()->savePictureBook(_4030, _4198, _4038);
    sub_71009F70B0(_4198);
}

// 0x71009d9a4c
void ScreenAppCamera::m164() {
    if (_3638)
        _3638->StopAtMin();
    sub_71009D80B8(_4080, 1);
    delete[] _4020;
    delete[] _4030;
    _4020 = nullptr;
    _4030 = nullptr;
    if (_3b70.isValid()) {
        _3b70.deleteGPUMemBlock();
        _3b70.invalidate();
    }
}

// 0x71009db888
void ScreenAppCamera::m101() {
    if (_3b70.isValid()) {
        _3b70.deleteGPUMemBlock();
        _3b70.invalidate();
    }
    delete[] _4020;
    delete[] _4030;
    _4020 = nullptr;
    _4030 = nullptr;
}

// 0x71009db8ec
void ScreenAppCamera::sub_71009DB8EC() {
    eui::MessageString name;
    sub_7100AA2BDC(_40a8, &name);
    setWidgetString(_3688, "T_Name_00", name);
    if (_408a) {
        _4360 = 2.0f;
    } else if (_4088) {
        sead::FormatFixedSafeString<128> flag("IsRegisteredPictureBook_%s", _40a8.cstr());
        _4360 = ksys::gdt::getBoolByKey(flag) ? 1.0f : 0.0f;
    }
}

// 0x71009d9a28
void ScreenAppCamera::m163() {
    if (_3610 && _3610->_104)
        return;
    getStateMachine().changeState(&sUnk_71025dcca0);
}

// 0x71009d92e4
void ScreenAppCamera::m156() {}
// 0x71009d98b4
void ScreenAppCamera::m160() {}
// 0x71009dbd18
void ScreenAppCamera::m166() {}
// 0x71009dbd00
s32 ScreenAppCamera::m157() {
    return 0;
}
// 0x71009dbd08
s32 ScreenAppCamera::m161() {
    return 0;
}
// 0x71009dbd10
s32 ScreenAppCamera::m165() {
    return 0;
}

// ScreenAppMapDungeon
// 0x71009e33dc
void ScreenAppMapDungeon::m154() {}
// 0x71009e33e0
void ScreenAppMapDungeon::m155() {
    sub_71009E34D0();
    if (mSensorChild) {
        const s32 state = mSensorChild->_104;
        if (state == 7 || (u32(state - 1) <= 4 && ((state - 1) & 1) == 0)) {
            getStateMachine().changeState(&sUnk_71025de0c0);
            return;
        }
    }
    if (sead::DynamicCast<ScreenAppSystemWindow>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow)))
        getStateMachine().changeState(&sUnk_71025de0c0);
}
// 0x71009e3a8c
void ScreenAppMapDungeon::m156() {}
// 0x71009e3a90
void ScreenAppMapDungeon::m158() {}
// 0x71009e3a94
void ScreenAppMapDungeon::m159() {
    sub_71009E3B84();
    if (mSensorChild) {
        const s32 state = mSensorChild->_104;
        if (state == 7 || (u32(state - 1) <= 4 && ((state - 1) & 1) == 0))
            return;
    }
    if (!sead::DynamicCast<ScreenAppSystemWindow>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow)))
        getStateMachine().changeState(&sUnk_71025de060);
}
// 0x71009e4e80
void ScreenAppMapDungeon::m101() {
    auto* home = sead::DynamicCast<ScreenAppHome>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome));
    if (home) {
        home->sub_71009DC77C(1, nullptr);
        mLayout->mPane->SetPosition(
            nn::util::Float3{sead::Vector2f::zero.x, sead::Vector2f::zero.y, 0.0f});
    }
    getStateMachine().changeState(&sUnk_71025de060);
    sUnk_71025de180 &= ~1;
    sUnk_71025de182 = 0;
}
// 0x71009e3c90
void ScreenAppMapDungeon::m160() {}
// 0x71009e3c94
void ScreenAppMapDungeon::m162() {}
// 0x71009e3c98
void ScreenAppMapDungeon::m163() {}
// 0x71009e3c9c
void ScreenAppMapDungeon::m164() {}
// 0x71009e7de8
s32 ScreenAppMapDungeon::m157() {
    return 0;
}
// 0x71009e7df0
s32 ScreenAppMapDungeon::m161() {
    return 0;
}
// 0x71009e7df8
s32 ScreenAppMapDungeon::m165() {
    return 0;
}

// ScreenAppPictureBook
// 0x71009faecc
void ScreenAppPictureBook::m164() {}
// 0x71009fa028: refills the new-picture flags of the registered pictures and the selected index
// table, then switches the picture-book state for the current mode.
void ScreenAppPictureBook::m98() {
    sUnk_7102482788 = -1;
    if (_3620) {
        bool stopAtMin = sUnk_71025eb5b8 == 1;
        if (!stopAtMin)
            stopAtMin = Unk_71025d69f0::instance()->sub_710094F7AC(3);
        if (stopAtMin) {
            _3620->StopAtMin();
        } else {
            _3620->StopAtMax();
            if (_3658)
                _3658->sub_710093E42C(0, 1);
            return;
        }
    }

    sPictureBookState._20 = 0;
    memset(&sPictureBookState._514, 0xff, sizeof(sPictureBookState._514));
    memset(&sPictureBookState._320, 0, sizeof(sPictureBookState._320));
    for (u32 i = 0; i < u32(sPictureBookState._1c); ++i) {
        sead::FormatFixedSafeString<128> name("IsRegisteredPictureBook_%s",
                                              sUnk_71025dfca0[i].cstr());
        const bool registered = ksys::gdt::getBoolByKey(name, false);
        sPictureBookState._320[i] = registered;
        if (registered) {
            sPictureBookState._514[sPictureBookState._20] = s32(i);
            ++sPictureBookState._20;
        }
    }
    sub_71009F9D64();
    if (sUnk_71025eb5b4) {
        if (_3660) {
            _3660->sub_710093DAD4(5);
            _3660->sub_710093F278(sPictureBookState._20, 0);
            _3660->sub_710093EC3C(sUnk_71025eb5b0, 1);
        }
        if (_3628)
            _3628->StopAtMax();
        getStateMachine().changeState(&sUnk_71025eb4f0);
    } else {
        if (_3658)
            _3658->sub_710093EC3C(sUnk_71025eb5b0, 1);
        if (_3660)
            _3660->sub_710093DAE8(2);
        if (_3628)
            _3628->StopAtMin();
        getStateMachine().changeState(&sUnk_71025eb490);
    }
    if (sUnk_71025eb5b8 == 1) {
        sUnk_71025eb430.init(0.2777777910232544f);
        sUnk_71025eb430.setToEnd();
        if (_3658)
            _3658->sub_710093E42C(0, 1);
    }
    if (sUnk_71025eb5b8 == 2) {
        sUnk_71025eb430.init(0.5f);
        if (sPictureBookState._1 == 1)
            sUnk_71025eb430.setToEnd();
    }
}

// 0x71009fa6c8: stops the pair of animators, tells the home screen and, while the picture book page is
// still open, forwards the selected picture to the per-picture update.
void ScreenAppPictureBook::m154() {
    uking::ui::getHeap();
    if (_3638)
        _3640->StopAtMin();
    if (auto* home = sead::DynamicCast<ScreenAppHome>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome)))
        home->sub_71009DD800(true);
    if (getStateMachine().getPrevState()->getId() == (&sUnk_71025eb4f0)->getId()) {
        if (_3628)
            _3628->PlayAuto(-1.0f);
        if (_3660) {
            _3660->sub_710093DAE8(0);
            if (_3658)
                _3658->sub_710093EC3C(sPictureBookState._514[_3660->_2ec], 1);
        }
    }
}

// 0x71009fa824: runs the reference page: steps its page timer / counter, or on the sensor trigger
// opens the selected picture's message.
void ScreenAppPictureBook::m155() {
    if (!_3628)
        return;
    if (!_3658)
        return;
    if ((_3628->mFlags & 1) && _3660)
        _3660->sub_710093FF88();
    if (_3628->mFrame == 0.0f) {
        const s32 mode = sUnk_71025eb5b8;
        if (mode == 1) {
            if (sUnk_71025eb430.isDone()) {
                ++sUnk_7102482788;
                sUnk_71025eb430.reset();
                if (_3630 && sUnk_7102482788 == 0)
                    _3630->PlayAuto(1.0f);
            }
            sUnk_71025eb430.update();
            if (_3658)
                _3658->sub_710093F594(false);
            return;
        }
        if (mode == 2) {
            if (sPictureBookState._1 == 1) {
                if (Unk_71025d69f0::instance()->sub_710094F6F8()) {
                    sPictureBookState._1 = 0;
                    sUnk_7102482788 = 0;
                }
            } else if (sUnk_71025eb430.updateAndCheckEnded()) {
                sUnk_7102482788 = 0;
            }
            if (sUnk_7102482788 == 0) {
                sUnk_7102482788 = 1;
                invokeSoundLink2Event_("mc_AddPicture");
            }
            if (_3658)
                _3658->sub_710093F594(false);
            return;
        }

        if (mode == 3 && isTrigMaybe(2)) {
            sUnk_71025eb5b8 = 0;
            Unk_71025d69f0::instance()->sub_710094DCC4(1, -2);
        }
        if (isTrigMaybe(0x10)) {
            s32 local_index = -1;
            s32 entry_index = -1;
            if (_3658)
                _3658->sub_710093F10C(_3658->_310, &local_index, &entry_index);
            if (local_index >= 0 && entry_index >= 0) {
                const u64 page = entry_index;
                const u64 clamped = page < 5 ? page : 0;
                const s64 index = sPictureBookState._288[clamped] + local_index;
                if (sPictureBookState._320[index])
                    sub_71009F9F30(sUnk_71025dfca0[index]);
            }
        }
        if (_3658)
            _3658->sub_710093F594(true);
    }
}

// 0x71009faab0
void ScreenAppPictureBook::m158() {
    if (auto* home = sead::DynamicCast<ScreenAppHome>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome)))
        home->sub_71009DD800(false);
    if (getStateMachine().getPrevState()->getId() == (&sUnk_71025eb490)->getId()) {
        if (_3628)
            _3628->PlayAuto(1.0f);
        if (_3660)
            _3660->sub_710093DAD4(4);
    }
}
// 0x71009fabc0
void ScreenAppPictureBook::m159() {
    if (!_3628 || !_3660)
        return;
    if ((_3628->mFlags & 1) && _3658)
        _3658->sub_710093FF88();
    if (_3628->mFrame != _3628->GetFrameSize())
        return;
    if (_3660)
        _3660->sub_710093F594(true);
    if (isTrigMaybe(1)) {
        if (ksys::gdt::getFlag_IsGet_Obj_SheikSensorLv2(false))
            getStateMachine().changeState(&sUnk_71025eb550);
    } else if (isTrigMaybe(2)) {
        invokeSoundLink2Event_("mc_Individual_Cancel");
        getStateMachine().changeState(&sUnk_71025eb490);
    }
}
// 0x71009face0
void ScreenAppPictureBook::m162() {
    createAndLoadScreenIfNeededImpl(ScreenId::AppSystemWindow, nullptr);
    if (auto* screen = sead::DynamicCast<ScreenAppSystemWindow>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow)))
        screen->m154(2);
}
// 0x71009fb208
s32 ScreenAppPictureBook::m157() {
    return 0;
}
// 0x71009fb210
s32 ScreenAppPictureBook::m161() {
    return 0;
}
// 0x71009fb218
s32 ScreenAppPictureBook::m165() {
    return 0;
}


// ScreenAppCamera creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_7102480388[] = {
    {"Pa_Guide_", sub_71009D7198, 1},
    {"Pa_SystemWindow_00", sub_71009D7294, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102480378(sUnk_7102480388);
// 0x71009d7168
const sead::Buffer<const ChildControlCreatorEntry>* Unk_71024803b8::getEntries() const {
    return &sUnk_7102480378;
}

// 0x71009d7198
ScreenChild* sub_71009D7198(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) ScreenChildEx(layout_ex);
}

ScreenChild* sub_71009D7294(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247dc90(layout_ex);
}

// ScreenAppMapDungeon creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_7102481048[] = {
    {"Pa_SensorBox_00", sub_71009DE3F4, 0},
    {"Pa_SensorIcon_00", sub_71009DE4F0, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102481038(sUnk_7102481048);
// 0x71009de3c4
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102481078::getEntries() const {
    return &sUnk_7102481038;
}

ScreenChild* sub_71009DE3F4(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247c010(layout_ex);
}

ScreenChild* sub_71009DE4F0(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247c6c0(layout_ex);
}

}  // namespace uking::ui

// 0x71009f345c
// 0x71009f34cc: sets up the picture book unit's texture capture part, registers it and creates its four
// state animators.
void Unk_71024826c0::m4(sead::Heap* heap) {
    _48.sub_71009CBD48(heap, _8, "P_Capture_00");
    _48.sub_71009CBDE8(_8, "PicLoad");
    uking::ui::sUnk_71025eb5c0.pushBack(&_48);
    if (_8) {
        _330 = _8->tryCreateAnimatorAuto("Hatena", false);
        _338 = _8->tryCreateAnimatorAuto("New", false);
        _340 = _8->tryCreateAnimatorAuto("Born", false);
        if (_340)
            _340->StopAtMax();
        _348 = _8->tryCreateAnimatorAuto("DLC", false);
        if (_348)
            _348->StopAtMin();
    }
}

Unk_71024826c0::~Unk_71024826c0() = default;

// 0x71009f3b20
void Unk_71024826c0::m8() {
    _48.sub_71009CC3A0();
}

// 0x71009f43e0
void Unk_71024826c0::m14() {
    _48.sub_71009CC3A0();
}

// 0x71009f47f8
Unk_7102482790::~Unk_7102482790() = default;

// The picture book entry setup for this unit type (template in uiScreens.h)
// 0x71009f95c4
template void uking::ui::ScreenAppPictureBookUnk::setupEntry<Unk_71024826c0>(
    sead::Heap* heap, s32 index, const uking::ui::ScreenAppPictureBookEntry::Params& params);
// NON_MATCHING (createUnits<Unk_7102482790>, 0x71009fb6fc): the original keeps the second memset's address in a
// callee-saved register and spills the end iterator; same code otherwise
// 0x71009fb62c
template void uking::ui::ScreenAppPictureBookUnk::setupEntry<Unk_7102482790>(
    sead::Heap* heap, s32 index, const uking::ui::ScreenAppPictureBookEntry::Params& params);
