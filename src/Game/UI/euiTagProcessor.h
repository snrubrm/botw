#pragma once

#include <basis/seadTypes.h>
#include <nn/font/font_TagProcessorBase.h>
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
    void EndPrint(nn::font::PrintContext<u16>* context) override;
    void EndCalculateRect(nn::font::PrintContext<u16>* context) override;

    // 0x7100be6254: type 0x80, two parameter bytes (the first is the negated flag)
    static char16* setAlphaTag(char16* out, bool flag, u8 alpha);
    // 0x7100be628c: type 0x82, one u16 parameter
    static char16* setSkipTag(char16* out, u16 count);
    // 0x7100be6308: type 2, one u16 parameter
    static char16* setSizeTag(char16* out, u16 size);

private:
    /* 0x8 */ u32 _8 = 0xff;
    /* 0xc */ u32 _c = 0xff;
    /* 0x10 */ const nn::font::Font* _10 = nullptr;
    /* 0x18 */ const nn::font::Font* _18 = nullptr;
    /* 0x20 */ void* _20 = nullptr;
    /* 0x28 */ u32 _28 = 0;
    /* 0x2c */ f32 _2c = 1.0f;
    /* 0x30 */ f32 _30 = 1.0f;
    /* 0x34 */ u32 mNestingDepth = 0;
    /* 0x38 */ MessageMgr* mMessageMgr;
    /* 0x40 */ FontMgr* mFontMgr;
    /* 0x48 */ u32 _48 = 0xffffff01;
};
KSYS_CHECK_SIZE_NX150(TagProcessor, 0x50);

}  // namespace eui
