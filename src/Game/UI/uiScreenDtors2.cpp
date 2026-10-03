#include "Game/UI/uiScreens.h"

// Screen<Name> destructors whose original keeps the vtable pointer stores (the destructor is user-provided
// with an empty body; upstream has the same form for GameDataFlagSelector::~GameDataFlagSelector() { ; },
// commit 96101229). The classes' members that would explain the stores are not modelled yet.
namespace uking::ui {

ScreenMiniGame::~ScreenMiniGame() { ; }
ScreenShopBtnList20::~ScreenShopBtnList20() { ; }
ScreenTime::~ScreenTime() { ; }
ScreenChallengeWin::~ScreenChallengeWin() { ; }
ScreenHardMode::~ScreenHardMode() { ; }
ScreenControllerWindow::~ScreenControllerWindow() { ; }
ScreenDLCWindow::~ScreenDLCWindow() { ; }

}  // namespace uking::ui
