#include <Havok/Common/Base/Container/String/hkString.h>

#include <cstring>

namespace hkString {

int strCmp(const char* s1, const char* s2) {
    return std::strcmp(s1, s2);
}

int strLen(const char* str) {
    return std::strlen(str);
}

}  // namespace hkString
