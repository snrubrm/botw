#include "Game/UI/uiScreens.h"

// The trivial destructors of the classes that derive directly from uking::ui::Screen (not ScreenEx). Defining them
// emits the vtables / RTTI of these classes in this TU; they must not share a TU with the ScreenEx leaf classes (the
// inline parent RTTI chain of those changes).
namespace uking::ui {

ScreenFadeDemo::~ScreenFadeDemo() = default;
ScreenChangeControllerNN::~ScreenChangeControllerNN() = default;
ScreenHomeNixSign::~ScreenHomeNixSign() = default;
ScreenBoxCursorTV::~ScreenBoxCursorTV() = default;
ScreenLoadSaveIcon::~ScreenLoadSaveIcon() = default;
ScreenMessageTips::~ScreenMessageTips() = default;
ScreenMessage3D::~ScreenMessage3D() = default;
// The original D1 keeps the vtable stores (upstream GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
ScreenMainDungeon::~ScreenMainDungeon() { ; }
ScreenErrorViewer::~ScreenErrorViewer() = default;
ScreenDemoMessage::~ScreenDemoMessage() = default;
ScreenMessageDialog::~ScreenMessageDialog() = default;

}  // namespace uking::ui
