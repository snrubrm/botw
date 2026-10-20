#include "Game/Actor/actExtendedEntity.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physUtil.h"

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

void ExtendedEntity::sub_7100E63F20() {
    if (_18) {
        ksys::phys::sub_7100FCFEB8(_18);
        _18 = nullptr;
    }
    if (_10) {
        ksys::phys::Constraint::destroy(_10);
        _10 = nullptr;
    }
    _0 = nullptr;
    _8 = nullptr;
    if (_60) {
        operator delete(_60);
        _60 = nullptr;
    }
}

}  // namespace uking::act
