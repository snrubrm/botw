#pragma once

#include <nn/ui2d/Pane.h>

namespace eui {

// Only the three fields proved by both constructors and the alignment consumers are known.
class AlignPane : public nn::ui2d::Pane {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Pane)

    ~AlignPane() override;

    /* 0xe0 */ u8 mAlignmentMode;
    /* 0xe1 */ bool mNeedsAlignment;
    /* 0xe2 */ bool mExtendEdge;
};

}  // namespace eui
