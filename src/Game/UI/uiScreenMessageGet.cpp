#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiTUStatics.h"
#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiTagProcessor.h"

namespace uking::ui {

}  // namespace uking::ui

namespace uking::ui {

// 0x7100a23ed8 (CSV eui::LayoutEx::findPane<TextBoxEx>; the body is an out-of-line DynamicCast of a tag processor to
// the game's TagProcessor, placeholder name)
TagProcessor* sub_7100A23ED8(nn::font::TagProcessorBase<u16>* processor) {
    return nn::font::DynamicCast<TagProcessor>(processor);
}

// 0x7100a233ec
ScreenChild* sub_7100A233EC(const nn::ui2d::ControlSrc&, eui::LayoutEx* layout) {
    auto* layout_ex = nn::font::DynamicCast<eui::LayoutEx>(layout);
    if (!layout_ex || !layout_ex->mScreen || !layout_ex->mScreen->mInitializeHeap)
        return nullptr;
    return new (layout_ex->mScreen->mInitializeHeap, 8) Unk_710247a6d8(layout_ex);
}

}  // namespace uking::ui

namespace uking::ui {

// 0x71025ef948: the MessageGet_00 screen's icon panes, indexed by the icon id the lookup below maps.
struct MessageGetIcon {
    s32 id;
    sead::SafeString pane;
};
static MessageGetIcon sUnk_71025ef948[14] = {
    {0, "Pa_IconKagoG_00"},
    {1, "Pa_IconKagoR_00"},
    {2, "Pa_IconKagoY_00"},
    {3, "Pa_IconKagoB_00"},
    {4, "Pa_IconDungeonClear_00"},
    {5, "Pa_IconWarpDLC_00"},
    {6, "PaIconDLCAkashiG_00"},
    {7, "PaIconDLCAkashiR_00"},
    {8, "PaIconDLCAkashiY_00"},
    {9, "PaIconDLCAkashiB_00"},
    {10, "Pa_IconDLCKagoG_00"},
    {11, "Pa_IconDLCKagoR_00"},
    {12, "Pa_IconDLCKagoY_00"},
    {13, "Pa_IconDLCKagoB_00"},
};
static sead::Buffer<MessageGetIcon> sUnk_71025ef938(sUnk_71025ef948);

// 0x7100a25474 (placeholder name): the icon table index of `id`, -1 when the icon is not listed.
s32 sub_7100A25474(s32 id) {
    for (s32 i = 0; i < 14; ++i) {
        if (sUnk_71025ef938[i].id == id)
            return i;
    }
    return -1;
}

}  // namespace uking::ui
