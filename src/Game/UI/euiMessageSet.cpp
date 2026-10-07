#include "Game/UI/euiMessageSet.h"

// libms (message binary library; part of the original executable, CSV LMS_*).
extern "C" {
s32 LMS_GetTextIndexByLabel(void* handle, const char* label);
const char16* LMS_GetText(void* handle, s32 index);
}

namespace eui {

MessageSet::MessageSet() = default;

// 0x7100be4e88
MessageString MessageSet::findMessage(const char* label) const {
    const s32 index = LMS_GetTextIndexByLabel(mHandle, label);
    if (index < 0)
        return MessageString();

    const s32 length = calcTextSizeByIndex(index) >> 1;
    const char16* text = u32(mTextNum) > u32(index) ? LMS_GetText(mHandle, index) : nullptr;
    return MessageString(length, text);
}

// 0x7100be4f10
MessageString MessageSet::tryFindMessage(const char* label) const {
    const s32 index = LMS_GetTextIndexByLabel(mHandle, label);
    if (index < 0)
        return MessageString();

    const s32 length = calcTextSizeByIndex(index) >> 1;
    const char16* text = u32(mTextNum) > u32(index) ? LMS_GetText(mHandle, index) : nullptr;
    return MessageString(length, text);
}

bool MessageSet::sub_7100BE4F98(const char* label) const {
    return LMS_GetTextIndexByLabel(mHandle, label) >= 0;
}

}  // namespace eui
