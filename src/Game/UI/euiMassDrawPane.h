#pragma once

#include "Game/UI/euiPictureEx.h"
#include <common/aglTextureData.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>

namespace eui {

// Native resource ctor BDF7BC and buffer setup BDFA6C establish the texture and three buffers.
class MassDrawPane : public PictureEx {
public:
    NN_RUNTIME_TYPEINFO(PictureEx)
    MassDrawPane(const nn::ui2d::ResPicture*, const nn::ui2d::ResPicture*,
                 const nn::ui2d::BuildArgSet&);
    MassDrawPane(const MassDrawPane&);
    ~MassDrawPane() override;
    void Calculate(nn::ui2d::DrawInfo&, nn::ui2d::Pane::CalculateContext&, bool) override;
    void DrawSelf(nn::ui2d::DrawInfo&, nn::gfx::CommandBuffer&) override;
    void sub_7100BDFA6C(sead::Heap* heap, s32 count);

    /* 0x108 */ agl::TextureData mTexture;
    /* 0x230 */ sead::Buffer<u8> _230;
    /* 0x240 */ sead::Buffer<u8> _240;
    /* 0x250 */ sead::Buffer<sead::Vector2f> _250;
    /* 0x260 */ bool _260 = false;
};

static_assert(sizeof(MassDrawPane) == 0x268);

}  // namespace eui
