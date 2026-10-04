#include "Game/AI/Action/actionExpandSensorSlowly.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
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
    auto* actor = mActor;
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        if (!body->isAddedToWorld())
            body->setTransform(actor->getMtx());
        const s32 type = *mAtkType_s;
        const s32 attr = *mAtkAttrType_s;
        const u32 attack_flags = type == 0 ? 0x800 : type == 1 ? 1 : 0x1f01f;
        const u32 attack_flags2 = attr == 2 ? 0x4c : attr == 1 ? 0x4a : 0x49;
        auto* sensor = getActorAttackSensor(actor);
        const auto* attack = actor->getParam()->getRes().mGParamList->getAttack();
        sensor->activateAttackSensor(attack_flags, attack_flags2, attack->mPower.ref(),
                                     attack->mImpulseLarge.ref(), 0.0f,
                                     attack->mGuardBreakPower.ref(), 0, -1, false, 1, -1);
        if (auto* capsule = sead::DynamicCast<ksys::phys::CapsuleRigidBody>(body)) {
            _dc = (_c4 - _b8).length();
            sead::Matrix34f home_mtx;
            actor->getHomeMtx(&home_mtx);
            _48.sub_71010C38F4(&home_mtx);
            _48.sub_71010C3A1C(capsule->getRadius());
            _48.sub_71010C3B18(_dc);
        }
        sub_7100059988();
    }
    _e0 = 1.0f;
    _e4 = 1.0f;
    sub_71007A44E4(actor, true);
    mFlags.set(Flag::Changeable);
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
