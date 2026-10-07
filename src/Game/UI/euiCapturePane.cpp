#include "Game/UI/euiCapturePane.h"

#include <nn/ui2d/Pane.h>
#include <heap/seadHeap.h>
#include <nn/ui2d/ResExtUserData.h>

namespace eui {

// NON_MATCHING: byte-to-float conversion and color-store scheduling differ.
// 0x7100bf14f0
sead::Color4f* CapturePane::setupClearColor_(sead::Heap* heap, nn::ui2d::Pane* pane,
                                           LayoutEx*, sead::BitFlag<u8>* flags) {
    const auto* rgb = pane->FindExtUserDataByName("CaptureBGColor");
    const auto* alpha = pane->FindExtUserDataByName("CaptureBGAlpha");
    if (rgb && rgb->GetCount() == 3) {
        const auto* values = rgb->GetIntArray();
        auto* color = new (heap, 8) sead::Color4f;
        color->r = static_cast<u8>(values[0]) / 255.0f;
        color->g = static_cast<u8>(values[1]) / 255.0f;
        color->b = static_cast<u8>(values[2]) / 255.0f;
        color->a = 0.0f;
        if (alpha)
            color->a = alpha->GetIntArray()[0] / 255.0f;
        return color;
    }
    if (alpha && alpha->GetIntArray()[0] == 255)
        flags->setBit(1);
    return nullptr;
}

// 0x7100bf15ec
void CapturePane::setupCaptureOutputAlpha255_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags) {
    const auto* data = pane->FindExtUserDataByName("CaptureOutputAlpha");
    if (data && data->GetIntArray()[0] == 255)
        flags->setBit(3);
}

// 0x7100bf1634
void CapturePane::setupCaptureOriginalSize_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags) {
    if (pane->FindExtUserDataByName("CaptureOriginalSize"))
        flags->setBit(4);
}

}  // namespace eui
