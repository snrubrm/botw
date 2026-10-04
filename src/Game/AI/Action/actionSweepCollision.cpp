#include "Game/AI/Action/actionSweepCollision.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"

namespace uking::action {

SweepCollision::SweepCollision(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SweepCollision::~SweepCollision() = default;

bool SweepCollision::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SweepCollision::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* area = sead::DynamicCast<ksys::act::AreaActor>(mActor)) {
        if (auto* body = area->_840) {
            body->setContactLayer(ksys::phys::ContactLayer::EntityNoHit);
            if (auto* capsule = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(body))
                capsule->setRadius(0.1f);
        }
    }
}

void SweepCollision::leave_() {
    ksys::act::ai::Action::leave_();
}

void SweepCollision::loadParams_() {}

void SweepCollision::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
