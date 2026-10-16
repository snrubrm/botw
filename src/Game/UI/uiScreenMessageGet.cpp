#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/uiTagProcessor.h"

namespace uking::ui {

// ScreenMessageGet creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_710248f710[] = {
    {"Pa_Gear_00", sub_7100A233EC, 0},
    {"Pa_Gear_01", sub_7100A233EC, 0},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_710248f700(sUnk_710248f710);
// 0x7100a233bc
const sead::Buffer<const ChildControlCreatorEntry>* Unk_710248f740::getEntries() const {
    return &sUnk_710248f700;
}
// 0x7100a233c8
Unk_710248f740::~Unk_710248f740() = default;

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
