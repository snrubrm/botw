#pragma once

#include <controller/seadControllerWrapperBase.h>

namespace eui {

// The controller wrapper of a screen (Screen::mUIController, 0x218 bytes; constructor 0x7100becd40). Only the
// part that is used so far is declared.
class UIController : public sead::ControllerWrapperBase {
public:
    UIController();
    void calc(u32 prev_hold, bool prev_pointer_on) override;
};

}  // namespace eui
