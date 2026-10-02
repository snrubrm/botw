#include "KingSystem/ActorSystem/actActorAtk.h"

namespace ksys::act {

Struct8Base::Struct8Base() = default;

void Struct8Base::resetFlags() {
    _18 = 0;
}

// Copies the flags first, then the other fields in order.
Struct8Base& Struct8Base::operator=(const Struct8Base& other) {
    _18 = other._18;
    _0 = other._0;
    _c = other._c;
    _20 = other._20;
    _38 = other._38;
    return *this;
}

}  // namespace ksys::act
