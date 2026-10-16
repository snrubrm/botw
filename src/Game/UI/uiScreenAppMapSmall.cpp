#include "Game/UI/uiManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/euiTextSearcher.h"
#include "Game/UI/euiMessageMgr.h"
#include <gfx/nin/seadGraphicsNvn.h>
#include <nn/ui2d/BuildTypes.h>
#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiScreenChildStates.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/euiAnimator.h"

namespace uking::ui {

// 0x71009d9c40
// NON_MATCHING: as eui::Screen::doBuildLayout_: our BuildResultInformation is zero-initialised (one extra stp) and
// the stack slots / load order around it differ.
void ScreenAppCamera::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_71024803b8 creator(mButtonGroup, &mControls, &_50);
    eui::TextSearcher searcher(eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_()), mTagProcessor);
    auto* device = sead::GraphicsNvn::instance()->getNnDevice();
    nn::ui2d::Layout::BuildOption options{};
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, device, accessor, &creator, &searcher, options, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x71009e0e24
// NON_MATCHING: as eui::Screen::doBuildLayout_: our BuildResultInformation is zero-initialised (one extra stp) and
// the stack slots / load order around it differ.
void ScreenAppMapDungeon::doBuildLayout_(const sead::SafeString& name, nn::ui2d::ResourceAccessor* accessor) {
    Unk_7102481078 creator(mButtonGroup, &mControls, &_50);
    eui::TextSearcher searcher(eui::MessageMgr::instance()->getLayoutMessageSet(getMessageName_()), mTagProcessor);
    auto* device = sead::GraphicsNvn::instance()->getNnDevice();
    nn::ui2d::Layout::BuildOption options{};
    nn::ui2d::BuildResultInformation result;
    mLayout->BuildWithName(&result, device, accessor, &creator, &searcher, options, name.cstr(), false);
    sub_71010ABF8C(creator.getEntries());
}

// 0x71009ea030
bool ScreenAppMap::sub_71009EA030() const {
    if (_3c98)
        return _3c98->mController.sub_71009CBFA4();
    return true;
}

// 0x71009e0df8
bool ScreenAppMapDungeon::sub_71009E0DF8() const {
    if (mSensorChild)
        return mSensorChild->mController.sub_71009CBFA4();
    return true;
}


// 0x71009ef488
// NON_MATCHING: position load and negation order.
void ScreenAppMap::sub_71009EF488(const sead::Vector3f* pos, s32 scale_level) {
    if (_3610) {
        UiSubsys1::instance()->sub_7100968AF8(0);
        _3ad4 = pos->x;
        _3ad8 = -pos->z;
        _3adc = scale_level;
    }
}

// 0x71009ef57c: the input speed is unused; the controller is always started at speed 1.
void ScreenAppMap::sub_71009EF57C(f32, s32 type) {
    if (_3c90) {
        switch (type) {
        case 0:
            _3c90->sub_71009C1474(1.0f, 0);
            break;
        case 1:
            _3c90->sub_71009C1474(1.0f, 1);
            break;
        }
    }
}

// 0x71009ef5a8
bool ScreenAppMap::sub_71009EF5A8(s32 type) {
    if (_3c90) {
        switch (type) {
        case 0:
            return _3c90->sub_71009C1814(0);
        case 1:
            return _3c90->sub_71009C1814(1);
        }
    }
    return true;
}

// 0x71009ef4ec (CSV unnamed)
void ScreenAppMap::sub_71009EF4EC(s32 a1, s32 a2) {
    if (u32(a1 - 3) > 1)
        return;
    _3ad2 = !(a2 & 1);
    UiSubsys1::instance()->sub_7100968AF8(a1);
}

// 0x71009ef51c (CSV unnamed)
void ScreenAppMap::sub_71009EF51C(s32 a1) {
    if (u32(a1) <= 0xe) {
        UiSubsys1::instance()->set128(a1);
        bool ready = UiSubsys1::instance()->sub_7100968BD8();
        if (ready)
            UiSubsys1::instance()->sub_7100968AF8(2);
        else
            UiSubsys1::instance()->sub_7100968AF8(1);
        _3ad2 = 0;
    }
}

