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

}  // namespace uking::ui
