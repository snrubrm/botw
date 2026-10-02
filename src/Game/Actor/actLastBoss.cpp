#include "Game/Actor/actLastBoss.h"

namespace uking::act {

// NON_MATCHING: member types incomplete
LastBoss::~LastBoss() = default;

void LastBoss::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    setter->set(0x20, 0x10);
    _14e8.reset(0x80);
    Enemy::m76(setter);
}

void LastBoss::m77(ksys::VFR::ScopedDeltaSetter* setter) {
    setter->set(0x20, 0x10);
}

bool LastBoss::isGuard() {
    return false;
}

bool LastBoss::isGuardJust() {
    return _14f8._30.isOn(1);
}

bool LastBoss::sub_71002C6210(f32 value) const {
    return _14f0 < value;
}

bool LastBoss::m140() {
    return _14e8.isOnBit(9);
}

}  // namespace uking::act
