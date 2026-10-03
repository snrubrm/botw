#include "Game/UI/uiScreens.h"

// Screen<Name> destructors of classes whose members are not modelled yet. NON_MATCHING: the original
// destructors destroy members (the bodies / thunks below do not match and are left unnamed in the CSV);
// they exist so that the classes' vtables (and with them the matching RTTI functions) are emitted.
namespace uking::ui {

ScreenTitle::~ScreenTitle() = default;
ScreenMainScreen3D::~ScreenMainScreen3D() = default;
ScreenAppCamera::~ScreenAppCamera() = default;
ScreenEnergyMeterDLC::~ScreenEnergyMeterDLC() = default;
ScreenMessageGet::~ScreenMessageGet() = default;
ScreenDoCommand::~ScreenDoCommand() = default;
ScreenSousaGuide::~ScreenSousaGuide() = default;
ScreenShopBtnList15::~ScreenShopBtnList15() = default;
ScreenShopInfo::~ScreenShopInfo() = default;
ScreenRupee::~ScreenRupee() = default;
ScreenKologNum::~ScreenKologNum() = default;
ScreenAkashNum::~ScreenAkashNum() = default;
ScreenMamoNum::~ScreenMamoNum() = default;
ScreenAppTool::~ScreenAppTool() = default;
ScreenAppAlbum::~ScreenAppAlbum() = default;
ScreenAppPictureBook::~ScreenAppPictureBook() = default;
ScreenAppMapDungeon::~ScreenAppMapDungeon() = default;
ScreenMainScreen::~ScreenMainScreen() = default;
ScreenPickUp::~ScreenPickUp() = default;
ScreenMessageTipsRunTime::~ScreenMessageTipsRunTime() = default;
ScreenAppMap::~ScreenAppMap() = default;
ScreenAppHome::~ScreenAppHome() = default;
ScreenMainShortCut::~ScreenMainShortCut() = default;
ScreenPauseMenu::~ScreenPauseMenu() = default;
ScreenPauseMenuInfo::~ScreenPauseMenuInfo() = default;
ScreenSaveTransferWindow::~ScreenSaveTransferWindow() = default;
ScreenOptionWindow::~ScreenOptionWindow() = default;
ScreenSystemWindow01::~ScreenSystemWindow01() = default;
ScreenPauseMenuRecipe::~ScreenPauseMenuRecipe() = default;
ScreenStaffRoll::~ScreenStaffRoll() = default;
ScreenStaffRollDLC::~ScreenStaffRollDLC() = default;
ScreenDLCSinJuAkashiNum::~ScreenDLCSinJuAkashiNum() = default;
ScreenKeyBoradTextArea::~ScreenKeyBoradTextArea() = default;
ScreenFadeStatus::~ScreenFadeStatus() = default;

}  // namespace uking::ui
