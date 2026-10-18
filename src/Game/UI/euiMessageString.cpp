#include "Game/UI/euiMessageString.h"

namespace eui {

// 0x7100be4fdc
MessageString::MessageString() : mString(nullptr), _8(0) {}

// 0x7100be4fe8
MessageString::MessageString(s32 length, const char16* string) : mString(string), _8(length) {}

// 0x7100be4ff4
MessageString::MessageString(const sead::WSafeString& string)
    : mString(string.cstr()), _8(string.calcLength()) {}

// 0x7100be50a8
MessageString::MessageString(const MessageString& other) : mString(other.mString), _8(other._8) {}

// 0x7100be50bc
void MessageString::assign(const MessageString& other) {
    mString = other.mString;
    _8 = other._8;
}

// 0x7100be50d0
// NON_MATCHING: tag dispatch and the loop-exit flags are emitted differently.
bool MessageString::sub_7100BE50D0(sead::WBufferedSafeString* out) const {
    char16* buffer = out->getBuffer();
    const char16* current = mString;
    const char16* end = mString + _8;
    const s32 capacity = out->getBufferSize();
    s32 written = 0;
    while (written < capacity && current < end) {
        if (*current == 0xe) {
            // Tag payload lengths are bytes; this is the same byte traversal as TagProcessor::m9.
            current = reinterpret_cast<const char16*>(
                reinterpret_cast<const u8*>(current) + 8 + current[3]);
        } else if (*current == 0xf) {
            current += 3;
        } else {
            buffer[written++] = *current++;
        }
    }
    const bool fits = current >= end && written < capacity;
    buffer[fits ? written : capacity - 1] = 0;
    return fits;
}

}  // namespace eui
