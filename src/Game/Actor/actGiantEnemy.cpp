#include "Game/Actor/actGiantEnemy.h"

namespace uking::act {

// NON_MATCHING: member types incomplete
GiantEnemy::~GiantEnemy() = default;

void GiantEnemy::killWithDropsAndEffects(int a1) {
    Enemy::killWithDropsAndEffects(a1);
    incrementGiantOrSandwormDefeatCount();
}

void GiantEnemy::calcMaybe() {
    Enemy::calcMaybe();
}

void GiantEnemy::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    _14c8.sub_710002A94C(this);
    Enemy::m76(setter);
}

void GiantEnemy::m145() {}

}  // namespace uking::act
