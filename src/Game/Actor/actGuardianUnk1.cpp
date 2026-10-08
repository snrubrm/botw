#include "Game/Actor/actGuardian.h"

namespace uking::act {

// Separate TU: the original keeps this out of line (Guardian::sub_710003B3FC tail-calls it).
bool Guardian::Unk1::sub_7100042338() const {
    return _8->sub_71000370B4();
}

void Guardian::Unk1::sub_7100042B40() {
    _64 = 0;
}

void Guardian::Unk1::sub_7100042B48() {}

}  // namespace uking::act
