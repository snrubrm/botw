#include "Game/AI/Action/actionExpandSensorSlowly.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"

namespace uking::action {

ExpandSensorSlowly::ExpandSensorSlowly(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ExpandSensorSlowly::~ExpandSensorSlowly() = default;

bool ExpandSensorSlowly::init_(sead::Heap* heap) {
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    if (auto* capsule = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(body)) {
        sead::BoundBox3f aabb;
        capsule->getAabbInLocal(&aabb);
        const f32 half_height = aabb.getHalfSizeY();
        _d0.y = half_height + half_height - capsule->getRadius();
        capsule->getVertices(&_b8, &_c4);
        _48.sub_71010C36A4(1.0f, 1.0f, &sead::Matrix34f::ident, heap, actor);
    }
    return true;
}

void ExpandSensorSlowly::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ExpandSensorSlowly::leave_() {
    sub_710005A348();
}

void ExpandSensorSlowly::loadParams_() {
    getStaticParam(&mAtkAttrType_s, "AtkAttrType");
    getStaticParam(&mAtkType_s, "AtkType");
    getStaticParam(&mOffLength_s, "OffLength");
    getStaticParam(&mOnLength_s, "OnLength");
    getStaticParam(&mAtExpandStep_s, "AtExpandStep");
}

void ExpandSensorSlowly::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
