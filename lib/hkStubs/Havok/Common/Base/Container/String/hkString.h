#pragma once

#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

namespace hkString {

int strCmp(const char* s1, const char* s2);
// Native 1594548 and complete hkOstream callers1588184/15880D0 consume a
// null-terminated string and use the returned signed 32-bit length.
int strLen(const char* str);
hkBool beginsWith(const char* str, const char* prefix);
hkBool endsWith(const char* str, const char* suffix);

}  // namespace hkString
