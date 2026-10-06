#pragma once

#include <basis/seadTypes.h>
#include <nn/font/font_TagProcessorBase.h>
#include <message/seadMessageSet.h>
#include "KingSystem/Utils/Types.h"

namespace nn::font {
class Font;
}

namespace eui {

class MessageMgr;
class FontMgr;

// The tag writers below build the tags of
// sead::MessageSet<char16>::TagInfo layout in a text buffer (start marker 0xe, group, type, parameter size in
// bytes, parameters) and return the position after the tag.
class TagProcessor : public nn::font::TagProcessorBase<u16> {
public:
    TagProcessor(MessageMgr* message_mgr, FontMgr* font_mgr);
    ~TagProcessor() override = default;
    const nn::font::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override;
    Operation Process(u32 code, nn::font::PrintContext<u16>* context) override;
    Operation CalculateRect(nn::font::Rectangle* rect, nn::font::PrintContext<u16>* context,
                            u32 code) override;
    void BeginPrint(nn::font::PrintContext<u16>* context) override;
    void EndPrint(nn::font::PrintContext<u16>* context) override;
    void BeginCalculateRect(nn::font::PrintContext<u16>* context) override;
    void EndCalculateRect(nn::font::PrintContext<u16>* context) override;

    virtual s32 m9(char16* out, u32* text_length, u32* character_count, u32 capacity,
                   const char16* text, u32 length, s32 page, u32 line_count,
                   bool trim_newlines, void* user_data);
    virtual void m10(const sead::MessageSet<char16>::TagInfo* tag, char16* out, u32* text_length,
                     u32* character_count, u32 capacity, const char16* text, u32 length, void* user_data);
    virtual void preProcessEuiTag_(const sead::MessageSet<char16>::TagInfo* tag, char16* out,
                                  u32* text_length, u32* character_count, u32 capacity,
                                  const char16* text, u32 length, void* user_data);
    virtual void m12(const sead::MessageSet<char16>::TagInfo* tag, char16* out, u32* text_length,
                     u32* character_count, u32 capacity, const char16* text, u32 length, void* user_data);
    virtual void m13(const sead::MessageSet<char16>::TagInfo* tag, char16* out, u32* text_length,
                     u32* character_count, u32 capacity, const char16* text, u32 length, void* user_data);
    virtual void preProcessAppTag_(const sead::MessageSet<char16>::TagInfo* tag, char16* out,
                                  u32* text_length, u32* character_count, u32 capacity,
                                  const char16* text, u32 length, void* user_data);
    virtual Operation m15(u32 code, nn::font::PrintContext<u16>* context, nn::font::Rectangle* rect);
    virtual Operation m16(const sead::MessageSet<char16>::TagInfo* tag,
                          nn::font::PrintContext<u16>* context, nn::font::Rectangle* rect,
                          const char16* next);
    virtual Operation m17(const sead::MessageSet<char16>::TagInfo* tag,
                          nn::font::PrintContext<u16>* context, nn::font::Rectangle* rect,
                          const char16* next);
    virtual Operation m18(const sead::MessageSet<char16>::TagInfo* tag,
                          nn::font::PrintContext<u16>* context, nn::font::Rectangle* rect,
                          const char16* next);
    virtual Operation m19(const sead::MessageSet<char16>::TagInfo* tag,
                          nn::font::PrintContext<u16>* context, nn::font::Rectangle* rect,
                          const char16* next);
    virtual Operation m20(const sead::MessageSet<char16>::TagInfo* tag,
                          nn::font::PrintContext<u16>* context, nn::font::Rectangle* rect,
                          const char16* next);
    virtual Operation m21(const sead::MessageSet<char16>::TagInfo* tag,
                          nn::font::PrintContext<u16>* context, nn::font::Rectangle* rect,
                          const char16* next);
    virtual Operation m22(const sead::MessageSet<char16>::TagInfo* tag,
                          nn::font::PrintContext<u16>* context, nn::font::Rectangle* rect,
                          const char16* next);
    virtual Operation m23(const sead::MessageSet<char16>::TagInfo* tag,
                          nn::font::PrintContext<u16>* context, nn::font::Rectangle* rect,
                          const char16* next);
    virtual Operation processPictFontProcessTag_(const sead::MessageSet<char16>::TagInfo* tag,
                                               nn::font::PrintContext<u16>* context,
                                               nn::font::Rectangle* rect, const char16* next);
    virtual Operation m25(const sead::MessageSet<char16>::TagInfo* tag,
                          nn::font::PrintContext<u16>* context, nn::font::Rectangle* rect,
                          const char16* next);
    virtual Operation m26(const sead::MessageSet<char16>::TagInfo* tag,
                          nn::font::PrintContext<u16>* context, nn::font::Rectangle* rect,
                          const char16* next);
    virtual f32 m27() const;
    virtual f32 m28() const;
    virtual f32 m29() const;
    virtual f32 m30() const;
    virtual f32 m31() const;
    virtual void m32(char16* glyph, u16* font_index, u8 type);

    // inline-only in the original; name is a guess (uking::ui::Fade::doCreateTagProcessor_ stores 1 at 0x48 and the
    // constructor of uking::ui::TagProcessor stores 0 there)
    void setRubyEnabled(bool enabled) { mRubyEnabled = enabled; }

    // 0x7100be6254: type 0x80, two parameter bytes (the first is the negated flag)
    static char16* setAlphaTag(char16* out, bool flag, u8 alpha);
    // 0x7100be628c: type 0x82, one u16 parameter
    static char16* setSkipTag(char16* out, u16 count);
    // 0x7100be6308: type 2, one u16 parameter
    static char16* setSizeTag(char16* out, u16 size);

protected:
    /* 0x8 */ u32 _8 = 0xff;
    /* 0xc */ u32 _c = 0xff;
    /* 0x10 */ const nn::font::Font* _10 = nullptr;
    /* 0x18 */ const nn::font::Font* _18 = nullptr;
    /* 0x20 */ f32 mSavedItalicRatio = 0.0f;
    /* 0x24 */ f32 mSavedScaleX = 0.0f;
    /* 0x28 */ f32 mSavedScaleY = 0.0f;
    /* 0x2c */ f32 mScaleX = 1.0f;
    /* 0x30 */ f32 mScaleY = 1.0f;
    /* 0x34 */ u32 mNestingDepth = 0;
    /* 0x38 */ MessageMgr* mMessageMgr;
public:
    // Original visibility is unknown; LayoutEx::isScalableFontTextBox_ reads this proved pointer.
    /* 0x40 */ FontMgr* mFontMgr;

protected:
    /* 0x48 */ bool mRubyEnabled = true;
    /* 0x49 */ u8 mAlpha = 0xff;
    /* 0x4a */ u8 mTopAlpha = 0xff;
    /* 0x4b */ u8 mBottomAlpha = 0xff;
};
KSYS_CHECK_SIZE_NX150(TagProcessor, 0x50);

}  // namespace eui
