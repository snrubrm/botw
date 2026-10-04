#include "Game/UI/euiTextBoxEx.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiTextSearcher.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/euiLetterAnimControl.h"
#include <gfx/nin/seadGraphicsNvn.h>
#include <new>
#include <nn/ui2d/BuildTypes.h>
#include <nn/ui2d/ResExtUserData.h>
#include <prim/seadSafeString.h>
#include <math/seadMathCalcCommon.h>
#include <nn/font/font_TextWriterBase.h>
#include <cfloat>

namespace eui {

void ProcessMessageAppTag(const MessageString& message,
                          sead::IDelegate1<const sead::MessageSet<char16>::TagInfo*>* callback);

// 0x7100be21b0
TextBoxEx::TextBoxEx(const nn::ui2d::ResTextBox* resource,
                     const nn::ui2d::ResTextBox* override_resource,
                     const nn::ui2d::BuildArgSet& args,
                     nn::ui2d::TextBox::InitializeStringParam* param)
    : nn::ui2d::TextBox(nullptr, sead::GraphicsNvn::instance()->getNnDevice(), param,
                       resource, override_resource, args) {
    mBits._6 = false;
    SetTagProcessor(static_cast<eui::TextSearcher*>(args.mTextSearcher)->getTagProcessor());
    if (FindExtUserDataByName("LetterAnimOn"))
        param->mBufferLength += 10;
}

// 0x7100be227c
TextBoxEx::TextBoxEx(const TextBoxEx& other, LayoutEx* layout)
    : nn::ui2d::TextBox(other, sead::GraphicsNvn::instance()->getNnDevice()) {
    Screen* screen = layout->mScreen;
    if (screen) {
        if (const auto* data = FindExtUserDataByName("LetterAnimOn")) {
            const f32 speed = data->GetFloatArray()[0];
            void* memory = nn::ui2d::Layout::AllocateMemory(sizeof(LetterAnimControl), 4);
            auto* control = memory ? new (memory) LetterAnimControl : nullptr;
            control->initialize(GetNwAllocatorHeap(), this, layout);
            control->sub_7100BD9B68(speed);
            screen->mControls.linkPrev(&control->_8);
        }
    }
}

// 0x7100be2350
void TextBoxEx::InitializeString(nn::ui2d::BuildResultInformation* result, nn::gfx::Device* device,
                                 const nn::ui2d::BuildArgSet& args,
                                 const nn::ui2d::TextBox::InitializeStringParam& param) {
    nn::ui2d::TextBox::InitializeString(result, device, args, param);
    adjustText_(const_cast<LayoutEx*>(static_cast<const LayoutEx*>(args.mParentLayout)));
}

// NON_MATCHING: pane-width and virtual-call scheduling differ; short buffer arguments are narrowed.
// 0x7100be24e0
bool TextBoxEx::InitializeStringWithTextSearcherInfo(
    nn::gfx::Device* device, const nn::ui2d::BuildArgSet&,
    const nn::ui2d::TextSearcher::TextInfo& info) {
    const bool animated = getLetterAnimSpeed_(nullptr);
    u32 reserve_characters = 0;
    u32 reserve_buffer = 0;
    if (isTextChangeOn_()) {
        const f32 available_height = GetSize().height - mFontSize.height;
        reserve_characters = available_height < 0.0f ? 1 :
            sead::Mathf::floor(available_height / (mFontSize.height + mLineSpace)) + 1;
        f32 character_width = mFontSize.width * 0.4f;
        f32 min_scale = 0.0f;
        if (getTextAdjustMinScale_(&min_scale))
            character_width *= min_scale;
        const f32 available_width = GetSize().width - character_width;
        reserve_characters *= available_width < 0.0f ? 1 :
            sead::Mathf::floor(available_width / (character_width + mCharSpace)) + 1;
        reserve_buffer = reserve_characters * 2 + (animated ? 10 : 0);
    }
    if (info.mText) {
        sead::WFixedSafeString<2048> buffer;
        u32 text_length = 0;
        u32 character_count = 0;
        m42(&buffer, &text_length, &character_count,
            reinterpret_cast<const char16*>(info.mText), info.mTextLength, u32(-1), false, nullptr);
        u32 min_buffer = text_length;
        if (!text_length || !character_count) {
            min_buffer = 1;
            character_count = 1;
        }
        if (animated)
            min_buffer += 10;
        reserve_buffer = sead::Mathu::max(reserve_buffer, sead::Mathu::max(min_buffer, info.mBufferLength));
        reserve_characters = sead::Mathu::max(reserve_characters, sead::Mathu::max(character_count, info.mBufferLength));
        if (info._10 > 0) {
            reserve_buffer = sead::Mathu::max(reserve_buffer, u32(info._10) * 2);
            reserve_characters = sead::Mathu::max(reserve_characters, u32(info._10));
        }
        AllocateStringBuffer(device, reserve_buffer, reserve_characters);
        nn::ui2d::TextBox::SetString(reinterpret_cast<const u16*>(buffer.cstr()), 0, text_length);
        return true;
    }
    if (reserve_buffer) {
        if (info._10 > 0) {
            reserve_buffer = sead::Mathu::max(reserve_buffer, u32(info._10) * 2 + (animated ? 10 : 0));
            reserve_characters = sead::Mathu::max(reserve_characters, u32(info._10));
        }
        AllocateStringBuffer(device, reserve_buffer, reserve_characters);
    }
    return false;
}

// 0x7100be2444
u16 TextBoxEx::setStringNoPreproces(const char16* string, u16 length) {
    if (string)
        return nn::ui2d::TextBox::SetString(reinterpret_cast<const u16*>(string), 0, length);
    return nn::ui2d::TextBox::SetString(
        reinterpret_cast<const u16*>(sead::WSafeString::cEmptyString.cstr()), 0, 0);
}

// 0x7100be24a0
void TextBoxEx::processAppTag(sead::IDelegate1<const sead::MessageSet<char16>::TagInfo*>* callback) {
    MessageString message(mTextLength, reinterpret_cast<const char16*>(mTextBuf));
    ProcessMessageAppTag(message, callback);
}


// 0x7100be2384
u16 TextBoxEx::setMessageString(const MessageString& string, void* user_data) {
    return m41(string.getString(), string.getLength(), nullptr, u32(-1), false, user_data);
}

// 0x7100be23b0
u16 TextBoxEx::setMessageStringWithPage(const MessageString& string, bool* has_next_page, u32 page,
                                     bool flag, void* user_data) {
    return m41(string.getString(), string.getLength(), has_next_page, page, flag, user_data);
}

// NON_MATCHING: the original resolves the virtual call before scanning the string.
// 0x7100be23e4
u16 TextBoxEx::SetString(const u16* string, u16 dst_index) {
    size_t length = 0;
    while (string[length])
        ++length;
    return SetString(string, dst_index, length);
}

// 0x7100be2414
u16 TextBoxEx::SetString(const u16* string, u16, u16 length) {
    return m41(reinterpret_cast<const char16*>(string), length, nullptr, u32(-1), false, nullptr);
}

// 0x7100be2434
u16 TextBoxEx::setStringWithPage(const char16* string, u16 length, bool* has_next_page, u32 page,
                               bool flag, void* user_data) {
    return m41(string, length, has_next_page, page, flag, user_data);
}

// NON_MATCHING: temporary stack placement and final size-update scheduling differ.
// 0x7100be2ba4
void TextBoxEx::adjustText_(LayoutEx* layout) {
    if (!mTextLength || !GetFont())
        return;
    f32 min_scale = 0.0f;
    if (!getTextAdjustMinScale_(&min_scale))
        return;
    if (!layout && IsLocationAdjust()) {
        const auto* data = FindExtUserDataByName("TextScaleOn");
        nn::ui2d::Size size = GetFontSize();
        if (data && data->GetCount() == 2)
            size.width = GetFont()->GetWidth() * data->GetFloatArray()[1];
        else
            size.width = GetFont()->GetWidth() * (size.height / GetFont()->GetHeight());
        SetFontSize(size);
    }
    f32 width = 0.0f;
    if (mTextLength && GetFont()) {
        nn::font::TextWriterBase<u16> writer;
        SetupTextWriter(&writer);
        writer.SetWidthLimit(FLT_MAX);
        width = writer.CalculateStringWidth(mTextBuf, mTextLength);
    }
    if (width > GetSize().width) {
        nn::ui2d::Size size = GetFontSize();
        size.width *= sead::Mathf::max(GetSize().width / width, min_scale);
        SetFontSize(size);
        SetLocationAdjust(true);
        SetGlobalMatrixDirty(true);
    }
}

// 0x7100be2d58
bool TextBoxEx::getTextAdjustMinScale_(f32* scale) {
    const auto* data = FindExtUserDataByName("TextScaleOn");
    if (!data)
        return false;
    if (scale)
        *scale = data->GetFloatArray()[0];
    return true;
}

// 0x7100be2d98
bool TextBoxEx::isWordwrapOn_() {
    const auto* data = FindExtUserDataByName("WordwrapOn");
    if (!data)
        return false;
    return data->GetIntArray()[0] != 0;
}

// NON_MATCHING: the compiler combines the final test into a conditional result.
// 0x7100be2dc8
bool TextBoxEx::isTextChangeOn_() const {
    return mTextId && mTextId[0] == '@';
}

// 0x7100be2dec
bool TextBoxEx::getLetterAnimSpeed_(f32* speed) {
    const auto* data = FindExtUserDataByName("LetterAnimOn");
    if (!data)
        return false;
    if (speed)
        *speed = data->GetFloatArray()[0];
    return true;
}

}  // namespace eui
