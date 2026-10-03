#include "Game/Actor/actGiantEnemy.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

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

void GiantEnemy::m110(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 0;
    } else {
        Actor::m110(a1, a2);
    }
}

void GiantEnemy::m111(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 2;
    } else {
        Actor::m111(a1, a2);
    }
}

void GiantEnemy::m112(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 0;
    } else {
        Actor::m112(a1, a2);
    }
}

void GiantEnemy::m113(f32* a1, s32* a2) {
    // tag hash 0xa4c7ba34 (no name known)
    if (ksys::act::hasTag(this, 0xA4C7BA34u)) {
        *a1 = 0.4f;
        *a2 = 2;
    } else {
        Actor::m113(a1, a2);
    }
}

}  // namespace uking::act
