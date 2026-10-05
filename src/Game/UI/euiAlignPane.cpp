#include "Game/UI/euiAlignPane.h"

namespace eui {

// 0x7100bf07a8
void AlignPane::Calculate(nn::ui2d::DrawInfo& draw_info,
                          nn::ui2d::Pane::CalculateContext& context, bool force) {
    if (mNeedsAlignment) {
        doAlign_();
        mNeedsAlignment = false;
    }
    nn::ui2d::Pane::Calculate(draw_info, context, force);
}

}  // namespace eui
