#include "Game/AI/Action/actionExpandSensor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"

namespace uking::action {

ExpandSensor::ExpandSensor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ExpandSensor::~ExpandSensor() = default;

bool ExpandSensor::init_(sead::Heap* heap) {
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    if (auto* capsule = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(body)) {
        const f32 radius = capsule->getRadius();
        sead::BoundBox3f aabb;
        capsule->getAabbInLocal(&aabb);
        const f32 half_height = aabb.getHalfSizeY();
        _c8.y = half_height + half_height - radius;
        capsule->getVertices(&_b0, &_bc);
        _40.sub_71010C36A4(1.0f, 1.0f, &sead::Matrix34f::ident, heap, actor);
    }
    return true;
}

void ExpandSensor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ExpandSensor::leave_() {
    sub_710012A680();
}

void ExpandSensor::loadParams_() {
    getStaticParam(&mParams.mAtkAttrType_s, "AtkAttrType");
    getStaticParam(&mParams.mAtkType_s, "AtkType");
    getStaticParam(&mParams.mOffLength_s, "OffLength");
    getStaticParam(&mParams.mOnLength_s, "OnLength");
}

void ExpandSensor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
