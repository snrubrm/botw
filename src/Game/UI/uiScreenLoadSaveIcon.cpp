#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiUI.h"

namespace uking::ui {

// 0x71010a3ea8
ScreenLoadSaveIcon::ScreenLoadSaveIcon() : Screen() {}

ScreenLoadSaveIcon::~ScreenLoadSaveIcon() = default;

// 0x71010a3f6c
void ScreenLoadSaveIcon::m93(sead::Heap*) {
    _300 = sub_7100BEAFB0("Pa_SaveIcon_00");
    _308 = _300->tryCreateAnimatorAutoWithWarning("Type", true);
    _310 = _300->tryCreateAnimatorAutoWithWarning("Color", true);
}

// 0x71010a3f10
void ScreenLoadSaveIcon::sub_71010A3F10(bool on) {
    if (!_318 && on)
        _31c = 90.0f;
    _31a = false;
    _320 = 0;
    _324 = 0;
    _318 = on;
}

// 0x71010a3f3c
void ScreenLoadSaveIcon::sub_71010A3F3C(bool on) {
    if (!_319 && on) {
        _31a = true;
        _320 = 16.0f;
        _324 = 10.0f;
    }
    _319 = on;
}

// 0x71010a42e0
void ScreenLoadSaveIcon::m101() {
    _31a = true;
    _300->startAnimCloseImpl_(false, true);
}

// 0x71010a4380
const char* ScreenLoadSaveIcon::getLayoutName_() const {
    return "LoadSaveIcon_00";
}

}  // namespace uking::ui
