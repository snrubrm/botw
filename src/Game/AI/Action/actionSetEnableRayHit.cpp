#include "Game/AI/Action/actionSetEnableRayHit.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SetEnableRayHit::SetEnableRayHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetEnableRayHit::~SetEnableRayHit() = default;

bool SetEnableRayHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetEnableRayHit::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* set = mActor->getPhysics()->findBodyByName(sub_71007A24D0()->cstr())) {
        if (auto* body = set->getRigidBodies()[0])
            body->setFlag200();
    }
    mFlags.set(Flag::Changeable);
}

void SetEnableRayHit::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetEnableRayHit::loadParams_() {}

void SetEnableRayHit::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
