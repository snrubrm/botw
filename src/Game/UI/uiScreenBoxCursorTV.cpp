#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAnimator.h"

namespace uking::ui {

ScreenBoxCursorTV::ScreenBoxCursorTV() : Screen() {}
ScreenBoxCursorTV::~ScreenBoxCursorTV() = default;

// 0x710109db4c
const char* ScreenBoxCursorTV::getLayoutName_() const {
    return "Cursor_00";
}

// 0x710109db58
void ScreenBoxCursorTV::m93(sead::Heap*) {
    if (eui::LayoutEx* layout = sub_7100BEAFB0("Pa_Cursor_00")) {
        _300 = layout->tryCreateAnimatorAuto("Type", true);
        if (_300)
            _300->StopAtMin();
    }
}

}  // namespace uking::ui
