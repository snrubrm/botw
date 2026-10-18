#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>

namespace eui {

// Result of a message lookup (ui::getMessage). Layout from the inlined construction: the 16-byte
// object is zero-initialised by the out-of-line constructor 0x7100be4fdc and has no destructor.
class MessageString {
public:
    MessageString();
    // 0x7100be4fe8 (CSV _ZN3eui13MessageStringC1EiPKDs; the first argument is the string length)
    MessageString(s32 length, const char16* string);
    // 0x7100be4ff4: the string and its length
    explicit MessageString(const sead::WSafeString& string);
    // 0x7100be50a8 (out-of-line copy constructor; the original has no inline copy). It is user-provided:
    // MessageSet::findMessage returns MessageString by value through a hidden pointer, which only happens for types
    // with a non-trivial copy constructor.
    MessageString(const MessageString& other);
    // 0x7100be50bc (CSV eui::MessageString::assign)
    void assign(const MessageString& other);
    // 0x7100be50d0: copy text without message tags; false if the output buffer fills.
    // Const spelling is inferred from the read-only receiver.
    bool sub_7100BE50D0(sead::WBufferedSafeString* out) const;

    // inline-only in the original; names are guesses: both TextBoxEx message setters read these fields.
    const char16* getString() const { return mString; }
    s32 getLength() const { return _8; }

private:
    const char16* mString;  // null if the message was not found
    s32 _8;
};

}  // namespace eui
