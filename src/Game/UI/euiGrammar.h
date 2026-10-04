#pragma once

#include <basis/seadTypes.h>
#include <message/seadMessageSet.h>
#include <prim/seadStringBuilder.h>

namespace eui {

// Language-dependent text helpers (plural forms, delimiters, Korean particles). Only the static helpers are known.
class Grammar {
public:
    // The four attribute bytes of a grammar tag (the tag's parameters)
    struct WordAttr {
        u8 _0;
        u8 _1;
        u8 _2;
        u8 _3;
    };

    // 0x7100be39b8
    static void setWordAttrFromTag(WordAttr* attr, const sead::MessageSet<char16>::TagInfo& tag);
    // 0x7100be3a94: the plural form index of the number for the current language
    static u64 getWordAttrCount(s32 count);
    // 0x7100be3d48: returns the required length, or -1 when the output buffer is too small.
    static s32 formatNumberWithDelimiter(sead::StringBuilder* out, u64 value);
    // 0x7100be41e4: whether the last visible character of the string (tags and white space are skipped) ends with a
    // final consonant (Korean). `ignore_rieul` treats the consonant rieul as no final consonant.
    static bool isStringEndWithPatchim(const char16* string, u32 length, bool ignore_rieul);
};

}  // namespace eui
