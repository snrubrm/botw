#include "Game/Actor/actSandworm.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

// NON_MATCHING: member types incomplete
Sandworm::~Sandworm() = default;

void Sandworm::killWithDropsAndEffects(int a1) {
    sub_71002CDB48();
    Enemy::killWithDropsAndEffects(a1);
    incrementGiantOrSandwormDefeatCount();
}

void Sandworm::m56(sead::Vector3f* pos) {
    if (_1650 && _1650->isAddedToWorld())
        _1650->getCenterOfMassInWorld(pos);
    else
        x_18(pos);
}

void Sandworm::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    Enemy::m76(setter);
}

}  // namespace uking::act
