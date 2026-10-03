#pragma once

#include <math/seadMatrix.h>

namespace ksys::act {
class Actor;
}

// 0x7100739498 (declared only; placeholder name): `if (actor && out && actor->getPhysicsMainBody())` writes the
// main body's transform to `out` and returns true, otherwise returns false (AddCarriedBase::m34 ignores the result).
bool sub_7100739498(ksys::act::Actor* actor, sead::Matrix34f* out);
