#pragma once

#include <prim/seadEnum.h>

namespace ksys::act {

// Placeholder enum (a 4-byte SEAD_ENUM in the original: the result of ActorConstDataAccess::sub_7100D14598 goes
// through a stack slot; it is the ridden animal type of the horse unit param, 11 is compared by PlayerBase::x_48).
SEAD_ENUM(Unk_7100d14598, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15)

}  // namespace ksys::act
