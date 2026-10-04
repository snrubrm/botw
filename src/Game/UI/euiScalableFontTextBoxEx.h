#pragma once

#include "Game/UI/euiTextBoxEx.h"

namespace eui {
class FontMgr;
class ScalableFontMgr;

// The constructors and the 0x170-byte native factory allocation prove this
// TextBoxEx subclass and its font-manager/cache state prefix.
class ScalableFontTextBoxEx : public TextBoxEx {
public:
    NN_RUNTIME_TYPEINFO(TextBoxEx)

    ScalableFontTextBoxEx(const nn::ui2d::ResTextBox*, const nn::ui2d::ResTextBox*,
                          const nn::ui2d::BuildArgSet&, nn::ui2d::TextBox::InitializeStringParam*);
    ScalableFontTextBoxEx(const ScalableFontTextBoxEx&, LayoutEx*);
    ~ScalableFontTextBoxEx() override = default;

    void Calculate(nn::ui2d::DrawInfo&, nn::ui2d::Pane::CalculateContext&, bool) override;
    void DrawSelf(nn::ui2d::DrawInfo&, nn::gfx::CommandBuffer&) override;
    u16 setStringNoPreproces(const char16* string, u16 length) override;
    s32 m42(sead::WBufferedSafeString*, u32*, u32*, const char16*, u32, u32, bool, void*) override;

    void sub_7100BE1BDC(ScalableFontMgr*);

    /* 0x160 */ FontMgr* mFontMgr;
    /* 0x168 */ u32 _168;
    /* 0x16c */ u32 _16c;
};

}  // namespace eui
