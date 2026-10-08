#include "Game/UI/uiScreens.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/SafeDelete.h"

// Screen<Name> destructors of classes whose members are not modelled yet. NON_MATCHING: the original
// destructors destroy members (the bodies / thunks below do not match and are left unnamed in the CSV);
// they exist so that the classes' vtables (and with them the matching RTTI functions) are emitted.
namespace uking::ui {

ScreenTitle::~ScreenTitle() = default;
ScreenMainScreen3D::~ScreenMainScreen3D() = default;
ScreenAppCamera::~ScreenAppCamera() = default;
ScreenEnergyMeterDLC::~ScreenEnergyMeterDLC() = default;
// 0x7100a23904
ScreenMessageGet::~ScreenMessageGet() {
    delete _3658;
    _37d8.freeBuffer();
}
// 0x7100a07408
ScreenDoCommand::~ScreenDoCommand() {
    _3638.freeBuffer();
    _3648.freeBuffer();
}
ScreenSousaGuide::~ScreenSousaGuide() = default;
// 0x7100a4ad84
ScreenShopBtnList15::~ScreenShopBtnList15() = default;
// 0x7100a517cc
ScreenShopInfo::~ScreenShopInfo() {
    _3658.freeBuffer();
}
ScreenRupee::~ScreenRupee() = default;
ScreenKologNum::~ScreenKologNum() = default;
ScreenAkashNum::~ScreenAkashNum() = default;
ScreenMamoNum::~ScreenMamoNum() = default;
// 0x71009fce34 (D1): frees the array, then resets the ScreenAppHome slot 0
ScreenAppTool::~ScreenAppTool() {
    if (_3640) {
        delete[] _3640;
        _3640 = nullptr;
        _3638 = 0;
    }
    if (auto* screen = sead::DynamicCast<ScreenAppHome>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome)))
        screen->sub_71009DC77C(0, nullptr);
}
ScreenAppAlbum::~ScreenAppAlbum() = default;
ScreenAppPictureBook::~ScreenAppPictureBook() = default;
ScreenAppMapDungeon::~ScreenAppMapDungeon() = default;
ScreenMainScreen::~ScreenMainScreen() = default;
ScreenPickUp::~ScreenPickUp() = default;
ScreenMessageTipsRunTime::~ScreenMessageTipsRunTime() = default;
ScreenAppMap::~ScreenAppMap() = default;
// 0x71009dc3ec (D1): frees the array, then shows the skip screen again (m80(true)) if there is one
ScreenAppHome::~ScreenAppHome() {
    _37f8.freeBuffer();
    if (auto* screen = sead::DynamicCast<Screen>(eui::ScreenMgr::instance()->getScreen(ScreenId::Skip)))
        screen->m80(true);
}
// 0x7100a1f0bc
ScreenMainShortCut::~ScreenMainShortCut() {
    _3850.freeBuffer();
    _36f0.freeBuffer();
}
ScreenPauseMenu::~ScreenPauseMenu() = default;
ScreenPauseMenuInfo::~ScreenPauseMenuInfo() = default;
ScreenSaveTransferWindow::~ScreenSaveTransferWindow() = default;
// 0x7100a28cec
ScreenOptionWindow::~ScreenOptionWindow() {
    for (s32 i = 0, n = _3698.size(); i < n; ++i)
        delete _3698.at(i);
    _3698.freeBuffer();
}
ScreenSystemWindow01::~ScreenSystemWindow01() = default;
// 0x7100a324a0
ScreenPauseMenuRecipe::~ScreenPauseMenuRecipe() {
    if (_3698) {
        delete _3698;
        _3698 = nullptr;
    }
    if (_36a0) {
        delete _36a0;
        _36a0 = nullptr;
    }
    if (_36a8) {
        delete _36a8;
        _36a8 = nullptr;
    }
    if (_36b0) {
        delete _36b0;
        _36b0 = nullptr;
    }
    if (_36b8) {
        delete _36b8;
        _36b8 = nullptr;
    }
}
ScreenStaffRoll::~ScreenStaffRoll() = default;
ScreenStaffRollDLC::~ScreenStaffRollDLC() = default;
ScreenDLCSinJuAkashiNum::~ScreenDLCSinJuAkashiNum() = default;
ScreenKeyBoradTextArea::~ScreenKeyBoradTextArea() = default;
// 0x7100a098d0
ScreenFadeStatus::~ScreenFadeStatus() {
    _3658.freeBuffer();
    _3668.freeBuffer();
}

}  // namespace uking::ui
