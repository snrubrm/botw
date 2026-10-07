#pragma once

#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

class ElementSpark;

// Constructor 0x71010c3114 copies this request, including the Actor pointer at offset 0.
// Field defaults and the final scalar's purpose are not recovered.
struct ElementSparkCreateArg {
    ksys::act::Actor* actor;
    sead::Vector3f position;
    f32 radius;
    f32 life;
    f32 _1c;
};
KSYS_CHECK_SIZE_NX150(ElementSparkCreateArg, 0x20);

namespace ksys::world {

// Null-safe request dispatch through the world manager's chemical element holder.
ElementSpark* sub_71010C30E8(const ElementSparkCreateArg* arg);

}  // namespace ksys::world
