#include "Game/AI/Action/actionDgnObj_DLC_CogWheel_Reject.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DgnObj_DLC_CogWheel_Reject::DgnObj_DLC_CogWheel_Reject(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DgnObj_DLC_CogWheel_Reject::~DgnObj_DLC_CogWheel_Reject() = default;

bool DgnObj_DLC_CogWheel_Reject::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DgnObj_DLC_CogWheel_Reject::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor) {
        if (auto* body = mActor->getMainBody()) {
            body->changeMotionType(ksys::phys::MotionType::Keyframed);
            body->setAngularVelocity(sead::Vector3f::zero);
            body->setLinearVelocity(sead::Vector3f::zero);
        }
    }
    playAS("Neutral", false, 0, 0, -1.0f);
}

void DgnObj_DLC_CogWheel_Reject::leave_() {
    ksys::act::ai::Action::leave_();
}

void DgnObj_DLC_CogWheel_Reject::loadParams_() {}

void DgnObj_DLC_CogWheel_Reject::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
