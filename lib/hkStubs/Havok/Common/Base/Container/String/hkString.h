#pragma once

#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

namespace hkString {

int strCmp(const char* s1, const char* s2);
// Native 1594548 and complete hkOstream callers1588184/15880D0 consume a
// null-terminated string and use the returned signed 32-bit length.
int strLen(const char* str);
// Native wrappers zero-extend their 32-bit byte counts to the C library's size_t.
// Full consumers 16ADFD8 and 17EFFB4 compare strings and byte buffers respectively.
int strNcmp(const char* s1, const char* s2, hkUint32 count);
int memCmp(const void* buffer1, const void* buffer2, hkUint32 numBytes);
// Native C-library searches and full consumers 1590590/17F38A4 return positions
// within the source string, which they use for offsets and subsequent searches.
const char* strStr(const char* str, const char* substring);
const char* strChr(const char* str, int character);
hkBool beginsWith(const char* str, const char* prefix);
hkBool endsWith(const char* str, const char* suffix);

}  // namespace hkString
