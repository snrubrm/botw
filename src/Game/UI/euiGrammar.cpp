#include "Game/UI/euiGrammar.h"
#include <devenv/seadEnvUtil.h>

namespace eui {

// 0x7100be39b8
void Grammar::setWordAttrFromTag(WordAttr* attr, const sead::MessageSet<char16>::TagInfo& tag) {
    const u8* param = tag.getParam();
    attr->_0 = param[0];
    attr->_1 = param[1];
    attr->_2 = param[2];
    attr->_3 = param[3];
}

// 0x7100be3a94
u64 Grammar::getWordAttrCount(s32 count) {
    switch (sead::EnvUtil::getLanguage().value()) {
    case sead::LanguageID::fr:
        return u32(count + 1) > 2;
    case sead::LanguageID::ru: {
        const s32 mod10 = count % 10;
        const s32 mod100 = count % 100;
        if (mod10 == 1 && mod100 != 11)
            return 0;
        if (mod10 == 2 && mod100 != 12)
            return 2;
        if (mod10 == 3 && mod100 != 13)
            return 2;
        return 1 + (mod10 == 4 && mod100 != 14);
    }
    default:
        if (count == -1 || count == 1)
            return 0;
        return 1;
    }
}

// NON_MATCHING: the control flow differs. The original tests `c == 0xe || c == 0xf` as `(c | 1) == 0xf` and the
// white space characters ('\n', '\r', ' ', 0x3000) as a bit test, as separate steps; our if chain over the same
// characters is turned into one switch with a jump table.
// 0x7100be41e4
bool Grammar::isStringEndWithPatchim(const char16* string, u32 length, bool ignore_rieul) {
    char16 last = 0;
    if (length != 0) {
        const char16* end = string + length;
        do {
            const char16 c = *string;
            if (c == 0xe || c == 0xf) {
                if (c == 0xf) {
                    // end tag: marker, group, type
                    string += 3;
                } else {
                    // start tag: marker, group, type, parameter size (bytes), parameters
                    string = reinterpret_cast<const char16*>(reinterpret_cast<const u8*>(string) + 8 + string[3]);
                }
            } else if (c == '\n' || c == '\r' || c == ' ' || c == 0x3000) {
                ++string;
            } else {
                last = c;
                ++string;
            }
        } while (string < end);
    }

    if (last == 0)
        return false;

    if (last >= 0xac00 && last <= 0xd7a3) {
        const s32 final_consonant = (last - 0xac00) % 28;
        return final_consonant != 0 && (final_consonant != 8 || !ignore_rieul);
    }

    if (u16(last - '0') >= 10 && u16(last + 0xf0) > 9)
        return true;

    const s32 digit = last < 0x3a ? last - '0' : last - 0xff10;
    if (ignore_rieul) {
        if (digit >= 7)
            return false;
        return (0x49 >> digit) & 1;
    }
    if (u32(digit - 2) >= 8)
        return true;
    return (0x72 >> (digit - 2)) & 1;
}

}  // namespace eui
