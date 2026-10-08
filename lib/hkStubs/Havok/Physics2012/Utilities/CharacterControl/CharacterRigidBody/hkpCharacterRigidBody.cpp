#include <Havok/Physics2012/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>

hkpRigidBody* hkpCharacterRigidBody::getRigidBody() const {
    return m_character;
}

void hkpCharacterRigidBody::setLinearVelocity(const hkVector4f& velocity) {
    m_velocity = velocity;
}
