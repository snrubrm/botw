#pragma once

#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::phys {

class CharacterController;

class CharacterControllerRigidBody : public RigidBody {
    SEAD_RTTI_OVERRIDE(CharacterControllerRigidBody, RigidBody)
public:
    CharacterControllerRigidBody(CharacterController* controller, hkpRigidBody* body,
                                 sead::Heap* heap, const sead::SafeString& name);
    ~CharacterControllerRigidBody() override;

    float getVolume() override;
    bool setTimeFactor(float value) override;
    u32 getCollisionMasks(CollisionMasks* masks, const u32* shape_key,
                          const sead::Vector3f& contact_point) override;

protected:
    const hkpShape* getNewHavokShape_() override;
    float updateScale_(float scale, float old_scale) override;

private:
    CharacterController* mController;
};
KSYS_CHECK_SIZE_NX150(CharacterControllerRigidBody, 0xd8);

}  // namespace ksys::phys
