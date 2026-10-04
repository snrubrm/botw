#include "Game/AI/Action/actionDemoSweep.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physEntityGroupFilter.h"

namespace uking::action {

DemoSweep::DemoSweep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoSweep::~DemoSweep() = default;

bool DemoSweep::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoSweep::enter_(ksys::act::ai::InlineParamPack* params) {
    using ksys::phys::GroundHit;
    if (auto* area = sead::DynamicCast<ksys::act::AreaActor>(mActor)) {
        if (auto* body = area->_840) {
            u32 mask = 0;
            mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::Camera);
            mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::CameraBody);
            mask = ksys::phys::orEntityGroundHitMask(mask, GroundHit::Player);
            body->setGroundHitMask(ksys::phys::ContactLayer::EntityGround, mask);
        }
    }
}

void DemoSweep::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoSweep::loadParams_() {
    getDynamicParam(&mDynScalingTime_d, "DynScalingTime");
}

void DemoSweep::calc_() {
    auto* actor = mActor;
    const f32 scale = actor->getScale().x;
    auto* area = sead::DynamicCast<ksys::act::AreaActor>(actor);
    if (!area)
        return;
    auto* body = area->_840;
    if (!body)
        return;
    auto* capsule = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(body);
    if (!capsule)
        return;

    const f32 radius = capsule->getRadius();
    const f32 step = *mDynScalingTime_d > 0.0f ? scale / *mDynScalingTime_d : 1.0f;
    bool finished;
    if (radius < scale) {
        const f32 next = radius + step;
        finished = (next >= scale) | (next < radius);
        capsule->setRadius(finished ? scale : next);
    } else if (radius > scale) {
        const f32 next = radius - step;
        finished = (next <= scale) | (radius < next);
        capsule->setRadius(finished ? scale : next);
    } else {
        capsule->setRadius(radius);
        finished = true;
    }
    if (finished)
        setFinished();
}

}  // namespace uking::action
