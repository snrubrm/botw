#include <Havok/Common/Base/Container/String/hkString.h>

#include <cstring>

namespace hkString {

int strCmp(const char* s1, const char* s2) {
    return std::strcmp(s1, s2);
}

int strLen(const char* str) {
    return std::strlen(str);
}

// NON_MATCHING: return branches and loop register allocation differ.
hkBool endsWith(const char* str, const char* suffix) {
    const int length = strLen(str);
    const int suffixLength = strLen(suffix);
    if (length >= suffixLength) {
        const char* end = str + (length - suffixLength);
        for (int i = 0; i < suffixLength; ++i) {
            if (end[i] != suffix[i])
                return false;
        }
        return true;
    }
    return false;
}

}  // namespace hkString
