#include "Game/UI/euiGrammar.h"
#include <devenv/seadEnvUtil.h>

namespace eui {

// NON_MATCHING: character append remains an out-of-line SDK call and loop lowering differs.
// 0x7100be3d48
s32 Grammar::formatNumberWithDelimiter(sead::StringBuilder* out, u64 value) {
    const bool grouped = sead::EnvUtil::getRegion() == sead::RegionID::US ||
                         sead::EnvUtil::getRegion() == sead::RegionID::EU;
    const bool first_group = sead::EnvUtil::getLanguage() == sead::LanguageID::en ||
                             sead::EnvUtil::getRegionLanguage() == sead::RegionLanguageID::EUfr;
    sead::FixedSafeString<24> number;
    const s32 length = number.format("%lld", value);
    s32 required = length;
    if (grouped && length > 3) {
        required += (length - 1) / 3;
        if ((length - 1) % 3 == 0 && !first_group)
            --required;
    }
    if (out->getBufferSize() <= required)
        return -1;
    out->clear();
    if (length < 4 || !grouped) {
        out->copy(number.cstr());
        return length;
    }
    char delimiter;
    if (sead::EnvUtil::getLanguage() == sead::LanguageID::en)
        delimiter = ',';
    else if (sead::EnvUtil::getLanguage() == sead::LanguageID::de ||
             sead::EnvUtil::getLanguage() == sead::LanguageID::it ||
             sead::EnvUtil::getLanguage() == sead::LanguageID::nl)
        delimiter = '.';
    else
        delimiter = ' ';
    const s32 end = number.calcLength() + 1;
    for (s32 i = 0; i != end; ++i) {
        out->append(number.at(i));
        const s32 remaining = length - i;
        if (remaining >= 2 && (remaining - 1) % 3 == 0 && (first_group || i != 0))
            out->append(delimiter);
    }
    return required;
}

// 0x7100be39b8
void Grammar::setWordAttrFromTag(WordAttr* attr, const sead::MessageSet<char16>::TagInfo& tag) {
    const u8* param = tag.getParam();
    attr->_0 = param[0];
    attr->_1 = param[1];
    attr->_2 = param[2];
    attr->_3 = param[3];
}

// 0x7100be39dc (CSV unnamed): find a group-0xc9 type-0 tag in the message text, fill the attribute
// bytes from its parameters.
// NON_MATCHING: the original has a third (dead) tag-marker arm that loads from a null pointer;
// only the 0xe/0xf arms are reachable (the (head|1) pre-check proves it), so it is omitted here.
// Also differs in the 0xe arm's register assignment (temp + mov), q's register, the duplicated
// bounds-check layout, and the tail. The 0xe arm is written first: clang otherwise emits the
// 0xe/0xf tests swapped (same as sub_71010B307C).
bool Grammar::sub_7100BE39DC(WordAttr* attr, const MessageString& message) {
    const char16* text = message.getString();
    if (text == nullptr || (s32)message.getLength() < 1)
        return false;
    const char16* end = text + (s32)message.getLength();
    const char16* p = text;
    do {
        char16 head = *p;
        if ((head | 1) != 0xf) {
            ++p;
            continue;
        }
        const char16* q;
        // Note: written 0xe-first: clang emits the 0xf test first (as in the original); the
        // written 0xf-first order emits the tests swapped (unexplained, seen in sub_71010B307C too).
        if (head == 0xe) {
            q = p;
            p = reinterpret_cast<const char16*>(reinterpret_cast<const u8*>(p) + p[3] + 8);
        } else if (head == 0xf) {
            q = p;
            p += 3;
        } else {
            return false;
        }
        if (q[1] == 0xc9 && q[2] == 0) {
            const u8* param = reinterpret_cast<const u8*>(q);
            attr->_0 = param[8];
            attr->_1 = param[9];
            attr->_2 = param[10];
            attr->_3 = param[11];
            return true;
        }
    } while (p < end);
    return false;
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
