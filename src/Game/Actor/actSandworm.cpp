#include "Game/Actor/actSandworm.h"

namespace uking::act {

// NON_MATCHING: member types incomplete
Sandworm::~Sandworm() = default;

void Sandworm::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    Enemy::m76(setter);
}

}  // namespace uking::act
