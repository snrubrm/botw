#include <basis/seadNew.h>
#include "Game/Actor/actBeamBase.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

Beam::Beam(const CreateArg& arg) : BeamBase(arg) {}

ksys::act::BaseProc* Beam::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Beam(arg);
}

bool Beam::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return BeamBase::prepareInit_(heap, arg);
}

void Beam::updatePositionMaybe() {
    BeamBase::updatePositionMaybe();
}

void Beam::initMaybe() {
    BeamBase::initMaybe();
    _c88 = mMainBody;
    _c90 = findPhysicsBodyByName("Atk", "AtkBody");
}

void Beam::m165(sead::Vector3f* out) {
    _c88->getPosition(out);
}

}  // namespace uking::act
