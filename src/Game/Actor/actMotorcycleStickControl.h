#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace uking::act {

// Placeholder names (the objects have no vtable and no out-of-line constructor: the Motorcycle
// constructor initializes them inline). Both are "approach the target value" controllers used for
// the stick values of the Motorcycle: `_0` is the rate used when the value moves towards zero (or
// the target is within epsilon of zero), `_4` the rate when it moves away from zero, `_8` the
// current value.

// CSV (unnamed) 0x71002c8918, Motorcycle +0xb90.
struct Unk_71002c8918 {
    f32 sub_71002C8918(f32 target);

    f32 _0;
    f32 _4;
    f32 _8;
};
KSYS_CHECK_SIZE_NX150(Unk_71002c8918, 0xc);

// CSV motorcycleStickControlStuff 0x7100e72ac0, Motorcycle +0xb9c (X) and +0xba8 (Y).
struct Unk_7100e72ac0 {
    f32 motorcycleStickControlStuff(f32 target);

    f32 _0;
    f32 _4;
    f32 _8;
};
KSYS_CHECK_SIZE_NX150(Unk_7100e72ac0, 0xc);

}  // namespace uking::act
