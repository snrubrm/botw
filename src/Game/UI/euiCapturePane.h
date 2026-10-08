#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include <gfx/seadColor.h>
#include <common/aglRenderBuffer.h>
#include <common/aglRenderTarget.h>
#include <nn/ui2d/Pane.h>
#include <nn/ui2d/TextureInfo.h>


namespace agl {
class TextureData;
}

namespace sead {
class Heap;
}

namespace eui {

class LayoutEx;

// The layout and virtual overrides mirror DynamicCapturePane (vtable 0x71024c9758: dtor, GetRuntimeTypeInfo,
// Calculate, Draw). The RTTI static is at 0x71025d6530 (guard 0x71025d6538): a Pane subclass, DynamicCast'ed by the pane walks
// sub_7100BEE240 / sub_7100BEE3C8 / sub_7100BEE564.
class CapturePane : public nn::ui2d::Pane {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Pane)
    // 0x7100bf12d4
    CapturePane(const nn::ui2d::ResPane* resource, const nn::ui2d::BuildArgSet& args);
    // 0x7100bf1e9c
    ~CapturePane() override;
    // 0x7100bf1f7c (not decompiled)
    void Calculate(nn::ui2d::DrawInfo&, nn::ui2d::Pane::CalculateContext&, bool) override;
    // 0x7100bf20a0 (not decompiled)
    void Draw(nn::ui2d::DrawInfo&, nn::gfx::CommandBuffer&) override;
    // 0x7100bf1348 (not decompiled): reads the pane's user data (clear colour, flags)
    void initialize_(LayoutEx* layout);

    // 0x7100bf166c (2040 bytes, not decompiled; the CSV name listed (Heap*, const char*) but the pane is `this`):
    // `layout_name` is the layout's name (or its screen's name)
    void initializeCaptureTextureData_(const char* layout_name);
    // 0x7100bf1e64 (56 bytes, not decompiled; placeholder name)
    void sub_7100BF1E64();

    // The members start in the tail padding of nn::ui2d::Pane (at 0xda).
    /* 0xda */ sead::BitFlag<u8> mCaptureFlags;  // passed to the setup*_ helpers by initialize_
    /* 0xdb */ bool _db = true;
    /* 0xdc */ bool _dc = false;
    /* 0xdd */ bool _dd = false;  // set by Calculate
    /* 0xe0 */ sead::Color4f* mClearColor = nullptr;
    /* 0xe8 */ void* _e8 = nullptr;
    /* 0xf0 */ nn::ui2d::ExternalTextureInfo mTextureInfo;
    /* 0x108 */ const agl::TextureData* mTexture = nullptr;  // freed by sub_7100BF1E64
    /* 0x110 */ agl::RenderBuffer mRenderBuffer;
    /* 0x178 */ agl::RenderTargetColor mRenderTarget;

    static sead::Color4f* setupClearColor_(sead::Heap*, nn::ui2d::Pane*, LayoutEx*,
                                          sead::BitFlag<u8>* flags);
    static void setupCaptureOutputAlpha255_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags);
    static void setupCaptureOriginalSize_(nn::ui2d::Pane* pane, sead::BitFlag<u8>* flags);
};
static_assert(offsetof(CapturePane, _db) == 0xdb);
static_assert(offsetof(CapturePane, mRenderTarget) == 0x178);

}  // namespace eui
