#include "Game/UI/uiScreens.h"
#include "Game/UI/euiPartsEx.h"
#include <nn/ui2d/ResExtUserData.h>
#include "KingSystem/System/SeadController.h"

namespace uking::ui {

// 0x71010aa230 (CSV ScreenBase::dtorDelete)
ScreenBase::~ScreenBase() = default;

// 0x71010a9f44 (CSV ScreenBase::getAnimationStep_)
f32 ScreenBase::getAnimationStep_() const {
    return eui::ScreenMgr::instance()->getAnimationStep();
}

// 0x71010a9fc0 (CSV ScreenBase::getArchiveName_)
const char* ScreenBase::getArchiveName_() const {
    return "Common";
}

// 0x71010a9b48
const char* ScreenBase::replacePartsLayoutName(const char* name, eui::PartsEx* parts, eui::LayoutEx*) {
    const auto* data = parts->FindExtUserDataByName("ReplacePartsForNN");
    if (data && data->GetType() == nn::ui2d::ExtUserDataType_String)
        return data->GetString();
    return name;
}

// 0x71010a9eb8 (CSV ScreenBase::registerController_)
void ScreenBase::registerController_() {
    if (isEnableControl())
        mUIController->registerWith(ksys::SeadController::getInstance(), false);
}

// NON_MATCHING (Screen::~Screen, 0x71010aa54c, and ScreenEx::~ScreenEx, 0x7100a47910): the original destructors
// destroy members that are not modelled yet. They are defaulted here so that the classes' vtables, and with
// them the RTTI functions (which match), are emitted.
Screen::~Screen() = default;
ScreenEx::~ScreenEx() = default;

}  // namespace uking::ui
