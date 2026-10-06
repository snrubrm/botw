#include "Game/Actor/actSandworm.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

Sandworm::Sandworm(const CreateArg& arg) : Enemy(arg) {
    _1c0 = 1;
}

Sandworm::~Sandworm() = default;

ksys::act::BaseProc* Sandworm::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Sandworm(arg);
}

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

void Sandworm::setNecklaceFlag(s32 index) {
    if (index >= 1 && ksys::act::hasTag(this, 0x12ad8456))
        Enemy::setNecklaceFlag(index + 1);
}

void Sandworm::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    Enemy::m76(setter);
}

}  // namespace uking::act
