#include "Game/AI/Action/actionShockWave.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ShockWave::ShockWave(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShockWave::~ShockWave() = default;

bool ShockWave::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShockWave::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* lod = actor->getLodState()) {
        lod->mFlags10.set(0x40);
        if (*mIsReuseActor_m)
            actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    }

    _4c = actor->getScale().x;
    if (*mScaleTime_m > 1.0f) {
        _48 = actor->getScale().x / *mScaleTime_m;
        actor->setScale(sead::Vector3f::ones * _48);
    } else {
        _48 = 0;
    }

    const int attack_attr = *mAttackAttr_m;
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        body->setTransform(actor->getMtx());
        sub_71007A2B64(body, nullptr);
        sub_71007A2EB0(body, actor, nullptr);
        getActorAttackSensor(actor)->activateAttackSensor(0x8000, attack_attr, *mAttackPower_m, 0,
                                                          0.0f, 0, 1, -1, false, *mAtMinDamage_m,
                                                          -1);
    }
}

void ShockWave::leave_() {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        sub_71007A3258(body, nullptr);
        sub_71007A2D34(body);
    }
    if (auto* lod = mActor->getLodState()) {
        lod->mFlags10.reset(0x40);
        if (*mIsReuseActor_m)
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000);
    }
}

void ShockWave::loadParams_() {
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackAttr_m, "AttackAttr");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mIsReuseActor_m, "IsReuseActor");
}

void ShockWave::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
