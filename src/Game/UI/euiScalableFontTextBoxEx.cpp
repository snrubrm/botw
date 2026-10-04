#include "Game/UI/euiScalableFontTextBoxEx.h"
#include <nn/font/font_ScalableFont.h>
#include <nn/ui2d/BuildTypes.h>
#include "Game/UI/euiFontMgr.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiTextSearcher.h"

namespace eui {

// NON_MATCHING: font-manager and zero-state stores are combined after the lookup.
// 0x7100be1a98
ScalableFontTextBoxEx::ScalableFontTextBoxEx(
    const nn::ui2d::ResTextBox* resource, const nn::ui2d::ResTextBox* replacement,
    const nn::ui2d::BuildArgSet& args, nn::ui2d::TextBox::InitializeStringParam* string_param)
    : TextBoxEx(resource, replacement, args, string_param),
      mFontMgr(static_cast<const TextSearcher*>(args.mTextSearcher)->getTagProcessor()->mFontMgr),
      _168(0), _16c(0) {}

// 0x7100be1ae0
ScalableFontTextBoxEx::ScalableFontTextBoxEx(const ScalableFontTextBoxEx& other, LayoutEx* layout)
    : TextBoxEx(other, layout), mFontMgr(other.mFontMgr), _168(0), _16c(0) {}

// 0x7100be1b1c
void ScalableFontTextBoxEx::Calculate(nn::ui2d::DrawInfo& info,
                                     nn::ui2d::Pane::CalculateContext& context, bool force) {
    auto* manager = mFontMgr->getScalableFontMgr();
    if (_168 == 0) {
        if (!manager->mCacheUpdatePending)
            sub_7100BE1BDC(manager);
    } else if (_168 == 1) {
        if (_16c < manager->mCacheGeneration) {
            if (_16c + 1 < manager->mCacheGeneration) {
                if (!manager->mCacheUpdatePending)
                    sub_7100BE1BDC(manager);
            } else {
                _168 = 2;
                _16c = manager->mCacheGeneration;
                mBits.textChanged = 1;
            }
        }
    } else if (_16c < manager->mCacheGeneration) {
        if (!manager->mCacheUpdatePending)
            sub_7100BE1BDC(manager);
    }
    if (_168 != 2)
        context._28 = true;
    nn::ui2d::TextBox::Calculate(info, context, force);
}

// 0x7100be1bdc
void ScalableFontTextBoxEx::sub_7100BE1BDC(ScalableFontMgr* manager) {
    if (auto* font = nn::font::DynamicCast<const nn::font::ScalableFont>(GetFont())) {
        if (manager->sub_7100BE57A4(mTextBuf, mTextLength, font, mFontMgr)) {
            _168 = 2;
            mBits.textChanged = 1;
        } else {
            _168 = 1;
        }
        _16c = manager->mCacheGeneration;
    }
}

// 0x7100be1cfc
u16 ScalableFontTextBoxEx::setStringNoPreproces(const char16* string, u16 length) {
    const u16 result = TextBoxEx::setStringNoPreproces(string, length);
    _168 = 0;
    return result;
}

// 0x7100be1d20
void ScalableFontTextBoxEx::DrawSelf(nn::ui2d::DrawInfo& info, nn::gfx::CommandBuffer& command_buffer) {
    if (_168 == 2)
        nn::ui2d::TextBox::DrawSelf(info, command_buffer);
}

// 0x7100be1d34
s32 ScalableFontTextBoxEx::m42(sead::WBufferedSafeString* out, u32* text_length,
                              u32* character_count, const char16* string, u32 length,
                              u32 page, bool flag, void* user_data) {
    const s32 result = TextBoxEx::m42(out, text_length, character_count, string, length,
                                     page, flag, user_data);
    _168 = 0;
    return result;
}

}  // namespace eui
