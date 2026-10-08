#include "Game/UI/euiCapturePane.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiPartsEx.h"
#include "Game/UI/euiScreen.h"

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

// 0x7100bee240
void sub_7100BEE240(nn::ui2d::Pane* pane) {
    if (auto* capture = nn::font::DynamicCast<CapturePane>(pane))
        capture->_db = true;
    for (auto& child : pane->GetChildList())
        sub_7100BEE240(&child);
}

// NON_MATCHING: the original calls PartsEx::GetRuntimeTypeInfoStatic out of line (0x7100a4a4f8, shared with other
// callers); here it is inlined. Same for sub_7100BEE4D4.
// 0x7100bee334
void sub_7100BEE334(nn::ui2d::Pane* pane, LayoutEx* layout) {
    if (auto* parts = nn::font::DynamicCast<PartsEx>(pane))
        layout = static_cast<LayoutEx*>(parts->mPartsLayoutLink.layout);
    sub_7100BEE3C8(pane, layout);
    for (auto& child : pane->GetChildList())
        sub_7100BEE334(&child, layout);
}

// 0x7100bee3c8
void sub_7100BEE3C8(nn::ui2d::Pane* pane, LayoutEx* layout) {
    if (auto* capture = nn::font::DynamicCast<CapturePane>(pane)) {
        const char* name = layout->mScreen ? layout->mScreen->_c8.cstr() : layout->mName;
        capture->initializeCaptureTextureData_(name);
    }
    sub_7100BED748(pane, layout);
}

// NON_MATCHING: as sub_7100BEE334.
// 0x7100bee4d4
void sub_7100BEE4D4(nn::ui2d::Pane* pane, LayoutEx* layout) {
    if (auto* parts = nn::font::DynamicCast<PartsEx>(pane))
        layout = static_cast<LayoutEx*>(parts->mPartsLayoutLink.layout);
    sub_7100BEE564(pane);
    for (auto& child : pane->GetChildList())
        sub_7100BEE4D4(&child, layout);
}

// 0x7100bee564
void sub_7100BEE564(nn::ui2d::Pane* pane) {
    if (auto* capture = nn::font::DynamicCast<CapturePane>(pane))
        capture->sub_7100BF1E64();
}

}  // namespace eui
