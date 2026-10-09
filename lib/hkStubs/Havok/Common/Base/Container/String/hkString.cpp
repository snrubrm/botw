#include <Havok/Common/Base/Container/String/hkString.h>

#include <cstring>

namespace hkString {

int strCmp(const char* s1, const char* s2) {
    return std::strcmp(s1, s2);
}

int strLen(const char* str) {
    return std::strlen(str);
}

int strNcmp(const char* s1, const char* s2, hkUint32 count) {
    return std::strncmp(s1, s2, count);
}

int memCmp(const void* buffer1, const void* buffer2, hkUint32 numBytes) {
    return std::memcmp(buffer1, buffer2, numBytes);
}

const char* strStr(const char* str, const char* substring) {
    return std::strstr(str, substring);
}

const char* strChr(const char* str, int character) {
    return std::strchr(str, character);
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
