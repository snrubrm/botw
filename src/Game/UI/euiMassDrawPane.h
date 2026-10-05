#pragma once

#include "Game/UI/euiPictureEx.h"

namespace eui {

// The resource constructor delegates to PictureEx. Only the calculation
// interface is recovered here; capture fields and the full extent are unknown.
class MassDrawPane : public PictureEx {
public:
    ~MassDrawPane() override;
    void Calculate(nn::ui2d::DrawInfo&, nn::ui2d::Pane::CalculateContext&, bool) override;
};

}  // namespace eui
