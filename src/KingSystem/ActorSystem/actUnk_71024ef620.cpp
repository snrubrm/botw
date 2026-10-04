#include "KingSystem/ActorSystem/actUnk_71024ef620.h"
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {

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
    _30 = 0;
    _18->sub_7100F5F458(MotionType::_0);
}

void Unk_71024ef620::sub_7100EBB60C() {
    _60.reset(0x10);
    _10->triggerScheduledMotionTypeChange();
}

void Unk_71024ef620::sub_7100EBB624() {
    sead::Vector3f velocity = _10->getLinearVelocity();
    velocity.x = 0.0f;
    velocity.z = 0.0f;
    _10->setLinearVelocity(velocity);
}

}  // namespace ksys::act
