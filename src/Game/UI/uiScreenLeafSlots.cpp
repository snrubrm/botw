#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiScreenChildStates.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "Game/UI/uiManager.h"
#include "Game/Scene/gameScene.h"

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

// 0x71009ec01c (CSV ScreenAppMap::demoLeave)
void ScreenAppMap::demoLeave() {
    UiSubsys1::instance()->sub_7100968844();
    _3ad1 = 1;
}

// 0x71009eaf40 (CSV ScreenAppMap::m83)
void ScreenAppMap::m83() {
    sub_71009EACC0(0);
    getStateMachine().changeState(&sUnk_71025df180);
    if (_3638) {
        if (wm::isFindDungeonActivated())
            _3638->StopAtMin();
        else
            _3638->StopAtMax();
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
// 0x71009e3a8c
void ScreenAppMapDungeon::m156() {}
// 0x71009e3a90
void ScreenAppMapDungeon::m158() {}
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
