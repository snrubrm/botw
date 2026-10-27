#include "Game/UI/euiAlignPane.h"
#include <nn/ui2d/BuildTypes.h>
#include <nn/ui2d/ResExtUserData.h>
#include <prim/seadSafeString.h>
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/euiTextBoxEx.h"
#include <nn/ui2d/Types.h>

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


// NON_MATCHING: equivalent codegen forms only: the target tests mAlpha before IsInfluencedAlpha, keeps
// `width * -0.5f` as a multiply (ours folds it to `margin - width * 0.5f`), and selects the text alignment
// with the negated condition (ne vs eq). The body and every call are otherwise identical.
// 0x7100bf0f24
void AlignPane::calcPartsBound_(nn::ui2d::Pane* pane, Bound* bound, f32 margin) {
    if (!pane->IsVisible())
        return;
    if (pane->GetAlpha() == 0 && pane->IsInfluencedAlpha())
        return;

    if (!pane->FindExtUserDataByName("AlignIgnore")) {
        const f32 width = pane->GetSize().width;
        margin += pane->GetPosition().x;
        f32 min;
        f32 max;
        if (auto* text_box = sub_7100933580(pane)) {
            const nn::font::Rectangle rect = text_box->GetTextDrawRect();
            const f32 text_width = rect.right - rect.left;
            const f32 half_text = text_width * 0.5f;
            const f32 left = margin - width * 0.5f;
            const f32 right = margin + width * 0.5f;
            switch (text_box->GetTextPositionH()) {
            case nn::ui2d::HorizontalPosition_Left:
                min = left;
                max = left + text_width;
                break;
            case nn::ui2d::HorizontalPosition_Right:
                min = right - text_width;
                max = right;
                break;
            default:
                min = margin - half_text;
                max = margin + half_text;
                break;
            }
        } else if (sub_7100BDF594(pane) || sub_7100BDF6A8(pane)) {
            const f32 scale = pane->GetScale().x;
            const f32 extent = width * 0.5f * (scale > 0 ? scale : -scale);
            min = margin - extent;
            max = margin + extent;
        } else {
            min = 0;
            max = 0;
        }
        if (min < max) {
            switch (pane->GetBasePositionH()) {
            case nn::ui2d::HorizontalPosition_Left:
                min += width * 0.5f;
                max += width * 0.5f;
                break;
            case nn::ui2d::HorizontalPosition_Right:
                min -= width * 0.5f;
                max -= width * 0.5f;
                break;
            default:
                break;
            }
        }
        if (min < bound->min)
            bound->min = min;
        if (bound->max < max)
            bound->max = max;
    }

    for (auto& child : pane->GetChildList())
        calcPartsBound_(&child, bound, margin);
}

}  // namespace eui
