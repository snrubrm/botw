#include "Game/UI/euiMassDrawPane.h"

namespace eui {

// 0x7100bdfca4
void MassDrawPane::Calculate(nn::ui2d::DrawInfo& info,
                             nn::ui2d::Pane::CalculateContext& context, bool force) {
    nn::ui2d::Pane::Calculate(info, context, force);
}

}  // namespace eui
