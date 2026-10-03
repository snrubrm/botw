#pragma once

#include <basis/seadTypes.h>

namespace eui {

// Result of a message lookup (ui::getMessage). Layout from the inlined construction: the 16-byte
// object is zero-initialised by the out-of-line constructor 0x7100be4fdc and has no destructor.
class MessageString {
public:
    MessageString();
    // 0x7100be4fe8 (CSV _ZN3eui13MessageStringC1EiPKDs; the first argument is the string length)
    MessageString(s32 length, const char16* string);
    // 0x7100be50bc (CSV eui::MessageString::assign)
    void assign(const MessageString& other);

private:
    const char16* mString;  // null if the message was not found
    u32 _8;
};

}  // namespace eui
