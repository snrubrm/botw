#include "Game/UI/euiRootPane.h"

#include <nn/ui2d/BuildTypes.h>
#include "Game/UI/euiLayoutEx.h"

namespace eui {

// 0x7100be196c
RootPane::RootPane(const nn::ui2d::ResPane* resource, const nn::ui2d::BuildArgSet& args)
    : nn::ui2d::Pane(resource, args), mRootLayout(static_cast<LayoutEx*>(args.mRootLayout)) {}

// 0x7100be19a8
RootPane::RootPane(const RootPane& other, LayoutEx* layout)
    : nn::ui2d::Pane(other), mRootLayout(layout) {}

// 0x7100be19e0 / 0x7100be19e4
RootPane::~RootPane() = default;

}  // namespace eui
