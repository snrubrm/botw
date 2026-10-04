#include "Game/UI/euiTextBoxEx.h"
#include <nn/ui2d/ResExtUserData.h>

namespace eui {

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
