#include "KingSystem/ActorSystem/actUnk_71024ef620.h"
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace ksys::act {

Unk_71024ef620::~Unk_71024ef620() = default;

void sub_7100EBA4AC(Unk_71024ef620* body) {
    delete body;
}

// 0x7100eba300: creates the surfing body from the instance set's "Player" body set. The
// "SurfingBody" rigid body and the "Surfing" contact point and collision records are copied in, and
// the body's inertia and damping values seed the record.
// NON_MATCHING: the original reuses one stack slot per SafeString temporary (three slots, 0x70
// frame) and stores the contact/collision pointers together; ours coalesces the temporaries to one
// slot and interleaves the inlined constructor stores with the lookups.
Unk_71024ef620* sub_7100EBA300(phys::InstanceSet* physics, sead::Heap* heap) {
    phys::RigidBodySet* body_set = physics->findBodyByName("Player");
    if (!body_set)
        return nullptr;

    auto* body = new (heap, 8) Unk_71024ef620;
    body->_10 = body_set->findBodyByHavokName("SurfingBody");
    body->_18 = physics->getCharacterController();

    const s32 contact_index = physics->findContactPointInfo("Surfing");
    body->_20 = contact_index >= 0 ? physics->getContactPointInfoAt(contact_index) : nullptr;

    const s32 collision_index = physics->findCollisionInfo("SurfingBody");
    body->_28 = collision_index >= 0 ? physics->getCollisionInfoAt(collision_index) : nullptr;

    body->_10->getInertiaLocal(&body->_4c);
    body->_58 = body->_10->getLinearDamping();
    body->_64 = body->_10->getAngularDamping();
    body->_68 = body->_10->getMaxAngularVelocity();
    return body;
}

void Unk_71024ef620::sub_7100EBB518() {
    _60.reset(1);
    if (_8) {
        if (auto* rope = sead::DynamicCast<RopeBase>(_8->getConnectedCalcChild())) {
            rope->sub_7100ECDE98();
            rope->sleep(BaseProc::SleepWakeReason::_0);
        }
    }
    _60.reset(0x10);
    _10->triggerScheduledMotionTypeChange();
    _10->setInertiaLocal(_4c);
    _10->setLinearDamping(_58);
    _10->removeFromWorld();
    _30 = nullptr;
    _18->sub_7100F5F458(MotionType::_0);
}

void Unk_71024ef620::sub_7100EBB60C() {
    _60.reset(0x10);
    _10->triggerScheduledMotionTypeChange();
}

void Unk_71024ef620::sub_7100EBB670() {}

void Unk_71024ef620::sub_7100EBB624() {
    sead::Vector3f velocity = _10->getLinearVelocity();
    velocity.x = 0.0f;
    velocity.z = 0.0f;
    _10->setLinearVelocity(velocity);
}

}  // namespace ksys::act
