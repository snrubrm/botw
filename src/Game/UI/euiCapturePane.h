#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include <gfx/seadColor.h>

namespace nn::ui2d {
class Pane;
}

namespace sead {
class Heap;
}

namespace eui {

class LayoutEx;

// Only the static resource-policy helpers are recovered here. The capture
// pane's object layout, construction and virtual interface are not modeled.
class CapturePane {
public:
    static sead::Color4f* setupClearColor_(sead::Heap*, nn::ui2d::Pane*, LayoutEx*,
                                          sead::BitFlag<u8>* flags);
    static void setupCaptureOutputAlpha255_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags);
    static void setupCaptureOriginalSize_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags);
};

}  // namespace eui
