#include <math/seadMathCalcCommon.h>
#include "Game/UI/euiTagProcessor.h"
#include <cstring>
#include <nn/font/font_PrintContext.h>
#include <nn/font/font_TextWriterBase.h>
#include "Game/UI/euiMessageMgr.h"
#include "Game/UI/euiFontMgr.h"

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

// NON_MATCHING: page-mode loop unswitching, tag dispatch and saved-span arithmetic differ.
s32 TagProcessor::m9(char16* out, u32* text_length, u32* character_count, u32 capacity,
                     const char16* text, u32 length, s32 page, u32 line_count,
                     bool trim_newlines, void* user_data) {
    const char16* end = text + length;
    u32 written = 0;
    u32 characters = 0;
    *text_length = 0;
    *character_count = 0;
    *out = 0;

    if (page > 0) {
        s32 skipped_pages = 0;
        u32 skipped_lines = 0;
        const char16* font_tag = nullptr;
        const char16* size_tag = nullptr;
        const char16* color_tag = nullptr;
        u32 font_tag_length = 0;
        u32 size_tag_length = 0;
        u32 color_tag_length = 0;
        while (skipped_pages < page) {
            if (text >= end)
                return 2;
            const char16* current = text;
            if (*current == 0xe || *current == 0xf) {
                if (*current == 0xe)
                    text = reinterpret_cast<const char16*>(
                        reinterpret_cast<const u8*>(current) + 8 + current[3]);
                else
                    text = current + 3;
                if (text > end) {
                    mMessageMgr->m0();
                    return 3;
                }
                if (current[1] == 0) {
                    switch (current[2]) {
                    case 1:
                        font_tag = current;
                        font_tag_length = u32(text - current);
                        break;
                    case 2:
                        size_tag = current;
                        size_tag_length = u32(text - current);
                        break;
                    case 3:
                        color_tag = current;
                        color_tag_length = u32(text - current);
                        break;
                    case 4:
                        skipped_lines = 0;
                        ++skipped_pages;
                        break;
                    }
                }
            } else {
                if (*current == u'\n') {
                    if (++skipped_lines >= line_count) {
                        skipped_lines = 0;
                        ++skipped_pages;
                    }
                }
                text = current + 1;
            }
        }
        if (font_tag)
            m10(reinterpret_cast<const sead::MessageSet<char16>::TagInfo*>(font_tag), out,
                &written, &characters, capacity, font_tag, font_tag_length, user_data);
        if (size_tag)
            m10(reinterpret_cast<const sead::MessageSet<char16>::TagInfo*>(size_tag), out,
                &written, &characters, capacity, size_tag, size_tag_length, user_data);
        if (color_tag)
            m10(reinterpret_cast<const sead::MessageSet<char16>::TagInfo*>(color_tag), out,
                &written, &characters, capacity, color_tag, color_tag_length, user_data);
    }

    s32 result = 0;
    u32 lines = 0;
    u32 trailing_newlines = 0;
    while (text < end) {
        if (written + 1 >= capacity) {
            mMessageMgr->m0();
            result = 5;
            break;
        }
        if (*text == 0xe || *text == 0xf) {
            const char16* next;
            if (*text == 0xe)
                next = reinterpret_cast<const char16*>(
                    reinterpret_cast<const u8*>(text) + 8 + text[3]);
            else
                next = text + 3;
            if (next > end) {
                mMessageMgr->m0();
                result = 3;
                break;
            }
            const auto* tag = reinterpret_cast<const sead::MessageSet<char16>::TagInfo*>(text);
            const u32 tag_length = u32(next - text);
            if (tag->group == 0) {
                if (tag->type == 4) {
                    result = page == -1 ? 4 : 1;
                    break;
                }
                m10(tag, out, &written, &characters, capacity, text, tag_length, user_data);
            } else if (tag->group == 1) {
                preProcessEuiTag_(tag, out, &written, &characters, capacity, text, tag_length,
                                  user_data);
            } else if (tag->group == 201) {
                m13(tag, out, &written, &characters, capacity, text, tag_length, user_data);
            } else {
                preProcessAppTag_(tag, out, &written, &characters, capacity, text, tag_length,
                                  user_data);
            }
            trailing_newlines = 0;
            text = next;
        } else {
            if (*text >= 0x20) {
                ++characters;
                trailing_newlines = 0;
            } else if (*text == u'\n') {
                ++lines;
                if (page != -1 && lines >= line_count) {
                    result = text + 1 < end;
                    break;
                }
                ++trailing_newlines;
            }
            out[written++] = *text++;
        }
    }
    if (page == -1 && lines >= line_count && result == 0)
        result = 4;
    if (trailing_newlines != 0 && trim_newlines)
        written = written >= trailing_newlines ? written - trailing_newlines : 0;
    *text_length = written;
    *character_count = characters;
    out[written] = 0;
    return result;
}

