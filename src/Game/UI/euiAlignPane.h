#pragma once

#include <nn/ui2d/Pane.h>

namespace eui {

// Fields proved by both constructors and the alignment consumers.
class AlignPane : public nn::ui2d::Pane {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Pane)

    ~AlignPane() override;

    void Calculate(nn::ui2d::DrawInfo&, nn::ui2d::Pane::CalculateContext&, bool) override;
    void doAlign_();

    /* 0xdc */ f32 mDefaultMargin;
    /* 0xe0 */ u8 mAlignmentMode;
    /* 0xe1 */ bool mNeedsAlignment;
    /* 0xe2 */ bool mExtendEdge;
};

}  // namespace eui
