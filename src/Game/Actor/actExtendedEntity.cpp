#include "Game/Actor/actExtendedEntity.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

ExtendedEntity::ExtendedEntity() = default;

ExtendedEntity::~ExtendedEntity() = default;

void ExtendedEntity::sub_7100E64E60() {
    if (_10) {
        if (_10->_50 & 1)
            _10->sub_7100F6A074();
        if (_8->isAddedToWorld())
            _8->removeFromWorld();
    }
}

void ExtendedEntity::sub_7100E64EAC(f32 scale) {
    if (_0)
        _0->sub_7100F62DD0(scale);
    if (_8)
        _8->setColImpulseScale(scale);
}

}  // namespace uking::act
