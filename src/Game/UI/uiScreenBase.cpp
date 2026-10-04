#include "Game/UI/uiScreens.h"

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

// NON_MATCHING (Screen::~Screen, 0x71010aa54c, and ScreenEx::~ScreenEx, 0x7100a47910): the original destructors
// destroy members that are not modelled yet. They are defaulted here so that the classes' vtables, and with
// them the RTTI functions (which match), are emitted.
Screen::~Screen() = default;
ScreenEx::~ScreenEx() = default;

}  // namespace uking::ui
