#include "Game/UI/euiTextBoxEx.h"

// A separate translation unit: the original's out-of-line DynamicCast has the runtime type info
// of the whole chain (TextBoxEx / TextBox / Pane) initialised inline.
namespace eui {

// 0x7100933580
TextBoxEx* sub_7100933580(nn::ui2d::Pane* pane) {
    return nn::font::DynamicCast<TextBoxEx>(pane);
}

}  // namespace eui
