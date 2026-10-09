#pragma once

#include <basis/seadTypes.h>

namespace ksys::act {

// Placeholder name: the object at Actor::_6b8. Sound emission checks its counter at +0x7a;
// FixedMagneStick::calc_ writes its byte at +0x8b.
struct ActorUnk6b8 {
    u8 _0[0x7a];
    // 0x710105e114: values below 2 skip the chemical sound spatial flags.
    u16 _7a;
    u8 _7c[0x8b - 0x7c];
    u8 _8b;
};

}  // namespace ksys::act
