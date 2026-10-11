#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiUI.h"

namespace uking::ui {

// 0x71010a2114
ScreenHomeNixSign::ScreenHomeNixSign() : Screen() {}

ScreenHomeNixSign::~ScreenHomeNixSign() = default;

// 0x71010a215c
void ScreenHomeNixSign::m98() {
    _2fc = 0;
}

// 0x71010a2164
void ScreenHomeNixSign::m94() {
    if (isOpened()) {
        if (_2fc < 30.0f)
            _2fc += getAnimationStep_();
        else
            close(-1);
    }
}

// 0x71010a2258
const char* ScreenHomeNixSign::getLayoutName_() const {
    return "HomeNixSign_00";
}

}  // namespace uking::ui