// 0x71009eecd0
bool ScreenAppMap::sub_71009EECD0() const {
    if (!_3610 || !_3610->sub_71009AEF7C())
        return false;
    return isOpened();
}

// 0x71009eed10
s32 ScreenAppMap::sub_71009EED10() const {
    return _3610->sub_71009AEF7C();
}


// ScreenAppMap creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_7102481768[] = {
    {"Pa_Map_00", sub_71009E7F60, 0},
    {"Pa_MapIcon_00", sub_71009E805C, 0},
    {"Pa_PlayerNavi_00", sub_71009E8158, 0},
    {"Pa_StampBox_00", sub_71009E8254, 0},
    {"Pa_SensorIcon_00", sub_71009DE4F0, 0},
    {"Pa_SensorBox_00", sub_71009DE3F4, 0},
    {"Pa_Sensor_00", sub_71009E8350, 0},
    {"Pa_Comp_00", sub_71009E844C, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_7102481758(sUnk_7102481768);
// 0x71009e7f30
const sead::Buffer<const ChildControlCreatorEntry>* Unk_7102481828::getEntries() const {
    return &sUnk_7102481758;
}
// 0x71009e7f3c
Unk_7102481828::~Unk_7102481828() = default;

ScreenChild* sub_71009E7F60(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) ScreenAppMapWidget(layout_ex);
}

ScreenChild* sub_71009E805C(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_7102478048(layout_ex);
}

ScreenChild* sub_71009E8158(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_7102479838(layout_ex);
}

ScreenChild* sub_71009E8254(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247d8f8(layout_ex);
}

ScreenChild* sub_71009E8350(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247c368(layout_ex);
}

ScreenChild* sub_71009E844C(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_7102477c30(layout_ex);
}

// 0x71009f1e9c
void sub_71009F1E9C() {
    createAndLoadScreenIfNeededImpl(ScreenId::AppSystemWindow, nullptr);
    auto* screen = sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
    if (screen)
        screen->m154(5);
}

// 0x71009f1f64
void sub_71009F1F64() {
    createAndLoadScreenIfNeededImpl(ScreenId::AppSystemWindow, nullptr);
    auto* screen = sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
    if (screen)
        screen->m154(6);
}

// 0x71009f202c
void sub_71009F202C() {
    createAndLoadScreenIfNeededImpl(ScreenId::AppSystemWindow, nullptr);
    auto* screen = sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
    if (screen)
        screen->m154(7);
}

// 0x71009f2204
void sub_71009F2204() {
    auto* screen = sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
    if (!screen || screen->isClosed())
        return;
    if (ScreenAppSystemWindow::sub_71009FC4A0() != 0)
        return;
    sub_7100A9AC84(UiSubsys1::instance()->_3a0);
    PauseMenuDataMgr::instance()->_444fc = 2;
    Manager::instance()->sub_7100A7C8D4();
}

// 0x71009e3b84
void sub_71009E3B84() {
    auto* screen = sead::DynamicCast<ScreenAppSystemWindow>(
        eui::ScreenMgr::instance()->getScreen(ScreenId::AppSystemWindow));
    if (!screen || screen->_3610 != 8 || !screen->isClosedOrClosing())
        return;
    if (ScreenAppSystemWindow::sub_71009FC4A0() != 0)
        return;
    Manager::instance()->setWarpDestination(sub_7100A9EEA4(), sub_7100A9EEF4());
    Manager::instance()->sub_7100A7C9C0();
}

// 0x71009e70b8
void ScreenAppMapDungeon::sub_71009E70B8() {
    Unk_71025d69f0::instance()->sub_710094E064();
    close(-1);
    if (auto* screen = sead::DynamicCast<ScreenAppMap>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppMap)))
        screen->close(-1);
}

// 0x71009f273c
void ScreenAppMap::sub_71009F273C() {
    Unk_71025d69f0::instance()->sub_710094E064();
    close(-1);
}

}  // namespace uking::ui
