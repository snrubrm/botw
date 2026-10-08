#include "KingSystem/Physics/CharacterController/physCharacterRigidBody.h"

namespace ksys::phys {

CharacterRigidBody::CharacterRigidBody(const hkpCharacterRigidBodyCinfo& info)
    : hkpCharacterRigidBody(info), _88(1.0f), _8c(10000.0f) {}

CharacterRigidBody::~CharacterRigidBody() = default;

void CharacterRigidBody::getGround(const hkArray<SupportInfo>&, hkBool, hkpSurfaceInfo&) {}

}  // namespace ksys::phys
