#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>

namespace nn::ui2d {
class Pane;
}

namespace eui {

// Only the static resource-policy helpers are recovered here. The capture
// pane's object layout, construction and virtual interface are not modeled.
class CapturePane {
public:
    static void setupCaptureOutputAlpha255_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags);
    static void setupCaptureOriginalSize_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags);
};

}  // namespace eui
