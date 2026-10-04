#include "Game/UI/euiTagProcessor.h"
#include <cstring>
#include <nn/font/font_PrintContext.h>
#include <nn/font/font_TextWriterBase.h>
#include "Game/UI/euiMessageMgr.h"

namespace eui {

// 0x7100be5be4
TagProcessor::TagProcessor(MessageMgr* message_mgr, FontMgr* font_mgr)
    : mMessageMgr(message_mgr), mFontMgr(font_mgr) {}

// 0x7100be5c48
TagProcessor::Operation TagProcessor::Process(u32 code, nn::font::PrintContext<u16>* context) {
    return m15(code, context, nullptr);
}

// 0x7100be5c58
TagProcessor::Operation TagProcessor::CalculateRect(nn::font::Rectangle* rect,
                                                  nn::font::PrintContext<u16>* context, u32 code) {
    return m15(code, context, rect);
}

// 0x7100be5d00
void TagProcessor::BeginCalculateRect(nn::font::PrintContext<u16>* context) {
    _10 = _18 = context->writer->GetFont();
    if (mNestingDepth == 0) {
        mScaleX = context->scaleX;
        mScaleY = context->scaleY;
    }
    ++mNestingDepth;
}

// 0x7100be5cf0
void TagProcessor::EndPrint(nn::font::PrintContext<u16>*) {
    --mNestingDepth;
}

// 0x7100be5d30
void TagProcessor::EndCalculateRect(nn::font::PrintContext<u16>*) {
    --mNestingDepth;
}

// 0x7100be6330
void TagProcessor::m10(const sead::MessageSet<char16>::TagInfo* tag, char16* out,
                       u32* text_length, u32* character_count, u32 capacity,
                       const char16* text, u32 length, void*) {
    if (tag->type != 0 || (mMessageMgr->isRubyEnabled() && mRubyEnabled)) {
        if (*text_length + length < capacity) {
            std::memcpy(out + *text_length, text, length * 2);
            *text_length += length;
            if (tag->type == 0) {
                u16 character_bytes;
                std::memcpy(&character_bytes, tag->getParam() + 2, sizeof(character_bytes));
                *character_count += character_bytes / 2;
            }
        }
    }
}

// 0x7100be6440
void TagProcessor::m13(const sead::MessageSet<char16>::TagInfo*, char16*, u32*, u32*, u32,
                       const char16*, u32, void*) {}

// 0x7100be6444
// NON_MATCHING: tag output store scheduling and constant-store merging differ.
void TagProcessor::m12(const sead::MessageSet<char16>::TagInfo* tag, char16* out,
                       u32* text_length, u32* character_count, u32 capacity,
                       const char16*, u32, void*) {
    if (*text_length + 11 < capacity) {
        char16 glyph = 0;
        u16 font_index = 0;
        m32(&glyph, &font_index, tag->getParam()[0]);
        if (glyph != 0) {
            char16* position = out + *text_length;
            position[0] = 0xe;
            position[1] = 0;
            position[2] = 0x81;
            position[3] = 2;
            position[4] = font_index;
            position[5] = glyph;
            position[6] = 0xe;
            position[7] = 0;
            position[8] = 0x81;
            position[9] = 2;
            position[10] = 0xffff;
            *text_length += 11;
            ++*character_count;
        }
    }
}

// 0x7100be66e8
TagProcessor::Operation TagProcessor::m16(const sead::MessageSet<char16>::TagInfo*,
                                         nn::font::PrintContext<u16>* context,
                                         nn::font::Rectangle*, const char16* next) {
    context->str = reinterpret_cast<const u16*>(next);
    return Operation_Default;
}

// 0x7100be66f4
TagProcessor::Operation TagProcessor::m17(const sead::MessageSet<char16>::TagInfo*,
                                         nn::font::PrintContext<u16>* context,
                                         nn::font::Rectangle*, const char16* next) {
    context->str = reinterpret_cast<const u16*>(next);
    return Operation_Default;
}

// 0x7100be6d4c
TagProcessor::Operation TagProcessor::m22(const sead::MessageSet<char16>::TagInfo*,
                                         nn::font::PrintContext<u16>* context,
                                         nn::font::Rectangle*, const char16* next) {
    context->str = reinterpret_cast<const u16*>(next);
    return Operation_NoCharSpace;
}

// 0x7100be6c50
TagProcessor::Operation TagProcessor::m20(const sead::MessageSet<char16>::TagInfo* tag,
                                         nn::font::PrintContext<u16>* context,
                                         nn::font::Rectangle*, const char16* next) {
    context->str = reinterpret_cast<const u16*>(next);
    u16 size;
    std::memcpy(&size, tag->getParam(), sizeof(size));
    const f32 scale = f32(size) / 100.0f;
    context->writer->SetScale(mScaleX * scale, mScaleY * scale);
    return Operation_Default;
}

// 0x7100be6f14
// NON_MATCHING: the original repeats tag classification tests in the traversal loop.
TagProcessor::Operation TagProcessor::m25(const sead::MessageSet<char16>::TagInfo* tag,
                                         nn::font::PrintContext<u16>* context,
                                         nn::font::Rectangle*, const char16* next) {
    u16 count;
    std::memcpy(&count, tag->getParam(), sizeof(count));
    s32 skipped = 0;
    while (skipped < count && reinterpret_cast<const u16*>(next) < context->strEnd) {
        if (*next == 0xe) {
            next = reinterpret_cast<const char16*>(reinterpret_cast<const u8*>(next) + 8 + next[3]);
        } else if (*next == 0xf) {
            next += 3;
        } else {
            ++skipped;
            ++next;
        }
    }
    context->str = reinterpret_cast<const u16*>(next);
    return Operation_Default;
}

// 0x7100be6554
// NON_MATCHING: character narrowing and tag marker branch scheduling differ.
TagProcessor::Operation TagProcessor::m15(u32 code, nn::font::PrintContext<u16>* context,
                                         nn::font::Rectangle* rect) {
    const u16 character = code;
    if ((character | 1) != 0xf) {
        if (rect)
            return nn::font::TagProcessorBase<u16>::CalculateRect(rect, context, character);
        return nn::font::TagProcessorBase<u16>::Process(character, context);
    }

    const auto* tag = reinterpret_cast<const sead::MessageSet<char16>::TagInfo*>(context->str - 1);
    const char16* next;
    if (tag->marker == 0xf) {
        next = reinterpret_cast<const char16*>(tag) + 3;
    } else if (tag->marker == 0xe) {
        next = reinterpret_cast<const char16*>(tag->getParam() + tag->paramSize);
    } else {
        mMessageMgr->m0();
        return Operation_EndDraw;
    }
    if (reinterpret_cast<const u16*>(next) > context->strEnd) {
        mMessageMgr->m0();
        return Operation_EndDraw;
    }

    if (tag->group == 1)
        return m16(tag, context, rect, next);
    if (tag->group != 0)
        return m17(tag, context, rect, next);
    switch (tag->type) {
    case 0:
        return m18(tag, context, rect, next);
    case 1:
        return m19(tag, context, rect, next);
    case 2:
        return m20(tag, context, rect, next);
    case 3:
        return m21(tag, context, rect, next);
    case 4:
        return m22(tag, context, rect, next);
    case 0x80:
        return m23(tag, context, rect, next);
    case 0x81:
        return processPictFontProcessTag_(tag, context, rect, next);
    case 0x82:
        return m25(tag, context, rect, next);
    case 0x83:
        return m26(tag, context, rect, next);
    default:
        return Operation_Default;
    }
}

// 0x7100be70b8
f32 TagProcessor::m27() const {
    return 0.4f;
}

// 0x7100be70c4
f32 TagProcessor::m28() const {
    return 1.0f;
}

// 0x7100be70cc
f32 TagProcessor::m29() const {
    return 0.0f;
}

// 0x7100be70d4
f32 TagProcessor::m30() const {
    return 0.0f;
}

// 0x7100be70dc
f32 TagProcessor::m31() const {
    return 1.0f;
}

// 0x7100be70e4
void TagProcessor::m32(char16* glyph, u16* font_index, u8) {
    *glyph = 0;
    *font_index = 0;
}

// 0x7100be63c4
void TagProcessor::preProcessEuiTag_(const sead::MessageSet<char16>::TagInfo* tag, char16* out,
                                    u32* text_length, u32* character_count, u32 capacity,
                                    const char16* text, u32 length, void* user_data) {
    if (tag->type == 7) {
        m12(tag, out, text_length, character_count, capacity, text, length, user_data);
        return;
    }
    if (*text_length + length < capacity) {
        std::memcpy(out + *text_length, text, length * 2);
        *text_length += length;
    }
}

// 0x7100be6508
void TagProcessor::preProcessAppTag_(const sead::MessageSet<char16>::TagInfo*, char16* out,
                                    u32* text_length, u32*, u32 capacity,
                                    const char16* text, u32 length, void*) {
    if (*text_length + length < capacity) {
        std::memcpy(out + *text_length, text, length * 2);
        *text_length += length;
    }
}

// 0x7100be6254
char16* TagProcessor::setAlphaTag(char16* out, bool flag, u8 alpha) {
    out[0] = 0xe;
    out[1] = 0;
    out[2] = 0x80;
    out[3] = 2;
    u8* params = reinterpret_cast<u8*>(out + 4);
    params[0] = !flag;
    params[1] = alpha;
    return out + 5;
}

// 0x7100be628c
char16* TagProcessor::setSkipTag(char16* out, u16 count) {
    out[0] = 0xe;
    out[1] = 0;
    out[2] = 0x82;
    out[3] = 2;
    out[4] = count;
    return out + 5;
}

// 0x7100be6308
char16* TagProcessor::setSizeTag(char16* out, u16 size) {
    out[0] = 0xe;
    out[1] = 0;
    out[2] = 2;
    out[3] = 2;
    out[4] = size;
    return out + 5;
}

}  // namespace eui
