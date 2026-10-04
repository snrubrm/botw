#pragma once

#include <basis/seadTypes.h>

namespace eui {

// The text tag processor of the UI texts (nn::font::TagProcessorBase<char16> derived in the original; the base is
// not modelled yet, so only the static helpers are declared). The tag writers below build the tags of
// sead::MessageSet<char16>::TagInfo layout in a text buffer (start marker 0xe, group, type, parameter size in
// bytes, parameters) and return the position after the tag.
class TagProcessor {
public:
    // 0x7100be6254: type 0x80, two parameter bytes (the first is the negated flag)
    static char16* setAlphaTag(char16* out, bool flag, u8 alpha);
    // 0x7100be628c: type 0x82, one u16 parameter
    static char16* setSkipTag(char16* out, u16 count);
    // 0x7100be6308: type 2, one u16 parameter
    static char16* setSizeTag(char16* out, u16 size);
};

}  // namespace eui
