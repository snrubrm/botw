#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiPartsEx.h"
#include "Game/UI/euiScreen.h"

// NON_MATCHING: the original calls PartsEx::GetRuntimeTypeInfoStatic out of line (0x7100a4a4f8, shared with other
// callers); here the compiler inlines it. The other pane walk and the PartsEx constructors must stay out of this TU:
// the compiler then outlines DynamicCast<PartsEx> or turns PartsEx::GetRuntimeTypeInfo into a tail call.
namespace eui {

// 0x7100bee334
void sub_7100BEE334(nn::ui2d::Pane* pane, LayoutEx* layout) {
    if (auto* parts = nn::font::DynamicCast<PartsEx>(pane))
        layout = static_cast<LayoutEx*>(parts->mPartsLayoutLink.layout);
    sub_7100BEE3C8(pane, layout);
    for (auto& child : pane->GetChildList())
        sub_7100BEE334(&child, layout);
}

}  // namespace eui
