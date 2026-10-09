#pragma once

#include <cstdarg>

#include <Havok/Common/Base/Types/hkBaseDefs.h>
#include <Havok/Common/Base/Types/hkBaseTypes.h>

class hkMemoryAllocator;

namespace hkString {

// Full native 15943E8 copies the AArch64 va_list; 159442C saves GP/vector
// argument registers. Ostream consumers15883C4/15880D0 supply format and buffer.
int vsnprintf(char* buffer, int bufferSize, const char* format, std::va_list args);
int snprintf(char* buffer, int bufferSize, const char* format, ...);
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
// Native allocation/copy wrappers and consumers 16A2344/16AD9A0 establish
// writable duplicate strings, with explicit allocator or the router heap.
char* strDup(const char* str, hkMemoryAllocator* allocator);
char* strDup(const char* str);
void strFree(char* str, hkMemoryAllocator* allocator);
hkBool beginsWith(const char* str, const char* prefix);
hkBool endsWith(const char* str, const char* suffix);

}  // namespace hkString
