#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiUI.h"

namespace uking::ui {

// 0x710109de68
ScreenChangeControllerNN::ScreenChangeControllerNN() : Screen() {}

ScreenChangeControllerNN::~ScreenChangeControllerNN() = default;

// 0x710109deac
void ScreenChangeControllerNN::m94() {
    if (isOpened())
        close(-4);
}

// 0x710109df74
const char* ScreenChangeControllerNN::getLayoutName_() const {
    return "ChangeControllerNN_00";
}

}  // namespace uking::ui
