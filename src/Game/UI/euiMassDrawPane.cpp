#include "Game/UI/euiMassDrawPane.h"

namespace eui {

MassDrawPane::MassDrawPane(const nn::ui2d::ResPicture* resource,
                           const nn::ui2d::ResPicture* replacement,
                           const nn::ui2d::BuildArgSet& args)
    : PictureEx(resource, replacement, args) {}

// NON_MATCHING: TextureData destruction remains out-of-line instead of its NVN texture member.
MassDrawPane::~MassDrawPane() = default;

void MassDrawPane::sub_7100BDFA6C(sead::Heap* heap, s32 count) {
    _230.tryAllocBuffer(count, heap);
    _230.fill(0);
    _240.tryAllocBuffer(count, heap);
    _240.fill(0);
    _250.tryAllocBuffer(count, heap);
    _250.fill(sead::Vector2f::zero);
}

// 0x7100bdfca4
void MassDrawPane::Calculate(nn::ui2d::DrawInfo& info,
                             nn::ui2d::Pane::CalculateContext& context, bool force) {
    nn::ui2d::Pane::Calculate(info, context, force);
}

}  // namespace eui