// NON_MATCHING: saved color byte stores combine into packed word stores.
void TagProcessor::BeginPrint(nn::font::PrintContext<u16>* context) {
    const auto top = context->writer->GetTextColor(0);
    const sead::Color4u8 top_color{top.v[0], top.v[1], top.v[2], top.v[2]};
    std::memcpy(&_8, &top_color, sizeof(top_color));
    const auto bottom = context->writer->GetTextColor(1);
    const sead::Color4u8 bottom_color{bottom.v[0], bottom.v[1], bottom.v[2], bottom.v[2]};
    std::memcpy(&_c, &bottom_color, sizeof(bottom_color));
    _10 = _18 = context->writer->GetFont();
    mTopAlpha = top.v[2];
    mBottomAlpha = bottom.v[2];
    mAlpha = 255;
    if (mNestingDepth == 0) {
        mScaleX = context->scaleX;
        mScaleY = context->scaleY;
    }
    ++mNestingDepth;
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

// 0x7100be6700
// NON_MATCHING: tag-span simplification and receiver/cursor load scheduling differ.
TagProcessor::Operation TagProcessor::m18(const sead::MessageSet<char16>::TagInfo* tag,
                                         nn::font::PrintContext<u16>* context,
                                         nn::font::Rectangle* rect, const char16* next) {
    context->str = reinterpret_cast<const u16*>(next);
    if (!mMessageMgr->isRubyEnabled() || rect || !mRubyEnabled)
        return Operation_Default;

    u16 base_bytes;
    u16 ruby_bytes;
    std::memcpy(&base_bytes, tag->getParam(), sizeof(base_bytes));
    const u32 base_count = base_bytes / 2;
    if (base_count == 0) {
        mMessageMgr->m0();
        return Operation_Default;
    }
    std::memcpy(&ruby_bytes, tag->getParam() + 2, sizeof(ruby_bytes));
    const u32 ruby_count = ruby_bytes / 2;
    s32 span = 0;
    s32 counted = 0;
    do {
        const char16* current = next + span;
        s32 length = 1;
        if (*current == 0xe || *current == 0xf) {
            const char16* end;
            if (*current == 0xe)
                end = reinterpret_cast<const char16*>(
                    reinterpret_cast<const u8*>(current) + 8 + current[3]);
            else
                end = current + 3;
            length = s32(end - current);
            if (current[1] != 0 || current[2] < 0x80)
                counted += length;
        } else {
            ++counted;
        }
        span += length;
    } while (counted < s32(base_count));
    if (u32(span - 1) >= 31 || ruby_bytes >= 64 || ruby_count == 0) {
        mMessageMgr->m0();
        return Operation_Default;
    }

    sead::WFixedSafeString<32> ruby;
    ruby.copy(reinterpret_cast<const char16*>(tag->getParam() + 4), ruby_count);
    sead::WFixedSafeString<32> base;
    base.copy(next, span);
    nn::font::TextWriterBase<u16> writer = *context->writer;
    if (mFontMgr->mRubyFont)
        writer.SetFont(mFontMgr->mRubyFont);
    const f32 size_ratio = m27();
    const f32 max_scale = m28();
    const f32 vertical_offset = m29();
    const f32 char_space = m30();
    writer.SetDrawFlag(0x300);
    writer.SetLineSpace(0.0f);
    writer.SetCharSpace(char_space);
    const f32 scale = size_ratio * context->writer->GetFontWidth() /
                      static_cast<f32>(writer.GetFont()->GetWidth());
    writer.SetItalicRatio(0.0f);
    writer.SetTagProcessor(&nn::font::TextWriterBase<u16>::sDefaultTagProcessor);
    writer.SetScale(scale < max_scale ? scale : max_scale, scale < max_scale ? scale : max_scale);

    auto* saved_processor = context->writer->mTagProcessor;
    TagProcessor processor(mMessageMgr, mFontMgr);
    context->writer->SetTagProcessor(&processor);
    const f32 base_width = context->writer->CalculateStringWidth(
        reinterpret_cast<const u16*>(base.cstr()), span);
    context->writer->SetTagProcessor(saved_processor);
    const f32 ruby_width = writer.CalculateStringWidth(
        reinterpret_cast<const u16*>(ruby.cstr()), ruby_count);
    const f32 remaining = static_cast<f32>(span) - ruby_width;
    if (remaining > 0.0f) {
        const f32 space = remaining / static_cast<f32>(ruby_count + 1);
        writer.SetCursorX(writer.GetCursorX() + space);
        writer.SetCharSpace(char_space + space);
    } else {
        writer.SetCursorX(writer.GetCursorX() + (base_width - ruby_width) * 0.5f);
    }
    if (context->writer->GetItalicRatio() != 0.0f) {
        writer.SetCursorX(writer.GetCursorX() + context->writer->GetItalicRatio() *
                         context->writer->GetScaleX() *
                         static_cast<f32>(context->writer->GetFont()->GetWidth()) * 0.5f);
    }
    writer.SetCursorY(writer.GetCursorY() + (-context->writer->GetScaleY() *
                     static_cast<f32>(context->writer->GetFont()->GetBaselinePos()) - vertical_offset));
    writer.Print(reinterpret_cast<const u16*>(ruby.cstr()), ruby_count);
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

// 0x7100be6bec
TagProcessor::Operation TagProcessor::m19(const sead::MessageSet<char16>::TagInfo* tag,
                                         nn::font::PrintContext<u16>* context,
                                         nn::font::Rectangle*, const char16* next) {
    context->str = reinterpret_cast<const u16*>(next);
    u16 font_index;
    std::memcpy(&font_index, tag->getParam(), sizeof(font_index));
    context->writer->SetFont(font_index == 0xffff ? _10 : mFontMgr->getFontByMessageIndex(font_index));
    _18 = context->writer->GetFont();
    return Operation_Default;
}

// NON_MATCHING: typed color copies split component addresses and reorder packing and alpha stores.
TagProcessor::Operation TagProcessor::m21(const sead::MessageSet<char16>::TagInfo* tag,
                                         nn::font::PrintContext<u16>* context,
                                         nn::font::Rectangle* rect, const char16* next) {
    context->str = reinterpret_cast<const u16*>(next);
    if (!rect) {
        u16 index;
        std::memcpy(&index, tag->getParam(), sizeof(index));
        sead::Color4u8 top;
        sead::Color4u8 bottom;
        if (index == 0xffff) {
            std::memcpy(&top, &_8, sizeof(top));
            std::memcpy(&bottom, &_c, sizeof(bottom));
            mTopAlpha = top.a;
            mBottomAlpha = bottom.a;
        } else {
            const auto& color = mMessageMgr->mGradationColors[index];
            top = color.top;
            bottom = color.bottom;
            mTopAlpha = top.a;
            mBottomAlpha = top.a;
        }
        nn::util::Unorm8x4 top_color{{top.r, top.g, top.b, u8(mAlpha * mTopAlpha / 255)}};
        nn::util::Unorm8x4 bottom_color{{bottom.r, bottom.g, bottom.b,
                                       u8(mAlpha * mBottomAlpha / 255)}};
        context->writer->SetTextColor(top_color, bottom_color);
    }
    return Operation_Default;
}

// 0x7100be6d58
TagProcessor::Operation TagProcessor::m23(const sead::MessageSet<char16>::TagInfo* tag,
                                         nn::font::PrintContext<u16>* context,
                                         nn::font::Rectangle* rect, const char16* next) {
    context->str = reinterpret_cast<const u16*>(next);
    if (rect == nullptr) {
        mAlpha = tag->getParam()[0] ? tag->getParam()[1] : 255;
        auto top = context->writer->GetTextColor(0);
        auto bottom = context->writer->GetTextColor(1);
        top.v[3] = mTopAlpha * mAlpha / 255;
        bottom.v[3] = mBottomAlpha * mAlpha / 255;
        context->writer->SetTextColor(top, bottom);
        context->writer->SetAlpha(mAlpha);
    }
    return Operation_Default;
}

// NON_MATCHING: tag-index caching and floating-point call/load scheduling differ.
// 0x7100be6dcc
TagProcessor::Operation TagProcessor::processPictFontProcessTag_(
    const sead::MessageSet<char16>::TagInfo* tag, nn::font::PrintContext<u16>* context,
    nn::font::Rectangle*, const char16* next) {
    context->str = reinterpret_cast<const u16*>(next);
    u16 font_index;
    std::memcpy(&font_index, tag->getParam(), sizeof(font_index));
    if (font_index != 0xffff) {
        mSavedScaleX = context->writer->GetScaleX();
        mSavedScaleY = context->writer->GetScaleY();
        const f32 italic_ratio = context->writer->GetItalicRatio();
        mSavedItalicRatio = italic_ratio;
        if (italic_ratio > 0) {
            const f32 font_width = context->writer->GetFontWidth();
            context->writer->SetCursorX(context->writer->GetCursorX() +
                                         italic_ratio * font_width * 0.5f);
        }
        const f32 font_height = context->writer->GetFontHeight();
        const nn::font::Font* font = mFontMgr->getFontByMessageIndex(font_index);
        const f32 pict_font_height = font->GetHeight();
        const f32 scale = font_height / pict_font_height * m31();
        context->writer->SetFont(font);
        context->writer->SetItalicRatio(0);
        context->writer->SetScale(scale, scale);
    } else {
        context->writer->SetFont(_18);
        context->writer->SetScale(mSavedScaleX, mSavedScaleY);
        context->writer->SetItalicRatio(mSavedItalicRatio);
        const f32 italic_ratio = mSavedItalicRatio;
        if (italic_ratio > 0) {
            const f32 font_width = context->writer->GetFontWidth();
            context->writer->SetCursorX(context->writer->GetCursorX() +
                                         italic_ratio * font_width * -0.5f);
        }
    }
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

// 0x7100be6fa0
// NON_MATCHING: tag traversal, span length conversion, and floating-point call scheduling differ.
TagProcessor::Operation TagProcessor::m26(const sead::MessageSet<char16>::TagInfo* tag,
                                         nn::font::PrintContext<u16>* context,
                                         nn::font::Rectangle*, const char16* next) {
    u16 count;
    u16 width;
    std::memcpy(&count, tag->getParam(), sizeof(count));
    std::memcpy(&width, tag->getParam() + 2, sizeof(width));
    const char16* end = next;
    u32 characters = 0;
    while (characters != count) {
        if (*end == 0xe) {
            end = reinterpret_cast<const char16*>(reinterpret_cast<const u8*>(end) + 8 + end[3]);
        } else if (*end == 0xf) {
            end += 3;
        } else {
            ++characters;
            ++end;
        }
    }
    nn::font::Rectangle rect{};
    context->writer->CalculateStringRect(&rect, reinterpret_cast<const u16*>(next), end - next);
    const f32 measured_width = rect.right - rect.left;
    const f32 max_width = f32(width) / 256.0f * context->writer->GetFontWidth();
    if (max_width < measured_width) {
        context->writer->SetScale(max_width / measured_width * context->writer->GetScaleX(),
                                  context->writer->GetScaleY());
    }
    context->str = reinterpret_cast<const u16*>(next);
    return Operation_Default;
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

// 0x7100be62b8
char16* TagProcessor::setFitWidthTag(char16* out, u16 count, f32 width) {
    out[0] = 0xe;
    out[1] = 0;
    out[2] = 0x83;
    out[3] = 4;
    out[4] = count;
    out[5] = sead::Mathf::round(width * 256.0f);
    return out + 6;
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
