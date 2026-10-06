#pragma once

#include <controller/seadMaskControllerWrapper.h>

namespace eui {

// The controller wrapper of a screen (Screen::mUIController, 0x218 bytes; constructor 0x7100becd40).
class UIController : public sead::MaskControllerWrapper {
    SEAD_RTTI_OVERRIDE(UIController, sead::MaskControllerWrapper)
public:
    UIController();

    sead::Controller* getController() const { return mController; }
};

static_assert(sizeof(UIController) == 0x218);

}  // namespace eui
