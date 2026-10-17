#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/System/physUserTag.h"

namespace ksys::phys {

class CharacterController;

// The 0x68-byte argument of CharacterControllerRigidBody::create, built by
// CharacterControllerParam::createController (0x710128152c): the mass / volume / state prefix, a
// 0x30-byte copied default block at 0x10, then the contact layer, ground hit and the two pointers
// the caller passes through.
struct CharacterControllerCreateArg {
    /* 0x00 */ f32 mass = 0.0f;
    /* 0x04 */ f32 _4 = 1.0f;
    /* 0x08 */ f32 volume = 0.0f;
    /* 0x0c */ u32 state = 1;
    /* 0x10 */ sead::Matrix34f _10 = sead::Matrix34f::ident;
    /* 0x40 */ f32 _40 = 75.0f;
    /* 0x44 */ u32 _44 = 0;
    /* 0x48 */ void* _48 = nullptr;
    /* 0x50 */ ContactLayer contact_layer = ContactLayer::EntityNPC;
    /* 0x54 */ GroundHit ground_hit = GroundHit::HitAll;
    /* 0x58 */ void* _58 = nullptr;
    /* 0x60 */ bool _60 = false;
};
KSYS_CHECK_SIZE_NX150(CharacterControllerCreateArg, 0x68);

class CharacterControllerRigidBody : public RigidBody {
    SEAD_RTTI_OVERRIDE(CharacterControllerRigidBody, RigidBody)
public:
    CharacterControllerRigidBody(CharacterController* controller, hkpRigidBody* body,
                                 sead::Heap* heap, const sead::SafeString& name);
    ~CharacterControllerRigidBody() override;

    // 0x7100f5dc84 (4-byte tail call): creates the controller and its rigid body. The full body is
    // the unnamed function 0x7100f5dc88, which is still undecompiled (declared only).
    static CharacterController* create(const CharacterControllerCreateArg& arg,
                                       const sead::SafeString& name, sead::Heap* heap);

    void sub_7100F6391C(UserTag::Unk5* arg);

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

// 0x7100f5dc88 (2700 B, still undecompiled): the implementation behind create; it allocates the
// 0x2a8-byte CharacterController (constructor 0x7100f5d8b8) and binds the rigid body to it.
CharacterController* sub_7100F5DC88(const CharacterControllerCreateArg& arg,
                                    const sead::SafeString& name, sead::Heap* heap);

}  // namespace ksys::phys
