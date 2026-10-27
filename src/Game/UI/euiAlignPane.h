#pragma once

#include <nn/ui2d/Pane.h>

namespace eui {

class LayoutEx;

// Fields proved by both constructors and the alignment consumers.
class AlignPane : public nn::ui2d::Pane {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Pane)

    AlignPane(const nn::ui2d::ResPane*, const nn::ui2d::BuildArgSet&);
    AlignPane(const AlignPane&, LayoutEx*);
    ~AlignPane() override = default;

    void Calculate(nn::ui2d::DrawInfo&, nn::ui2d::Pane::CalculateContext&, bool) override;
    void doAlign_();

    // A horizontal [min, max] extent (the alignment runs on the x axis).
    struct Bound {
        f32 min;
        f32 max;
    };
    void getAlignInfo_(nn::ui2d::Pane* pane, f32* out_width, f32* out_center, f32* out_offset);
    // static helper: it walks the pane tree from the given pane (no AlignPane receiver)
    static void calcPartsBound_(nn::ui2d::Pane* pane, Bound* bound, f32 margin);

    /* 0xdc */ f32 mDefaultMargin;
    /* 0xe0 */ u8 mAlignmentMode;
    /* 0xe1 */ bool mNeedsAlignment;
    /* 0xe2 */ bool mExtendEdge;
};

bool sub_7100BDF594(nn::ui2d::Pane* pane);
bool sub_7100BDF6A8(nn::ui2d::Pane* pane);

}  // namespace eui
