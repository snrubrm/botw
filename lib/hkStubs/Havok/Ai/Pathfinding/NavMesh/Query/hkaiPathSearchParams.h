#pragma once

#include <Havok/Common/Base/hkBase.h>

// The two path-search parameter objects built by 0x7101549660 and 0x71015496c4 and consumed by
// hkaiPathfindingUtil::findGraphPathMaybe 0x7101560368 (via 0x710155f9d8 and 0x710155fc58). The
// class names are unknown. Both are 0x68 bytes with three FLT_MAX vectors at +0, +0x10 and +0x50;
// the only difference is the byte at +0x4c (0 in the first, 1 in the second). The caller
// 0x710155f9d8 copies vectors to +0/+0x10/+0x50, words to +0x20/+0x24/+0x28/+0x30/+0x34/+0x38,
// a byte to +0x49 and words to +0x60, which is the layout below.
class Unk_7101549660 {
public:
    Unk_7101549660();

    /* 0x00 */ hkVector4 mVector0;
    /* 0x10 */ hkVector4 mVector10;
    /* 0x20 */ hkInt32 mKey = -1;
    /* 0x24 */ hkInt32 mMaximum = 100000;
    /* 0x28 */ hkUint8 _28[8] = {};
    /* 0x30 */ hkVector4 mVector30;
    /* 0x40 */ hkUint8 _40[8] = {};
    /* 0x48 */ hkUint8 mFlag48 = 0;
    /* 0x49 */ hkUint8 mFlag49 = 1;
    /* 0x4a */ hkUint8 mFlag4a = 1;
    /* 0x4b */ hkUint8 mFlag4b = 0;
    /* 0x4c */ hkUint8 mFlag4c = 0;
    /* 0x4d */ hkUint8 mFlag4d = 0;
    /* 0x4e */ hkUint8 mFlag4e = 1;
    /* 0x4f */ hkUint8 mFlag4f = 0;
    /* 0x50 */ hkVector4 mVector50;
    /* 0x60 */ hkInt32 mKey60 = -1;
    /* 0x64 */ hkUint8 _64[4];
};
static_assert(sizeof(Unk_7101549660) == 0x70);

class Unk_71015496C4 {
public:
    Unk_71015496C4();

    /* 0x00 */ hkVector4 mVector0;
    /* 0x10 */ hkVector4 mVector10;
    /* 0x20 */ hkInt32 mKey = -1;
    /* 0x24 */ hkInt32 mMaximum = 100000;
    /* 0x28 */ hkUint8 _28[8] = {};
    /* 0x30 */ hkVector4 mVector30;
    /* 0x40 */ hkUint8 _40[8] = {};
    /* 0x48 */ hkUint8 mFlag48 = 0;
    /* 0x49 */ hkUint8 mFlag49 = 1;
    /* 0x4a */ hkUint8 mFlag4a = 1;
    /* 0x4b */ hkUint8 mFlag4b = 0;
    /* 0x4c */ hkUint8 mFlag4c = 1;
    /* 0x4d */ hkUint8 mFlag4d = 0;
    /* 0x4e */ hkUint8 mFlag4e = 1;
    /* 0x4f */ hkUint8 mFlag4f = 0;
    /* 0x50 */ hkVector4 mVector50;
    /* 0x60 */ hkInt32 mKey60 = -1;
    /* 0x64 */ hkUint8 _64[4];
};
static_assert(sizeof(Unk_71015496C4) == 0x70);
