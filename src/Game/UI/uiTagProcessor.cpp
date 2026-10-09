#include "Game/UI/uiTagProcessor.h"
#include <cstring>
#include <devenv/seadEnvUtil.h>
#include <nn/font/font_PrintContext.h>
#include <nn/font/font_TextWriterBase.h>
#include "Game/UI/uiUI.h"
#include "KingSystem/GameData/gdtManagerInline.h"

namespace uking::ui {

// 0x71010afb74
TagProcessor::TagProcessor(eui::MessageMgr* message_mgr, eui::FontMgr* font_mgr)
    : eui::TagProcessor(message_mgr, font_mgr) {
    mRubyEnabled = false;
}

// 0x71010b2018
// NON_MATCHING: regional array indexing and cursor arithmetic scheduling differ.
TagProcessor::Operation TagProcessor::processPictFontProcessTag_(
    const sead::MessageSet<char16>::TagInfo* tag, nn::font::PrintContext<u16>* context,
    nn::font::Rectangle* rect, const char16* next) {
    const Operation result = eui::TagProcessor::processPictFontProcessTag_(tag, context, rect, next);
    const auto language = sead::EnvUtil::getRegionLanguage();
    if (language == sead::RegionLanguageID::KRko || language == sead::RegionLanguageID::CNzh ||
        language == sead::RegionLanguageID::TWzh) {
        static const f32 offsets[] = {0.08f, 0.06f, 0.08f};
        const f32 offset = offsets[language.getRelativeIndex() - sead::RegionLanguageID::KRko] *
                           (mSavedScaleY * context->writer->GetFontHeight());
        u16 font_index;
        std::memcpy(&font_index, tag->getParam(), sizeof(font_index));
        context->writer->SetCursorY(context->writer->GetCursorY() +
                                   (font_index == 0xffff ? -offset : offset));
    }
    return result;
}

// 0x71010b20a8
f32 TagProcessor::m31() const {
    return _58;
}

// NON_MATCHING: store scheduling (the original stores _2c = 100 second).
// 0x71010afbbc
s32 TagProcessor::m9(char16* out, u32* text_length, u32* character_count, u32 capacity, const char16* text,
                     u32 length, s32 page, u32 line_count, bool trim_newlines, void*) {
    eui::TagParseState state(text, length);
    _5c = false;
    _5d = false;
    return eui::TagProcessor::m9(out, text_length, character_count, capacity, text, length, page, line_count,
                                 trim_newlines, &state);
}

// NON_MATCHING: the original does not thread the jump from the first 0x50 check to the second one.
// 0x71010afc50
void TagProcessor::m10(const sead::MessageSet<char16>::TagInfo* tag, char16* out, u32* text_length,
                       u32* character_count, u32 capacity, const char16* text, u32 length, void* user_data) {
    auto* state = static_cast<eui::TagParseState*>(user_data);
    const u16* param = reinterpret_cast<const u16*>(tag->getParam());
    if (tag->type == 2) {
        if (*character_count == 0 && *param == 0x50)
            _5c = true;
        if (*param != 0x50)
            _5c = false;
        state->_2c = *param;
    } else if (tag->type == 3) {
        if (*param == 3)
            _5d = true;
    }
    eui::TagProcessor::m10(tag, out, text_length, character_count, capacity, text, length, user_data);
}

// 0x71010afc24
f32 TagProcessor::m27() const {
    return UI::instance()->sub_71010A719C();
}

// 0x71010afc34
f32 TagProcessor::m29() const {
    return UI::instance()->sub_71010A71A8();
}

// 0x71010afc44
f32 TagProcessor::m28() const {
    return 0.67f;
}

// 0x71010b20b0
// NON_MATCHING: bool-result normalization differs in the JumpButtonChange cases.
void TagProcessor::m32(char16* glyph, u16* font_index, u8 type) {
    *font_index = 2;
    char16 result = 0xe050;
    switch (type) {
    case 0:
        result = 0xe052;
        break;
    case 1:
        break;
    case 2:
        result = 0xe05a;
        break;
    case 3:
        result = 0xe058;
        break;
    case 4:
        result = 0xe05d;
        break;
    case 5:
        result = 0xe055;
        break;
    case 6:
        result = 0xe060;
        break;
    case 7:
        result = 0xe061;
        break;
    case 8:
        result = 0xe062;
        break;
    case 9:
        result = 0xe063;
        break;
    case 10:
    case 11:
        result = 0xe040;
        break;
    case 12:
    case 37: {
        bool changed = false;
        result = ksys::gdt::getBoolByName(ksys::gdt::Manager::instance(), &changed,
                                         "JumpButtonChange") && changed ? 0xe041 : 0xe042;
        break;
    }
    case 13:
        result = 0xe043;
        break;
    case 14:
    case 15:
        result = 0xe046;
        break;
    case 16:
    case 17:
    case 18:
    case 19: {
        bool changed = false;
        result = ksys::gdt::getBoolByName(ksys::gdt::Manager::instance(), &changed,
                                         "JumpButtonChange") && changed ? 0xe042 : 0xe041;
        break;
    }
    case 20:
        result = 0xe044;
        break;
    case 21:
        result = 0xe045;
        break;
    case 22:
        result = 0xe047;
        break;
    case 23:
        result = 0xe04b;
        break;
    case 24:
        result = 0xe04c;
        break;
    case 25:
        result = 0xe087;
        break;
    case 26:
        result = 0xe088;
        break;
    case 27:
        result = 0xe089;
        break;
    case 28:
        result = 0xe08a;
        break;
    case 29:
        result = 0xe08b;
        break;
    case 30:
        result = 0xe08c;
        break;
    case 31:
        result = 0xe08d;
        break;
    case 32:
        result = 0xe08e;
        break;
    case 33:
        result = 0xe05e;
        break;
    case 34:
        result = 0xe05f;
        break;
    case 35:
        result = 0xe054;
        break;
    case 36:
        result = 0xe066;
        break;
    case 38:
        result = 0xe042;
        break;
    default:
        result = 0;
        break;
    }
    *glyph = result;
}

}  // namespace uking::ui
