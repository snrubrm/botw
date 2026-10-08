#include "Game/UI/euiMessageString.h"

namespace eui {

// 0x7100be4fdc
MessageString::MessageString() : mString(nullptr), _8(0) {}

// 0x7100be4fe8
MessageString::MessageString(s32 length, const char16* string) : mString(string), _8(length) {}

// 0x7100be50a8
MessageString::MessageString(const MessageString& other) : mString(other.mString), _8(other._8) {}

// 0x7100be50bc
void MessageString::assign(const MessageString& other) {
    mString = other.mString;
    _8 = other._8;
}

}  // namespace eui
