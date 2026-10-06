#pragma once

#include <basis/seadTypes.h>

namespace ksys::mii {

// Placeholder (lane4 s49; Actor::mUMiiHylianInfo): only the integer at +0x18 that Actor::sub_71011CA00C returns is known.
class HylianInfo {
public:
    u8 _0[0x18];
    /* 0x18 */ s32 _18;
};

}  // namespace ksys::mii
