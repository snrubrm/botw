#include "Game/UI/uiScreens.h"

// Trivial overrides of the leaf screens' own state-callback slots (154+).
namespace uking::ui {

// 0x7100a41874
void ScreenRupee::m154() {}

// 0x7100a41c8c
s32 ScreenRupee::m157() { return 0; }

// 0x7100a41a68
void ScreenRupee::m160() {}

// 0x7100a41c94
s32 ScreenRupee::m161() { return 0; }

// 0x7100a41b28
void ScreenRupee::m164() {}

// 0x7100a41c9c
s32 ScreenRupee::m165() { return 0; }

// 0x7100a41ca4
s32 ScreenRupee::m169() { return 0; }

// 0x7100a0f238
void ScreenKologNum::m154() {}

// 0x7100a0f600
s32 ScreenKologNum::m157() { return 0; }

// 0x7100a0f478
void ScreenKologNum::m160() {}

// 0x7100a0f608
s32 ScreenKologNum::m161() { return 0; }

// 0x7100a0f514
void ScreenKologNum::m164() {}

// 0x7100a0f610
s32 ScreenKologNum::m165() { return 0; }

// 0x71009cf1bc
void ScreenAkashNum::m154() {}

// 0x71009cf988
s32 ScreenAkashNum::m157() { return 0; }

// 0x71009cf3ec
void ScreenAkashNum::m160() {}

// 0x71009cf990
s32 ScreenAkashNum::m161() { return 0; }

// 0x71009cf490
void ScreenAkashNum::m164() {}

// 0x71009cf998
s32 ScreenAkashNum::m165() { return 0; }

// 0x7100a22d7c
void ScreenMamoNum::m154() {}

// 0x7100a22dcc
void ScreenMamoNum::m156() {}

// 0x7100a230ac
s32 ScreenMamoNum::m157() { return 0; }

// 0x7100a22f24
void ScreenMamoNum::m160() {}

// 0x7100a230b4
s32 ScreenMamoNum::m161() { return 0; }

// 0x7100a22fc0
void ScreenMamoNum::m164() {}

// 0x7100a230bc
s32 ScreenMamoNum::m165() { return 0; }

// 0x71009ff6a4
void ScreenAppTool::m154() {}

// 0x71009ff6cc
void ScreenAppTool::m156() {}

// 0x7100a00050
s32 ScreenAppTool::m157() { return 0; }

// 0x71009ffad0
void ScreenAppTool::m159() {}

// 0x7100a00058
s32 ScreenAppTool::m161() { return 0; }

// 0x71009ffdac
void ScreenAppTool::m164() {}

// 0x7100a00060
s32 ScreenAppTool::m165() { return 0; }

// 0x7100a00068
s32 ScreenAppTool::m169() { return 0; }

// 0x71009d6c24
s32 ScreenAppAlbum::m157() { return 0; }

// 0x71009d6c2c
s32 ScreenAppAlbum::m161() { return 0; }

// 0x71009d6c34
s32 ScreenAppAlbum::m165() { return 0; }

// 0x71009d63d4
void ScreenAppAlbum::m168() {}

// 0x71009d6c3c
s32 ScreenAppAlbum::m169() { return 0; }

// 0x7100a21928
void ScreenMainShortCut::m154() {}

// 0x7100a219c8
void ScreenMainShortCut::m156() {}

// 0x7100a22324
s32 ScreenMainShortCut::m157() { return 0; }

// 0x7100a2232c
s32 ScreenMainShortCut::m161() { return 0; }

// 0x7100a22090
void ScreenMainShortCut::m162() {}

// 0x7100a22120
void ScreenMainShortCut::m164() {}

// 0x7100a22334
s32 ScreenMainShortCut::m165() { return 0; }

// 0x7100a2233c
s32 ScreenMainShortCut::m169() { return 0; }

// 0x7100a3ee40
s32 ScreenPauseMenu::m157() { return 0; }

// 0x7100a3ee48
s32 ScreenPauseMenu::m161() { return 0; }

// 0x7100a3ee50
s32 ScreenPauseMenu::m165() { return 0; }

// 0x7100a3ee58
s32 ScreenPauseMenu::m169() { return 0; }

// 0x7100a0a9a4
void ScreenGameOver::m155() {}

// 0x7100a0ac40
s32 ScreenGameOver::m157() { return 0; }

// 0x7100a0ab54
void ScreenGameOver::m160() {}

// 0x7100a0ac48
s32 ScreenGameOver::m161() { return 0; }

// 0x7100a4368c
void ScreenSaveTransferWindow::m156() {}

// 0x7100a46534
s32 ScreenSaveTransferWindow::m157() { return 0; }

// 0x7100a4376c
void ScreenSaveTransferWindow::m160() {}

// 0x7100a4653c
s32 ScreenSaveTransferWindow::m161() { return 0; }

// 0x7100a438b4
void ScreenSaveTransferWindow::m164() {}

// 0x7100a46544
s32 ScreenSaveTransferWindow::m165() { return 0; }

// 0x7100a438d8
void ScreenSaveTransferWindow::m168() {}

// 0x7100a4654c
s32 ScreenSaveTransferWindow::m169() { return 0; }

// 0x71009d0c4c
void ScreenAmiiboWindow::m155() {}

// 0x71009fc49c
void ScreenAppSystemWindow::m155() {}

// 0x7100a04c38
void ScreenDLCSinJuAkashiNum::m154() {}

// 0x7100a05004
s32 ScreenDLCSinJuAkashiNum::m157() { return 0; }

// 0x7100a04e58
void ScreenDLCSinJuAkashiNum::m160() {}

// 0x7100a0500c
s32 ScreenDLCSinJuAkashiNum::m161() { return 0; }

// 0x7100a04f18
void ScreenDLCSinJuAkashiNum::m164() {}

// 0x7100a05014
s32 ScreenDLCSinJuAkashiNum::m165() { return 0; }

// 0x71009f28a8
s32 ScreenAppMap::getSlink2LocalPropertyNum_() const {
    return 2;
}

}  // namespace uking::ui
