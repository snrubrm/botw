#pragma once

#include <nn/ui2d/Pane.h>

namespace eui {
class LayoutEx;

// The constructors prove the root layout pointer after Pane. The original
// factory allocates 0xf0 bytes; its alignment/tail extent is not established.
class RootPane : public nn::ui2d::Pane {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Pane)

    RootPane(const nn::ui2d::ResPane*, const nn::ui2d::BuildArgSet&);
    RootPane(const RootPane&, LayoutEx*);
    ~RootPane() override;

    /* 0xe0 */ LayoutEx* mRootLayout;
};

}  // namespace eui
