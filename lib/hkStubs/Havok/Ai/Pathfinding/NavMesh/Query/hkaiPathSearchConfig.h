#pragma once

#include <Havok/Common/Base/hkBase.h>

// The path-search configuration object built by 0x710155e8fc. The second phase of the navmesh
// search consumes it: 0x71015602f8 forwards to 0x710155fc58, which returns early when the key at
// +0 is -1. The class name and the extent beyond 0x70 are unknown; the fields below are exactly the
// constructor's stores (0x86a0 + 0x10000 at +0x20 is 100000, and 0x3c23d70a at +0x50 is 0.01f).
class Unk_710155E8FC {
public:
    Unk_710155E8FC();

    /* 0x00 */ hkInt32 mKey = -1;
    /* 0x04 */ hkUint8 _04[0x10 - 0x04];
    /* 0x10 */ hkVector4 mZero10;
    /* 0x20 */ hkInt32 mMaximum = 100000;
    /* 0x24 */ hkUint32 mZero24[4] = {};
    /* 0x34 */ hkUint32 _34;
    /* 0x38 */ void* mPtr38 = nullptr;
    /* 0x40 */ void* mPtr40 = nullptr;
    /* 0x48 */ hkReal mField48 = -4.0f;
    /* 0x4c */ hkBool mField4c = true;
    /* 0x4d */ hkBool mField4d = false;
    /* 0x4e */ hkUint8 _4e[2];
    /* 0x50 */ hkReal mTolerance = 0.01f;
    /* 0x54 */ hkUint8 _54[0xc];
    /* 0x60 */ hkVector4 mZero60;
};
static_assert(sizeof(Unk_710155E8FC) == 0x70);
