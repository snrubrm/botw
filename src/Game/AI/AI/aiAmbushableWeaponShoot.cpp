#include "Game/AI/AI/aiAmbushableWeaponShoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::ai {

AmbushableWeaponShoot::AmbushableWeaponShoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AmbushableWeaponShoot::~AmbushableWeaponShoot() = default;

bool AmbushableWeaponShoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AmbushableWeaponShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("投擲", &pack);
}

void AmbushableWeaponShoot::calc_() {
    if (isCurrentChild("投擲")) {
        if (auto* body = mActor->getRigidBodyByName(sub_71007A24D0()->cstr()))
            body->setScale(mActor->getScale().x * 1.5f);
        if (sub_71007A274C(mActor))
            sub_7100300908();
    }
}

void AmbushableWeaponShoot::sub_7100300908() {
    auto* actor = mActor;
    auto* attack = sub_71007A255C(actor, 0);
    ksys::act::ai::InlineParamPack params;
    if (attack) {
        sead::Vector3f dir = attack->_c;
        if (dir.y < 0.0f)
            dir.y = -dir.y;
        params.addVec3(dir, "TargetDir", -1);
        params.addFloat(sead::Mathf::clamp(attack->_a0.length() * 0.15f, 1.0f, 50.0f), "Power", -1);
    } else {
        sead::Vector3f dir = actor->getVelocity();
        dir.normalize();
        dir.set(-dir.z, -dir.y, dir.x);
        params.addVec3(dir, "TargetDir", -1);
        params.addFloat(100.0f, "Power", -1);
    }
    changeChild("迎撃", &params);
}

void AmbushableWeaponShoot::leave_() {
    if (auto* body = mActor->getRigidBodyByName(sub_71007A24D0()->cstr()))
        body->setScale(mActor->getScale().x);
}

void AmbushableWeaponShoot::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool AmbushableWeaponShoot::isFinished() const {
    return getCurrentChild()->isFinished() || ActionBase::isFinished();
}

bool AmbushableWeaponShoot::isFailed() const {
    return getCurrentChild()->isFailed() || ActionBase::isFailed();
}

}  // namespace uking::ai
