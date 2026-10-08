#include "Game/UI/euiButton.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

static const sead::SafeString sUnk_7102482168 = "Pa_CheckBtn_00";

// 0x71009f2b84
void ScreenAppMenuBtn::m93(sead::Heap*) {
    _3618 = static_cast<eui::AnimButton*>(mButtonGroup->FindControlByName("Pa_Btn_00"));
    if (_3618) {
        _3618->mLayout->GetPane()->SetVisible(false);
        _3618->mLayout->sub_7100BDDE7C(false, 1, true);
        _3618->mFlags |= 0x200;
        _3618->mFlags |= 0x20;
        _3610 = _3618->mLayout->tryCreateAnimatorAutoWithWarning("TexPattern", true);
    }
    const char* name = sUnk_7102482168.cstr();
    auto* button = static_cast<eui::ButtonBase*>(mButtonGroup->FindControlByName(name));
    if (button) {
        button->setFlag10(true);
        button->mLayout->GetPane()->SetVisible(true);
    }
}

// 0x71009f2c7c
void ScreenAppMenuBtn::m107(eui::AnimButton* button) {
    if (sUnk_7102482168 != button->mName)
        return;
    if (auto* check = nn::font::DynamicCast<eui::CheckButton>(button))
        Manager::instance()->sub_7100A7A72C(check->mChecked);
}

}  // namespace uking::ui
