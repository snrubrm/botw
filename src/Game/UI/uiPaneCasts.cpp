#include "Game/UI/euiButton.h"
#include "Game/UI/euiPartsEx.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/uiScreens.h"

// A separate translation unit: the original's out-of-line DynamicCast has the runtime type info
// of the whole chain (TextBoxEx / TextBox / Pane) initialised inline.
namespace eui {

// 0x7100933580
TextBoxEx* sub_7100933580(nn::ui2d::Pane* pane) {
    return nn::font::DynamicCast<TextBoxEx>(pane);
}

// 0x7100945088
PartsEx* sub_7100945088(nn::ui2d::Pane* pane) {
    return nn::font::DynamicCast<PartsEx>(pane);
}

// 0x7100a013e4
AnimButton* sub_7100A013E4(ControlBase* control) {
    return nn::font::DynamicCast<AnimButton>(control);
}

}  // namespace eui

namespace uking::ui {

// 0x71009de2b8
ScreenChildEx* sub_71009DE2B8(eui::ControlBase* control) {
    return nn::font::DynamicCast<ScreenChildEx>(control);
}

}  // namespace uking::ui
