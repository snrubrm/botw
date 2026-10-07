#include "Game/UI/euiAlignPane.h"
#include <nn/ui2d/BuildTypes.h>
#include <nn/ui2d/ResExtUserData.h>
#include <prim/seadSafeString.h>
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"

namespace eui {

AlignPane::AlignPane(const nn::ui2d::ResPane* resource, const nn::ui2d::BuildArgSet& args)
    : Pane(resource, args), mDefaultMargin(0), mAlignmentMode(0), mNeedsAlignment(true),
      mExtendEdge(false) {
    if (const auto* data = FindExtUserDataByName("AlignOn")) {
        const sead::SafeString mode(data->GetString());
        if (mode == "Center")
            mAlignmentMode = 0;
        else if (mode == "Left")
            mAlignmentMode = 1;
        else if (mode == "Right")
            mAlignmentMode = 2;
    }
    if (FindExtUserDataByName("AlignExtendEdge"))
        mExtendEdge = true;
    if (const auto* data = FindExtUserDataByName("AlignDefaultMargin"))
        mDefaultMargin = data->GetFloatArray()[0];
    auto* layout = static_cast<const LayoutEx*>(args.mParentLayout);
    if (layout->mScreen)
        layout->mScreen->_107 |= 0x20;
}

AlignPane::AlignPane(const AlignPane& other, LayoutEx* layout)
    : Pane(other), mDefaultMargin(other.mDefaultMargin), mAlignmentMode(other.mAlignmentMode),
      mNeedsAlignment(true), mExtendEdge(other.mExtendEdge) {
    if (layout->mScreen)
        layout->mScreen->_107 |= 0x20;
}


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
