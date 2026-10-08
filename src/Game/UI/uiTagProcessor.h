#pragma once

#include "Game/UI/euiTagProcessor.h"

namespace uking::ui {

// Game tag processor (descriptive name), identified by ctor 0x10afb74 and vtable 0x250acb0.
class TagProcessor : public eui::TagProcessor {
public:
    TagProcessor(eui::MessageMgr* message_mgr, eui::FontMgr* font_mgr);
    ~TagProcessor() override = default;
    NN_RUNTIME_TYPEINFO(eui::TagProcessor)
    s32 m9(char16* out, u32* text_length, u32* character_count, u32 capacity, const char16* text, u32 length,
           s32 page, u32 line_count, bool trim_newlines, void* user_data) override;
    void m10(const sead::MessageSet<char16>::TagInfo* tag, char16* out, u32* text_length, u32* character_count,
             u32 capacity, const char16* text, u32 length, void* user_data) override;
    f32 m27() const override;
    f32 m28() const override;
    f32 m29() const override;
    f32 m31() const override;
    void m32(char16* glyph, u16* font_index, u8 type) override;

private:
    friend class ScreenMessageDialog;

    /* 0x50 */ void* _50 = nullptr;
    /* 0x58 */ f32 _58 = 1.4f;
    /* 0x5c */ bool _5c = false;

public:
    // Original visibility is unknown; ScreenMessageDialog::sub_71010B3294 reads it.
    /* 0x5d */ bool _5d = false;
};
KSYS_CHECK_SIZE_NX150(TagProcessor, 0x60);

}  // namespace uking::ui
